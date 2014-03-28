export PRODIR = ../..

export THIRDPARTYDIR = E:/workspace/ThirdParty

#export BUILD_OPT = DLL

BINDIR = ../bin/

OBJSDIR = ../objs/

OBJS =		

LIBS =







#target
ALL_TARGET = all	Fenger math tools examples boostware
CLEAN_TARGET = clean cleanFenger cleanmath cleantools cleanexamples cleanboostware
INSTALL_TARGET = install installFenger installmath installtools installexamples
	
.PHONY:		 $(ALL_TARGET) $(CLEAN_TARGET) $(INSTALL_TARGET)

all:	Fenger math tools examples boostware

Fenger:	
	(cd ./Fenger; make all)

math:
	(cd ./math; make all)
	
tools:
	(cd ./tools; make all)

examples:
	(cd ./examples; make all)
	
boostware:
	(cd ./boostware; make all)







#clean
clean:	cleanFenger cleanmath cleantools cleanexamples cleanboostware

cleanFenger:
	(cd ./Fenger; make clean)
	
cleanmath:
	(cd ./math; make clean)
	
cleantools:
	(cd ./tools; make clean)
	
cleanexamples:
	(cd ./examples; make clean)
	
cleanboostware:
	(cd ./boostware; make clean)








#install
install:	installFenger installmath installtools installexamples
	
installFenger:
	(cd ./Fenger; make install)
	
installmath:
	(cd ./math; make install)
	
installtools:
	(cd ./tools; make install)
	
installexamples:
	(cd ./examples; make install)