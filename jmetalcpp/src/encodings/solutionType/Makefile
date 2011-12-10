CPP  = g++
CC   = gcc
OBJ  = ArrayRealSolutionType.o BinaryRealSolutionType.o BinarySolutionType.o RealSolutionType.o
LIBNAME= libsolutionType.a

LIBS +=  -lm 
INCS +=  -I. -I../../core -I../../util -I../variable

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) -O3 

CFLAGS = $(INCS) 

.PHONY: all all-before all-after clean clean-custom

all: all-before $(LIBNAME)  all-after

clean: clean-custom
	rm -f $(OBJ) $(LIBNAME) 

$(LIBNAME): $(OBJ)
	ar -r $(LIBNAME) *.o
	ranlib $(LIBNAME) 

.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< 
