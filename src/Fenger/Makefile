CXXFLAGS =

BINDIR = $(PRODIR)/bin/

OBJSDIR = $(PRODIR)/objs/

OBJS =		Fenger.o Mesher.o

DSTOBJS = $(foreach N,$(OBJS),$(OBJSDIR)$(N))

LIBS =

INCDIR = 	$(PRODIR)/include -I$(THIRDPARTYDIR)/boost1_55/include



ifeq ($(PLATFORM),win32)
	TARGET = Fenger.exe
else
	TARGET = Fenger
endif


$(TARGET):	$(OBJS)
	($(CXX) -o $(TARGET) $(OBJS) $(LIBS);mv $(TARGET) $(BINDIR))
	
	
$(filter %.o, $(OBJS)):%.o:%.cpp
	($(CXX) -c $(CXXFLAGS_GLOBAL) $(CXXFLAGS) -I$(INCDIR) $< -o $@)
	

	
.PHONY:all patch clean

all:	$(TARGET) patch

patch:
	$(foreach N,$(OBJS),mv $(N) $(OBJSDIR);)

clean:
	rm -f $(DSTOBJS) $(BINDIR)$(TARGET)