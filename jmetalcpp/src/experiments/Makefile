CPP  = g++
CC   = gcc
OBJ  = Settings.o NSGAII_Settings.o
LIBNAME= libexperiments.a

LIBS +=  
INCS +=  -I. -I../core -I../util -I../encodings/solutionType \
	-I../encodings/variable -I../util/comparators \
	-I../problems -I../util/wrapper -I../metaheuristics/nsgaII \
	-I../operators/crossover -I../operators/mutation -I../operators/selection

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
