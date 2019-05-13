all:

include ../../src/config.mk

LDFLAGS =  -L/deps/anaconda3/lib/ -lboost_python3 -lboost_numpy3 -lpython3.5m
EXTRA_CXXFLAGS += -I.. -I../../src -Wno-sign-compare -I/deps/anaconda3/include/python3.5m/ -I/deps/anaconda3/include

# Kaldi libraries required
ADDLIBS = ../../src/decoder/decoder.a ../../src/lat/lat.a ../../src/fstext/fstext.a  \
	  ../../src/feat/feat.a ../../src/util/util.a ../../src/base/base.a ../../src/cpucompute/cpucompute.a

TESTFILES = 
OBJFILES = decoder_wrapper.o

LIBNAME = decoder_wrapper

include ../../src/makefiles/default_rules.mk

cleantest:
	rm -f *.txt *.svg *.fst

distclean: clean cleantest


