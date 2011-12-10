CPP  = g++
CC   = gcc
OBJ  = XReal.o
LIB  = libwrapper.a

LIBS +=  -lm 
INCS +=  -I. -I../../core -I../../encodings/solutionType -I../../encodings/variable \
	-I../../util

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) -O3 

CFLAGS = $(INCS) 

.PHONY: all all-before all-after clean clean-custom

all: all-before $(LIB) all-after

clean: clean-custom
	rm -f $(OBJ) $(LIB)

$(LIB): $(OBJ)
	ar -r $(LIB) *.o
	ranlib $(LIB)

.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< 
