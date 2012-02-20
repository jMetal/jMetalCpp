CPP  = g++
CC   = gcc
OBJ  = Comparator.o CrowdingComparator.o DominanceComparator.o \
	ObjectiveComparator.o OverallConstraintViolationComparator.o \
	RankComparator.o EqualSolutions.o CrowdingDistanceComparator.o \
	SolutionComparator.o
LIB  = libcomparators.a

LIBS +=  -lm 
INCS +=  -I. -I.. -I../../core

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
