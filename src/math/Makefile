CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

CXXDLLFLAGS = -fPIC -shared

BINDIR = $(PRODIR)/bin/

OBJSDIR = $(PRODIR)/objs/

OBJS =		fresnelintegral.o

DSTOBJS = $(foreach N,$(OBJS),$(OBJSDIR)$(N))

LIBS =

INCDIR = 	$(PRODIR)/include -I$(THIRDPARTYDIR)/boost1_55/include

STATIC_TARGET = fresnelintegral.a

ifeq ($(PLATFORM),win32)
	DLL_TARGET = fresnelintegral.dll
else
	DLL_TARGET = fresnelintegral.so
endif


$(DLL_TARGET):	$(OBJS)
	($(CXX) -o  $(DLL_TARGET) $(CXXDLLFLAGS) $(OBJS) $(LIBS);mv $(DLL_TARGET) $(BINDIR))
	
	
$(filter %.o, $(OBJS)):%.o:%.cpp
	($(CXX) -c $(CXXFLAGS_GLOBAL) $(CXXFLAGS) -I$(INCDIR) $< -o $@)
	

	
.PHONY:all patch clean

all:	$(DLL_TARGET) patch

patch:
	$(foreach N,$(OBJS),mv $(N) $(OBJSDIR);)

clean:
	rm -f $(DSTOBJS) $(BINDIR)$(DLL_TARGET)