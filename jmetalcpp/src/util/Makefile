CPP  = g++
CC   = gcc
OBJ  = Distance.o PermutationUtility.o PseudoRandom.o RandomGenerator.o Ranking.o \
AdaptiveGrid.o NonDominatedSolutionList.o
LIBNAME= libutil.a

LIBS += 
#INCS +=  -I. -I../core -Icomparators
INCS +=  -I. -I../core -Icomparators

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) 

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
