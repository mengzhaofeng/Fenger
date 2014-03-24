CXXFLAGS =


#module
MODULENAME	=	examples

PREDEFINE = 

ifeq ($(BUILD_OPT),STATIC)
	PREDEFINE += BUILD_FENGER_$(BUILD_OPT)
endif

export PREDEFINES = $(foreach N,$(PREDEFINE),-D$(N))

OBJS =		$(MODULENAME).o 


#libdir
BINDIR = $(PRODIR)/bin/$(PLATFORM)/

LIBDIR = $(PRODIR)/lib/$(PLATFORM)/	

OBJSDIR = $(PRODIR)/objs/



DSTOBJS = $(foreach N,$(OBJS),$(OBJSDIR)$(N))

LIBS = tools

LLIBS = $(foreach N, $(LIBS), -l$(N))

INCDIR = 	$(PRODIR)/include $(THIRDPARTYDIR)/boost1_55/include

INCDIRS	= $(foreach N,$(INCDIR), -I$(N))




ifeq ($(PLATFORM),win32)
	TARGET = $(MODULENAME).exe
else
	TARGET = $(MODULENAME)
endif




#com
$(TARGET):	$(OBJS)
	($(CXX) -o $(TARGET) $(OBJS)  -L$(LIBDIR) $(LLIBS);mv $(TARGET) $(BINDIR))
	
	
$(filter %.o, $(OBJS)):%.o:%.cpp
	($(CXX) -c $(PREDEFINES) $(CXXFLAGS_GLOBAL) $(CXXFLAGS) $(INCDIRS) $< -o $@)
	




#target	
.PHONY:all patch clean

all:	$(TARGET) patch

patch:
	$(foreach N,$(OBJS),mv $(N) $(OBJSDIR);)





#clean
clean:
	rm -f $(DSTOBJS) $(BINDIR)$(TARGET)