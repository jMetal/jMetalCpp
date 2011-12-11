CPP  = g++
CC   = gcc
OBJ  = Kursawe.o Fonseca.o Schaffer.o ZDT1.o ZDT2.o ZDT3.o ZDT4.o ZDT6.o DTLZ1.o
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
