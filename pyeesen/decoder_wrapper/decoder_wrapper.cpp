#include <fst/arc-map.h>
#include <fst/arc.h>
#include "decoder/lattice-faster-decoder.h"
#include "decoder/decodable-matrix.h"
#include "decoder_wrapper.h"
#include "base/kaldi-types.h"
#include "fst/fst-decl.h"
#include "fst/vector-fst.h"
#include "fstext/fstext-lib.h"


namespace eesen {


  LatticeDecoder::~LatticeDecoder() {
    delete decoder_; decoder_ = NULL;
    delete decoder_fst_; decoder_fst_ = NULL;
  }

  LatticeDecoder::LatticeDecoder(std::string lm_model_filename, std::string word_syms_filename, float acoustic_scale, int max_active, float beam, float lattice_beam) {

    acoustic_scale_ = acoustic_scale;
    allow_partial_ = true;

    word_syms_ = fst::SymbolTable::ReadText(word_syms_filename);

    LatticeFasterDecoderConfig config;
    config.max_active = max_active;
    config.beam = beam;
    config.lattice_beam = lattice_beam;

    decoder_fst_ = fst::ReadFstKaldi(lm_model_filename);
    decoder_ = new LatticeFasterDecoder(*decoder_fst_, config);

  }


  std::string LatticeDecoder::Decode(const numpy::ndarray &loglikes_ndarray) {
    // Reset seed each decode to preserve deteminism
    numpy::dtype float_dtype = numpy::dtype::get_builtin<float>();

    // Make sure we get floats (not doubles)
    numpy::ndarray loglikes = loglikes_ndarray.astype(float_dtype);

    // Create a wrapper around NumPy data to pass into Eesen
    MatrixWrapper<float> loglikes_matbase(reinterpret_cast<float*>(loglikes.get_data()), loglikes.shape(1), loglikes.shape(0), loglikes.strides(0)/sizeof(float)); // cols, rows, stride
    Matrix<float> loglikes_mat(loglikes_matbase);
    DecodableMatrixScaled decodable(loglikes_mat, acoustic_scale_);

    if (!decoder_->Decode(&decodable))
      throw_error_already_set();

    if (!decoder_->ReachedFinal() && !allow_partial_)
      throw_error_already_set();

    fst::VectorFst<LatticeArc> decoded;

    if (!decoder_->GetBestPath(&decoded))
      throw_error_already_set();

    std::vector<int> out_ids, out_alignment;
    LatticeWeight weight;
    GetLinearSymbolSequence(decoded, &out_alignment, &out_ids, &weight);
    float out_prob = -(weight.Value1() + weight.Value2());

    std::string decoded_hyp = "";
    for (int i = 0; i < out_ids.size(); ++i) {
      std::string s = word_syms_->Find(out_ids[i]);
      decoded_hyp += s;
      if (i  != out_ids.size()-1)
	decoded_hyp += " ";
    }

    // In future, put lattice stuff here


    // Construct PyTuple to return
    return decoded_hyp;
    //return make_tuple(decoded_hyp,out_prob);
  }


 BOOST_PYTHON_MODULE(eesen){
   numpy::initialize();

   class_<LatticeDecoder>("LatticeDecoder", init<std::string, std::string, float, int, float, float>())
     .def("Decode", &LatticeDecoder::Decode)
     .def("set_acoustic_scale", &LatticeDecoder::set_acoustic_scale)
     ;
 }



} // namespace eesen
