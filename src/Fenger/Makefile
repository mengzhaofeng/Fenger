CXXFLAGS =

BINDIR = ../../bin/

OBJSDIR = ../../objs/

OBJS =		fresnelintegral.o

DSTOBJS = $(foreach N,$(OBJS),$(OBJSDIR)$(N))

LIBS =

INCDIR = 	../../include ../../../ThirdParty/boost1_55/include

TARGET = fresnelintegral.a


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