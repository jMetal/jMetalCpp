CPP  = g++
CC   = gcc
OBJ  = GDE3_Settings.o NSGAII_Settings.o SMPSO_Settings.o
LIBNAME= libexperimentssettings.a

LIBS +=  
INCS +=  -I. -I.. -I../../core -I../../util -I../../encodings/solutionType \
	-I../../encodings/variable -I../../util/comparators \
	-I../../problems -I../../util/wrapper -I../../metaheuristics/nsgaII \
	-I../../metaheuristics/gde3 -I../../metaheuristics/smpso \
	-I../../operators/crossover -I../../operators/mutation -I../../operators/selection \
	-I../util -I../../qualityIndicator -I../../qualityIndicator/util \
	-I../../util/archive

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
