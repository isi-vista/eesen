#ifndef LATGEN_FASTER_WRAPPER_H
#define LATGEN_FASTER_WRAPPER_H

#include <vector>
#include <boost/python.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/numeric.hpp>
#include <boost/python/numpy.hpp>
#include <boost/python/numpy/ndarray.hpp>
#include <boost/python/errors.hpp>

#include "fst/fst-decl.h"
#include "decoder/decodable-matrix.h"



using namespace boost::python;


namespace eesen { 

  // forward declarations - useful for interfacing the class from Python/Java
  // No need to include the headers

  template <typename Num> class Matrix;

  class LatticeFasterDecoder;
  struct LatticeFasterConfig;
  template<typename > class VectorBase;
  template<typename > class MatrixBase;

  template<typename Real>
  class MatrixWrapper : public MatrixBase<Real> {
  public:
    MatrixWrapper(Real *data, MatrixIndexT cols, MatrixIndexT rows, MatrixIndexT stride): MatrixBase<Real>(data, cols, rows, stride) {};
  };

}


namespace eesen {


class LatticeDecoder {
  public:
    LatticeDecoder(std::string lm_model_filename, std::string word_sym_file, float acoustic_scale, int max_active, float beam, float lattice_beam);

    ~LatticeDecoder();
    std::string Decode(const numpy::ndarray &loglikes);

    void set_acoustic_scale(float acoustic_scale) { acoustic_scale_ = acoustic_scale; }

  private:
    LatticeFasterDecoder *decoder_;
    fst::VectorFst<fst::StdArc> * decoder_fst_;
    fst::SymbolTable *word_syms_;
    float acoustic_scale_;
    bool allow_partial_;
};



}

#endif  // #ifdef LATGEN_FASTER_WRAPPER_H
