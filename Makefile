export CXXFLAGS_GLOBAL =	-O2 -g -Wall -fmessage-length=0

BINDIR = ./bin/

OBJSDIR = ./objs/

OBJS =		

LIBS =

TARGET = Fenger.exe
	
.PHONY:		all	src 

all:	src

src:	
	(cd ./src; make all)

clean:
	(cd ./src; make clean)
