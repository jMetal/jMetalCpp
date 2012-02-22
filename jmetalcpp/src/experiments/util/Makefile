CPP  = g++
CC   = gcc
OBJ  = FileUtils.o RBoxplot.o RunExperiment.o RWilcoxon.o \
	Statistics.o
LIBNAME= libexperimentsutil.a

LIBS +=  
INCS +=  -I. -I.. -I../../core -I../../encodings/solutionType \
	-I../../encodings/variable -I../../util/comparators -I../../util \
	-I../../problems -I../../util/wrapper -I../../qualityIndicator \
	-I../../qualityIndicator/util

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
