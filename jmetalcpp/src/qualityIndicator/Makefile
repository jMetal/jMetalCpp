CPP  = g++
CC   = gcc
OBJ  = QualityIndicator.o Hypervolume.o
LIB  = libqualityIndicator.a

LIBS +=  -lm -pthread
INCS +=  -I. -I../core \
	-I../util -I../util/comparators -I./util

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

.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< 
