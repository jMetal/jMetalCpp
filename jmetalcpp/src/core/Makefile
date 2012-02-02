CPP  = g++
CC   = gcc
OBJ  = Algorithm.o Operator.o Problem.o Solution.o SolutionSet.o SolutionType.o Variable.o
LIB  = libcore.a

LIBS +=  -lm 
INCS +=  -I. -I../util/comparators

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) -O3 

CFLAGS = $(INCS) 

.PHONY: all all-before all-after clean clean-custom

all: all-before $(LIB) all-after

clean: clean-custom
	rm -f $(OBJ) $(LIB)

libcore.a: $(OBJ)
	ar -r $(LIB) *.o
	ranlib $(LIB)
	ar -r ../libjmetal.a libcore.a

.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< 

