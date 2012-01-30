CPP  = g++
CC   = gcc
OBJ  = nsgaII/NSGAII.o gGA/gGA.o smpso/SMPSO.o gde3/GDE3.o de/DE.o \
ssGA/ssGA.o pso/PSO.o
LIB  = libmetaheuristics.a

LIBS +=  -lm -pthread
INCS +=  -I. -I../core -InsgaII -IgGA -Ismpso -Igde3 -Ide -IssGA -Ipso \
	 -I../util -I../util/archive -I../util/comparators -I../util/wrapper \
	 -I../encodings/solutionType -I../encodings/variable -I../operators/selection

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) -g

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
