CPP  = g++
CC   = gcc
OBJ  = Mutation.o PolynomialMutation.o BitFlipMutation.o
LIB  = libmutation.a

LIBS +=  -lm 
INCS +=  -I. -I../../core -I../../util/wrapper -I../../encodings/solutionType -I../../encodings/variable \
	-I../../util

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) 

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
