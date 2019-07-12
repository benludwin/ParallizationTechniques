
CXX=g++ -m64
CXXFLAGS=-Iobjs/ -Wall -std=c++11
iSPC=ispc
iSPCFLAGS=-O2 --arch=x86-64 --target=sse2 
CIMGFLAGS=-O2 -L/usr/X11R6/lib -lm -lpthread -lX11

default: blur

.PHONY: dirs clean
.PRECIOUS: objs/blur.h

dirs:
	/bin/mkdir -p objs/

clean:
	/bin/rm -rf objs *~ blur

blur: dirs objs/blur.o objs/blur_ispc.o
	$(CXX) $(CIMGFLAGS) -o $@ objs/blur.o objs/blur_ispc.o

objs/blur.o: blur.cpp objs/blur_ispc.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

objs/%_ispc.h objs/%_ispc.o: %.ispc
	ispc -O2 --arch=x86-64 --target=sse2 $< -o objs/$*_ispc.o -h objs/$*_ispc.h

run: blur
	./blur
