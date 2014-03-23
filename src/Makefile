export PRODIR = ../..

export THIRDPARTYDIR = F:/workspace/ThirdParty

BINDIR = ../bin/

OBJSDIR = ../objs/

OBJS =		

LIBS =

ALL_TARGET = all	Fenger math tools examples
CLEAN_TARGET = clean cleanFenger cleanmath cleantools cleanexamples
	
.PHONY:		 $(ALL_TARGET) $(CLEAN_TARGET)

all:	Fenger math tools examples

Fenger:	
	(cd ./Fenger; make all)

math:
	(cd ./math; make all)
	
tools:
	(cd ./tools; make all)

examples:
	(cd ./examples; make all)

clean:	cleanFenger cleanmath cleantools cleanexamples

cleanFenger:
	(cd ./Fenger; make clean)
	
cleanmath:
	(cd ./math; make clean)
	
cleantools:
	(cd ./tools; make clean)
	
cleanexamples:
	(cd ./examples; make clean)