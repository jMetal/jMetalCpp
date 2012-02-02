CPP  = g++
CC   = gcc
OBJ  = QualityIndicator.o Hypervolume.o
LIB  = libqualityIndicator.a

LIBS +=  -lm 
INCS +=  -I. -I../core \
	-I../util -I../util/comparators -I./util

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
	ar -r ../libjmetal.a libqualityIndicator.a

.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< 
