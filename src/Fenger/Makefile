CXXFLAGS =


#module
MODULENAME	=	Fenger




#libdir
BINDIR = $(PRODIR)/bin/$(PLATFORM)/

LIBDIR = $(PRODIR)/lib/$(PLATFORM)/	

OBJSDIR = $(PRODIR)/objs/

OBJS =		$(MODULENAME).o Mesher.o

DSTOBJS = $(foreach N,$(OBJS),$(OBJSDIR)$(N))

LIBS =

INCDIR = 	$(PRODIR)/include $(THIRDPARTYDIR)/boost1_55/include

INCDIRS	= $(foreach N,$(INCDIR), -I$(N))




ifeq ($(PLATFORM),win32)
	TARGET = $(MODULENAME).exe
else
	TARGET = $(MODULENAME)
endif




#com
$(TARGET):	$(OBJS)
	($(CXX) -o $(TARGET) $(OBJS) $(LIBS);mv $(TARGET) $(BINDIR))
	
	
$(filter %.o, $(OBJS)):%.o:%.cpp
	($(CXX) -c $(CXXFLAGS_GLOBAL) $(CXXFLAGS) $(INCDIRS) $< -o $@)
	




#target	
.PHONY:all patch clean

all:	$(TARGET) patch

patch:
	$(foreach N,$(OBJS),mv $(N) $(OBJSDIR);)





#clean
clean:
	rm -f $(DSTOBJS) $(BINDIR)$(TARGET)
	
	
#install
install:
	