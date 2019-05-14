# TODO Cython does not recompile because of the templates and sourcefiles
FSTDIR=../tools/openfst
AFSTDIR=$(PWD)/$(FSTDIR)
PYTHON=python
INSTALL_PREFIX=/usr/local
INSTALL_PYTHON_PREFIX=/usr/local/
# OPENFST_VERSION=1.4.1 # fails with pyfst
OPENFST_VERSION=1.3.4
LINUX=$(shell lsb_release -sd | sed 's: :_:g')
EESEN_LIBS = ../src/decoder/decoder.a ../src/lat/lat.a ../src/fstext/fstext.a  \
	     ../src/feat/feat.a ../src/util/util.a ../src/base/base.a ../src/cpucompute/cpucompute.a

all: decoder_wrapper/decoder.a eesen/decoder_wrapper.so

decoder_wrapper/decoder.a: $(FSTDIR)/lib/libfst.a
	$(MAKE) -C decoder_wrapper/

eesen/decoder_wrapper.so: decoder_wrapper/decoder_wrapper.a
	PYEESEN_ADDLIBS="decoder_wrapper/decoder_wrapper.a $(EESEN_LIBS)" \
	LIBRARY_PATH=$(AFSTDIR)/lib:$(AFSTDIR)/lib/fst CPLUS_INCLUDE_PATH=$(AFSTDIR)/include \
	$(PYTHON) setup.py build_ext --inplace

distclean:
	$(MAKE) -C decoder_wrapper distclean
	$(PYTHON) setup.py clean --all

