CPP  = g++
CC   = gcc

LIBS +=  
#INCS +=  -I. -I../core -I../util -I../util/comparators -I../operators -I../metaheuristics -I../problems \
	-I../encodings/solutionType -I../encodings/variable
INCS +=  -I. -I../core -I../util -I../problems -I../util/comparators \
	-I../encodings/solutionType -I../encodings/variable -I../util/wrapper \
	-I../metaheuristics/nsgaII -I../operators/crossover -I../operators/mutation \
	-I../operators/selection -I../metaheuristics/gGA -I../metaheuristics/ssGA \
	-I../metaheuristics/gde3 -I../metaheuristics/de -I../metaheuristics/smpso \
	-I../metaheuristics/pso -I../util/archive -I../metaheuristics/paes \
	-I../metaheuristics/moead -I../experiments -I../experiments/util \
	-I../experiments/settings -I../qualityIndicator/util -I../qualityIndicator

#EXECS = NSGAII_main PAES_main gGA_main autodock DE_main GDE3_main
#DEPS = ../libjmetal.a ../metaheuristics/libmetaheuristics.a 
EXECS = NSGAII_main NSGAIIbin_main gGA_main gGAbin_main ssGA_main GDE3_main \
	DE_main SMPSO_main PSO_main PAES_main MOEAD_main StandardStudyExecution \
	StandardStudyReportPF StandardStudyReportRF StandardStudyExecutionSO \
	StandardStudyReportSO
WINEXECS = NSGAII_main.exe NSGAIIbin_main.exe NSGAII_main.exe gGA_main.exe \
	gGAbin_main.exe ssGA_main.exe GDE3_main.exe DE_main.exe SMPSO_main.exe \
	PSO_main.exe PAES_main.exe MOEAD_main.exe StandardStudyExecution.exe \
	StandardStudyReportPF.exe StandardStudyReportRF.exe \
	StandardStudyExecutionSO.exe StandardStudyReportSO.exe
DEPS = ../libjmetal.a

BIN_DIRECTORY = ../../bin

#CXXFLAGS += $(INCS) -g 
CXXFLAGS += $(INCS) 

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
	
MOEAD_main: MOEAD_main.cpp $(DEPS)
	$(CPP) MOEAD_main.cpp ../libjmetal.a -o MOEAD_main $(INCS) $(LIBS)
	cp MOEAD_main $(BIN_DIRECTORY)

gGA_main: gGA_main.cpp $(DEPS) 
	$(CPP) gGA_main.cpp ../libjmetal.a -o gGA_main $(INCS) $(LIBS)
	cp gGA_main $(BIN_DIRECTORY)

gGAbin_main: gGAbin_main.cpp $(DEPS) 
	$(CPP) gGAbin_main.cpp ../libjmetal.a -o gGAbin_main $(INCS) $(LIBS)
	cp gGAbin_main $(BIN_DIRECTORY)
	
ssGA_main: ssGA_main.cpp $(DEPS) 
	$(CPP) ssGA_main.cpp ../libjmetal.a -o ssGA_main $(INCS) $(LIBS)
	cp ssGA_main $(BIN_DIRECTORY)

DE_main: DE_main.cpp $(DEPS)
	$(CPP) DE_main.cpp ../libjmetal.a -o DE_main $(INCS) $(LIBS)
	cp DE_main $(BIN_DIRECTORY)
	
SMPSO_main: SMPSO_main.cpp $(DEPS)
	$(CPP) SMPSO_main.cpp ../libjmetal.a -o SMPSO_main $(INCS) $(LIBS)
	cp SMPSO_main $(BIN_DIRECTORY)

PSO_main: PSO_main.cpp $(DEPS)
	$(CPP) PSO_main.cpp ../libjmetal.a -o PSO_main $(INCS) $(LIBS)
	cp PSO_main $(BIN_DIRECTORY)
	
#NSGAIIStudy: ../experiments/NSGAIIStudy.cpp $(DEPS)
#	$(CPP) ../experiments/NSGAIIStudy.cpp ../libjmetal.a -o NSGAIIStudy $(INCS) $(LIBS)
#	cp NSGAIIStudy $(BIN_DIRECTORY)

StandardStudyExecution: ../experiments/StandardStudyExecution.cpp $(DEPS)
	$(CPP) ../experiments/StandardStudyExecution.cpp ../libjmetal.a -o StandardStudyExecution $(INCS) $(LIBS)
	cp StandardStudyExecution $(BIN_DIRECTORY)
	
StandardStudyReportPF: ../experiments/StandardStudyReportPF.cpp $(DEPS)
	$(CPP) ../experiments/StandardStudyReportPF.cpp ../libjmetal.a -o StandardStudyReportPF $(INCS) $(LIBS)
	cp StandardStudyReportPF $(BIN_DIRECTORY)
	
StandardStudyReportRF: ../experiments/StandardStudyReportRF.cpp $(DEPS)
	$(CPP) ../experiments/StandardStudyReportRF.cpp ../libjmetal.a -o StandardStudyReportRF $(INCS) $(LIBS)
	cp StandardStudyReportRF $(BIN_DIRECTORY)
	
StandardStudyExecutionSO: ../experiments/StandardStudyExecutionSO.cpp $(DEPS)
	$(CPP) ../experiments/StandardStudyExecutionSO.cpp ../libjmetal.a -o StandardStudyExecutionSO $(INCS) $(LIBS)
	cp StandardStudyExecutionSO $(BIN_DIRECTORY)
	
StandardStudyReportSO: ../experiments/StandardStudyReportSO.cpp $(DEPS)
	$(CPP) ../experiments/StandardStudyReportSO.cpp ../libjmetal.a -o StandardStudyReportSO $(INCS) $(LIBS)
	cp StandardStudyReportSO $(BIN_DIRECTORY)

#.cpp.o: $(DEPS)
#	$(CPP) $< $(DEPS) -o NSGAII_main $(INCS) $(LIBS)
