CPP  = g++
CC   = gcc
OBJ  = BinaryTournament2.o DifferentialEvolutionSelection.o Selection.o
LIB  = libselection.a

LIBS +=  -lm 
INCS +=  -I. -I../../core -I../../encodings/solutionType -I../../encodings/variable \
	-I../../util -I../../util/comparators

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
	ar -r ../../libjmetal.a libselection.a

.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< 
