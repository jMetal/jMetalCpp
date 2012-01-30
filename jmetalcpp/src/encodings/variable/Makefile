CPP  = g++
CC   = gcc
OBJ  = ArrayReal.o Binary.o BinaryReal.o Real.o
LIBNAME= libvariable.a

LIBS +=  -lm -pthread
INCS +=  -I. -I../../core -I../../util

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) -g

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
