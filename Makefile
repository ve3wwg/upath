CXX	:= g++
OPTZ	= -g -Og
INCL	= -I.
STD	= -std=c++17

.cpp.o:
	$(CXX) -c $(STD) -Wall -Wextra $(WARN) $(OPTZ) $(INCL) $< -o $*.o

all:	upath

upath: 	upath.o
	$(CXX) $(STD) upath.o -o upath

clean:
	rm -f *.o

clobber: clean
	rm -f upath
