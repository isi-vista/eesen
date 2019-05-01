# This file was generated using the following command:
# ./configure --shared --use-cuda=no

# Rules that enable valgrind debugging ("make valgrind")

valgrind: .valgrind

.valgrind:
	echo -n > valgrind.out
	for x in $(TESTFILES); do echo $$x>>valgrind.out; valgrind ./$$x >/dev/null 2>> valgrind.out; done
	! ( grep 'ERROR SUMMARY' valgrind.out | grep -v '0 errors' )
	! ( grep 'definitely lost' valgrind.out | grep -v -w 0 )
	rm valgrind.out
	touch .valgrind


KALDI_FLAVOR := dynamic
KALDILIBDIR := /nfs/isicvlnas01/users/xpeng/workspace/gaia/docker/ocr/eesen-dbg/src/lib
CONFIGURE_VERSION := 2
FSTROOT = /nfs/isicvlnas01/users/xpeng/workspace/gaia/docker/ocr/eesen-dbg/tools/openfst
OPENFST_VER = 1.4.1
OPENFST_GE_10400 = 1
EXTRA_CXXFLAGS += -DHAVE_OPENFST_GE_10400 -std=c++0x
OPENFSTLIBS = -L/nfs/isicvlnas01/users/xpeng/workspace/gaia/docker/ocr/eesen-dbg/tools/openfst/lib -lfst
OPENFSTLDFLAGS = -Wl,-rpath=/nfs/isicvlnas01/users/xpeng/workspace/gaia/docker/ocr/eesen-dbg/tools/openfst/lib
ATLASINC = [somewhere]/include
ATLASLIBS = [somewhere]/liblapack.a [somewhere]/libcblas.a [somewhere]/libatlas.a [somewhere]/libf77blas.a
# You have to make sure ATLASLIBS is set...

ifndef FSTROOT
$(error FSTROOT not defined.)
endif

ifndef ATLASINC
$(error ATLASINC not defined.)
endif

ifndef ATLASLIBS
$(error ATLASLIBS not defined.)
endif


CXXFLAGS = -msse -msse2 -Wall -I.. \
	   -pthread \
      -DKALDI_DOUBLEPRECISION=0 -DHAVE_POSIX_MEMALIGN \
      -Wno-sign-compare -Wno-unused-local-typedefs -Winit-self \
      -DHAVE_EXECINFO_H=1 -rdynamic -DHAVE_CXXABI_H \
      -DHAVE_ATLAS -I$(ATLASINC) \
      -I$(FSTROOT)/include \
      $(EXTRA_CXXFLAGS) \
      -g # -O0 -DKALDI_PARANOID 

ifeq ($(KALDI_FLAVOR), dynamic)
CXXFLAGS += -fPIC
endif

LDFLAGS = -rdynamic $(OPENFSTLDFLAGS)
LDLIBS = $(EXTRA_LDLIBS) $(OPENFSTLIBS) $(ATLASLIBS) -lm -lpthread -ldl
CC = g++
CXX = g++
AR = ar
AS = as
RANLIB = ranlib
