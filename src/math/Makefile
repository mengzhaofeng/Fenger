#Option
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

CXXDLLFLAGS = -fPIC -shared

ARFLAGS	= -r

#Module
MODULENAME	= fresnelintegral

#command
AR		= ar



#d
BINDIR = $(PRODIR)/bin/$(PLATFORM)/

LIBDIR = $(PRODIR)/lib/$(PLATFORM)/

OBJSDIR = $(PRODIR)/objs/

DSTOBJS = $(foreach N,$(OBJS),$(OBJSDIR)$(N))

INCDIR = 	$(PRODIR)/include $(THIRDPARTYDIR)/boost1_55/include

INCDIRS	= $(foreach N,$(INCDIR), -I$(N))

LIBS =

OBJS =		$(MODULENAME).o


#TARGET
ifeq ($(COMPILER),GCC)
	STATIC_TARGET = lib$(MODULENAME).a
else
	STATIC_TARGET = $(MODULENAME).lib
endif

ifeq ($(PLATFORM),win32)
	DLL_TARGET = $(MODULENAME).dll
else
	DLL_TARGET = $(MODULENAME).so
endif


#command
$(DLL_TARGET):	$(OBJS)
	($(CXX) -o  $(DLL_TARGET) $(CXXDLLFLAGS) $(OBJS) $(LIBS);mv $(DLL_TARGET) $(BINDIR))
	
$(STATIC_TARGET):	$(OBJS)
	($(AR) $(ARFLAGS) $(STATIC_TARGET) $(OBJS); mv $(STATIC_TARGET) $(LIBDIR))
	
$(filter %.o, $(OBJS)):%.o:%.cpp
	($(CXX) -c $(CXXFLAGS_GLOBAL) $(CXXFLAGS) $(INCDIRS) $< -o $@)
	



#target
.PHONY:all patch clean

all:	$(DLL_TARGET) $(STATIC_TARGET) patch

patch:
	$(foreach N,$(OBJS),mv $(N) $(OBJSDIR);)




#clean
clean:
	rm -f $(DSTOBJS) $(BINDIR)$(DLL_TARGET) $(LIBDIR)$(STATIC_TARGET)