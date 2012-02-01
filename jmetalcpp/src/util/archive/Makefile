CPP  = g++
CC   = gcc
OBJ  = Archive.o CrowdingArchive.o AdaptiveGridArchive.o
LIB  = libarchive.a

LIBS +=  -lm 
INCS +=  -I. -I../../core -I../../util -I../comparators

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
