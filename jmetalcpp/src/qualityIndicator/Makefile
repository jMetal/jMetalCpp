CPP  = g++
CC   = gcc
OBJ  = Epsilon.o Fitness.o GenerationalDistance.o Hypervolume.o \
	InvertedGenerationalDistance.o QualityIndicator.o Spread.o
LIB  = libqualityIndicator.a

LIBS +=  
INCS +=  -I. -I../core \
	-I../util -I../util/comparators -I./util

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
