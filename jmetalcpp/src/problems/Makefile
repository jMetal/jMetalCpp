CPP  = g++
CC   = gcc
OBJ  = Griewank.o Sphere.o Kursawe.o Fonseca.o Schaffer.o \
ZDT1.o ZDT2.o ZDT3.o ZDT4.o \
ZDT5.o ZDT6.o DTLZ1.o DTLZ2.o DTLZ3.o DTLZ4.o OneMax.o DTLZ5.o \
ProblemFactory.o DTLZ6.o DTLZ7.o LZ09.o LZ09_F1.o LZ09_F2.o \
LZ09_F3.o LZ09_F4.o LZ09_F5.o LZ09_F6.o LZ09_F7.o LZ09_F8.o \
LZ09_F9.o
LIBNAME= libproblems.a

LIBS +=  
INCS +=  -I. -I../core -I../util -I../encodings/solutionType \
	-I../encodings/variable -I../util/wrapper

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
