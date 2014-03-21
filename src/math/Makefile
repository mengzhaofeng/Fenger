CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

BINDIR = ../../bin/

OBJSDIR = ../../objs/

OBJS =		Fenger.o Mesher.o

DSTOBJS = $(foreach N,$(OBJS),$(OBJSDIR)$(N))

LIBS =

INCDIR = 	../../include ../../../ThirdParty/boost1_55/include


TARGET = Fenger.exe


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