CPP  = g++
CC   = gcc

LIBS +=  -lm 
#INCS +=  -I. -I../core -I../util -I../util/comparators -I../operators -I../metaheuristics -I../problems \
	-I../encodings/solutionType -I../encodings/variable
INCS +=  -I. -I../core -I../util -I../problems -I../util/comparators \
	-I../encodings/solutionType -I../encodings/variable -I../util/wrapper \
	-I../metaheuristics/nsgaII -I../operators/crossover -I../operators/mutation \
	-I../operators/selection -I../metaheuristics/gGA -I../metaheuristics/gde3 \
	-I../metaheuristics/de -I../metaheuristics/smpso -I../util/archive \
	-I../metaheuristics/paes 

#EXECS = NSGAII_main PAES_main gGA_main autodock DE_main GDE3_main
#DEPS = ../libjmetal.a ../metaheuristics/libmetaheuristics.a 
EXECS = autodock_main NSGAII_main NSGAIIbin_main gGA_main gGAbin_main GDE3_main DE_main \
	SMPSO_main PAES_main
WINEXECS = autodock_main.exe NSGAII_main.exe NSGAIIbin_main.exe NSGAII_main.exe gGA_main.exe \
	gGAbin_main.exe GDE3_main.exe DE_main.exe SMPSO_main.exe PAES_main.exe
DEPS = ../libjmetal.a

BIN_DIRECTORY = ../../bin

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) -O3 

CFLAGS = $(INCS)
#$(CPP) $(CXXFLAGS) -c $<  

.PHONY: all all-before all-after clean clean-custom

all: all-before $(EXECS) all-after

clean: clean-custom
	rm -f $(EXECS)
	rm -f $(WINEXECS)

NSGAII_main: NSGAII_main.cpp $(DEPS)
	$(CPP) NSGAII_main.cpp $(DEPS) -o NSGAII_main $(INCS) $(LIBS)
	cp NSGAII_main $(BIN_DIRECTORY)

NSGAIIbin_main: NSGAIIbin_main.cpp $(DEPS)
	$(CPP) NSGAIIbin_main.cpp $(DEPS) -o NSGAIIbin_main $(INCS) $(LIBS)
	cp NSGAIIbin_main $(BIN_DIRECTORY)

GDE3_main: GDE3_main.cpp $(DEPS)
	$(CPP) GDE3_main.cpp  ../libjmetal.a -o GDE3_main $(INCS) $(LIBS)
	cp GDE3_main $(BIN_DIRECTORY)

PAES_main: PAES_main.cpp $(DEPS)
	$(CPP) PAES_main.cpp ../libjmetal.a -o PAES_main $(INCS) $(LIBS)
	cp PAES_main $(BIN_DIRECTORY)

gGA_main: gGA_main.cpp $(DEPS) 
	$(CPP) gGA_main.cpp ../libjmetal.a -o gGA_main $(INCS) $(LIBS)
	cp gGA_main $(BIN_DIRECTORY)

gGAbin_main: gGAbin_main.cpp $(DEPS) 
	$(CPP) gGAbin_main.cpp ../libjmetal.a -o gGAbin_main $(INCS) $(LIBS)
	cp gGAbin_main $(BIN_DIRECTORY)

DE_main: DE_main.cpp $(DEPS)
	$(CPP) DE_main.cpp ../libjmetal.a -o DE_main $(INCS) $(LIBS)
	cp DE_main $(BIN_DIRECTORY)
	
SMPSO_main: SMPSO_main.cpp $(DEPS)
	$(CPP) SMPSO_main.cpp ../libjmetal.a -o SMPSO_main $(INCS) $(LIBS)
	cp SMPSO_main $(BIN_DIRECTORY)

autodock_main: autodock_main.cpp $(DEPS)
	$(CPP) autodock_main.cpp ../libjmetal.a -o  autodock_main $(INCS) $(LIBS) -pthread
	cp autodock_main $(BIN_DIRECTORY)

#.cpp.o: $(DEPS)
#	$(CPP) $< $(DEPS) -o NSGAII_main $(INCS) $(LIBS)
