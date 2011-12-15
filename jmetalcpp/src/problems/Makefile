CPP  = g++
CC   = gcc
OBJ  = Sphere.o Kursawe.o Fonseca.o Schaffer.o ZDT1.o ZDT2.o ZDT3.o ZDT4.o   \
ZDT5.o ZDT6.o DTLZ1.o DTLZ2.o DTLZ3.o DTLZ4.o OneMax.o
LIBNAME= libproblems.a

LIBS +=  -lm 
INCS +=  -I. -I../core -I../util -I../encodings/solutionType \
	-I../encodings/variable -I../util/wrapper

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) -O3 

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
