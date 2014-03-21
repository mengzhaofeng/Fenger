export CXXFLAGS_GLOBAL =	-O2 -g -Wall -fmessage-length=0

export PLATFORM = win32

export COMPILER = GCC

BINDIR = ./bin/

OBJSDIR = ./objs/

OBJS =		

LIBS =

TARGET = Fenger
	
.PHONY:		all	src 

all:	src

src:	
	(cd ./src; make all)

clean:
	(cd ./src; make clean)
