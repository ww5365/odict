#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-pipe \
  -fsigned-char \
  -Wall \
  -W \
  -g \
  -fPIC \
  -g \
  -Winline \
  -Wall \
  -pipe \
  -fPIC \
  -O2 \
  -finline-functions
CFLAGS=
CPPFLAGS=-DVERSION=\"1.1.4.2\" \
  -DLINUX \
  -D_REENTRANT
INCPATH=-I.
DEP_INCPATH=-I../../lib2-64/dict \
  -I../../lib2-64/dict/include \
  -I../../lib2-64/dict/output \
  -I../../lib2-64/dict/output/include \
  -I../../lib2-64/ullib \
  -I../../lib2-64/ullib/include \
  -I../../lib2-64/ullib/output \
  -I../../lib2-64/ullib/output/include

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=900149310ca43ff9e634ffa492c8d3da  COMAKE


.PHONY:all
all:comake2_makefile_check libodict.a 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mall[0m']"
	@echo "make all done"

.PHONY:comake2_makefile_check
comake2_makefile_check:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcomake2_makefile_check[0m']"
	#in case of error, update 'Makefile' by 'comake2'
	#@echo "$(COMAKE_MD5)">comake2.md5
	#@md5sum -c --status comake2.md5
	#@rm -f comake2.md5

.PHONY:ccpclean
ccpclean:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mccpclean[0m']"
	@echo "make ccpclean done"

.PHONY:clean
clean:ccpclean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf libodict.a
	rm -rf ./output/lib/libodict.a
	rm -rf ./output/include/odict.h
	rm -rf odict_odict.o

.PHONY:dist
dist:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdist[0m']"
	tar czvf output.tar.gz output
	@echo "make dist done"

.PHONY:distclean
distclean:clean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdistclean[0m']"
	rm -f output.tar.gz
	@echo "make distclean done"

.PHONY:love
love:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlove[0m']"
	@echo "make love done"

libodict.a:odict_odict.o \
  odict.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibodict.a[0m']"
	ar crs libodict.a odict_odict.o
	mkdir -p ./output/lib
	cp -f libodict.a ./output/lib
	mkdir -p ./output/include
	cp -f odict.h ./output/include

odict_odict.o:odict.cpp \
  odict.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40modict_odict.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o odict_odict.o odict.cpp

endif #ifeq ($(shell uname -m),x86_64)


