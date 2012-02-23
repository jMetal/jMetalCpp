CPP  = g++
CC   = gcc

LIBS +=  
INCS +=  -I. -I.. -I../util -I../../core -I../../util -I../../util/comparators

EXECS = Epsilon GenerationalDistance Hypervolume InvertedGenerationalDistance \
	Spread
WINEXECS = Epsilon.exe GenerationalDistance.exe Hypervolume.exe \
	InvertedGenerationalDistance.exe Spread.exe
DEPS = ../../libjmetal.a

BIN_DIRECTORY = ../../../bin

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) 

CFLAGS = $(INCS)
#$(CPP) $(CXXFLAGS) -c $<  

.PHONY: all all-before all-after clean clean-custom

all: all-before $(EXECS) clean all-after

clean: clean-custom
	rm -f $(EXECS)
	rm -f $(WINEXECS)

Epsilon: Epsilon_main.cpp $(DEPS)
	$(CPP) Epsilon_main.cpp $(DEPS) -o Epsilon $(INCS) $(LIBS)
	cp Epsilon $(BIN_DIRECTORY)

GenerationalDistance: GenerationalDistance_main.cpp $(DEPS)
	$(CPP) GenerationalDistance_main.cpp $(DEPS) -o GenerationalDistance $(INCS) $(LIBS)
	cp GenerationalDistance $(BIN_DIRECTORY)

Hypervolume: Hypervolume_main.cpp $(DEPS)
	$(CPP) Hypervolume_main.cpp $(DEPS) -o Hypervolume $(INCS) $(LIBS)
	cp Hypervolume $(BIN_DIRECTORY)

InvertedGenerationalDistance: InvertedGenerationalDistance_main.cpp $(DEPS)
	$(CPP) InvertedGenerationalDistance_main.cpp $(DEPS) -o InvertedGenerationalDistance $(INCS) $(LIBS)
	cp InvertedGenerationalDistance $(BIN_DIRECTORY)

Spread: Spread_main.cpp $(DEPS)
	$(CPP) Spread_main.cpp $(DEPS) -o Spread $(INCS) $(LIBS)
	cp Spread $(BIN_DIRECTORY)

#.cpp.o: $(DEPS)
#	$(CPP) $< $(DEPS) -o NSGAII_main $(INCS) $(LIBS)
