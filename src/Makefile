export PRODIR = ../..

export THIRDPARTYDIR = F:/workspace/ThirdParty

export BUILD_OPT = STATIC

export PREDEFINE = BUILD_FENGER_$(BUILD_OPT)

export PREDEFINES = $(foreach N,$(PREDEFINE),-D$(N))

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