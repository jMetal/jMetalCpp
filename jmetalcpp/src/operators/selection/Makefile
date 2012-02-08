CPP  = g++
CC   = gcc
OBJ  = BestSolutionSelection.o BinaryTournament.o BinaryTournament2.o \
	DifferentialEvolutionSelection.o Selection.o WorstSolutionSelection.o
LIB  = libselection.a

LIBS +=  -lm 
INCS +=  -I. -I../../core -I../../encodings/solutionType -I../../encodings/variable \
	-I../../util -I../../util/comparators

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
