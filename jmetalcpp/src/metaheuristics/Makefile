CPP  = g++
CC   = gcc
OBJ  = nsgaII/NSGAII.o
LIB  = libmetaheuristics.a

LIBS +=  -lm 
INCS +=  -I. -I../core -InsgaII -I../util/comparators \
	-I../util

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) -O3 

CFLAGS = $(INCS) 

.PHONY: all all-before all-after clean clean-custom

all: all-before $(LIB) all-after

clean: clean-custom
	rm -f *.o $(LIB)

$(LIB): $(OBJ)
	ar -r $(LIB) *.o
	ranlib $(LIB)

.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< 
