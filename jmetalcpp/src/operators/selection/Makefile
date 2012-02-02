CPP  = g++
CC   = gcc
OBJ  = BinaryTournament2.o DifferentialEvolutionSelection.o Selection.o \
BestSolutionSelection.o WorstSolutionSelection.o
LIB  = libselection.a

LIBS +=  -lm -pthread
INCS +=  -I. -I../../core -I../../encodings/solutionType -I../../encodings/variable \
	-I../../util -I../../util/comparators

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) -g

CFLAGS = $(INCS) 

.PHONY: all all-before all-after clean clean-custom

all: all-before $(LIB) all-after

clean: clean-custom
	rm -f $(OBJ) $(LIB)

$(LIB): $(OBJ)
	ar -r $(LIB) *.o
	ranlib $(LIB)
	ar -r ../../libjmetal.a libselection.a

.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< 
