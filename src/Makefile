export PRODIR = ../..

export THIRDPARTYDIR = E:/workspace/ThirdParty

BINDIR = ../bin/

OBJSDIR = ../objs/

OBJS =		

LIBS =

TARGET = 
	
.PHONY:		all	Fenger math clean cleanFenger cleanmath

all:	Fenger math

Fenger:	
	(cd ./Fenger; make all)

math:
	(cd ./math; make all)

clean:	cleanFenger cleanmath

cleanFenger:
	(cd ./Fenger; make clean)
	
cleanmath:
	(cd ./math; make clean)