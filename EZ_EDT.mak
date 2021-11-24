

UNAME := $(shell uname)

ifeq ($(shell uname -o 2>/dev/null),Msys)
	OS := MINGW
endif

ifneq ("$(OS)","")
	EZ_PATH=../../
endif

EZ_EDTLIB_PATH=$(EZ_PATH)/libeasea/

CXXFLAGS =  -std=c++14 -fopenmp -O2 -g -Wall -fmessage-length=0 -I$(EZ_EDTLIB_PATH)include

OBJS = EZ_EDT.o EZ_EDTIndividual.o 

LIBS = -lpthread -fopenmp 
ifneq ("$(OS)","")
	LIBS += -lws2_32 -lwinmm -L"C:\MinGW\lib"
endif

#USER MAKEFILE OPTIONS :

#END OF USER MAKEFILE OPTIONS

TARGET =	EZ_EDT

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS) -g $(EZ_EDTLIB_PATH)/libeasea.a $(LIBS)

	
#%.o:%.cpp
#	$(CXX) -c $(CXXFLAGS) $^

all:	$(TARGET)
clean:
ifneq ("$(OS)","")
	-del $(OBJS) $(TARGET).exe
else
	rm -f $(OBJS) $(TARGET)
endif
easeaclean:
ifneq ("$(OS)","")
	-del $(TARGET).exe *.o *.cpp *.hpp EZ_EDT.png EZ_EDT.dat EZ_EDT.prm EZ_EDT.mak Makefile EZ_EDT.vcproj EZ_EDT.csv EZ_EDT.r EZ_EDT.plot EZ_EDT.pop
else
	rm -f $(TARGET) *.o *.cpp *.hpp EZ_EDT.png EZ_EDT.dat EZ_EDT.prm EZ_EDT.mak Makefile EZ_EDT.vcproj EZ_EDT.csv EZ_EDT.r EZ_EDT.plot EZ_EDT.pop
endif

