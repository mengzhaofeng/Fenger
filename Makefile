export CXXFLAGS_GLOBAL =	-O2 -g -Wall -fmessage-length=0

export PLATFORM = win32

export COMPILER = GCC

BUILD = DLL

ifeq ($(BUILD),ALL)
	MAKE_CMD=make all BUILD_OPT=STATIC; make all BUILD_OPT=DLL
else
	ifeq ($(BUILD),DLL)
		MAKE_CMD= make all BUILD_OPT=DLL
	else
		MAKE_CMD= make all BUILD_OPT=STATIC
	endif
endif

BINDIR = ./bin/

OBJSDIR = ./objs/

INSDIR = 

OBJS =		

LIBS =

TARGET = Fenger
	
.PHONY:		all	src clean install

all:	src

src:	
	(cd ./src; $(MAKE_CMD))

clean:
	(cd ./src; make clean)
	
install:
	(cd ./src; make install)