CPP  = g++
CC   = gcc
OBJ  = nsgaII/NSGAII.o gGA/gGA.o ssGA/ssGA.o smpso/SMPSO.o gde3/GDE3.o de/DE.o \
	pso/PSO.o paes/paes.o moead/MOEAD.o moead/UtilsMOEAD.o
LIB  = libmetaheuristics.a

LIBS +=  -lm 
INCS +=  -I. -I../core -InsgaII -IgGA -IssGA -Ismpso -Ipso -Igde3 -Ide -Ipaes \
	-Imoead -I../util -I../util/archive -I../util/comparators \
	-I../util/wrapper -I../encodings/solutionType -I../encodings/variable \
	-I../operators/selection

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) -O3 

CFLAGS = $(INCS) 

.PHONY: all all-before all-after clean clean-custom

all: all-before $(LIB) all-after

clean: clean-custom
	rm  -f $(LIB) 
	find . -name "*.o" -exec rm {} \;

$(LIB): $(OBJ)
	ar -r $(LIB) $(OBJ)
	ranlib $(LIB)

.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< -o $@
	cp $@ .

