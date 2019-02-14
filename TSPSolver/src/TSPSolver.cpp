//============================================================================
// Name        : TSPSolver.cpp
// Author      : Emad Alharbi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
// TSP.cpp : Defines the entry point for the console application.
//


#include "math.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <JMetalInc/Problem.h>
#include <JMetalInc/Algorithm.h>
#include <JMetalInc/Solution.h>
#include <JMetalInc/BinaryTournament2.h>
#include <JMetalInc/BitFlipMutation.h>
#include <JMetalInc/SinglePointCrossover.h>

#include <JMetalInc/gGA.h>
#include <JMetalInc/SBXCrossover.h>
#include <JMetalInc/PolynomialMutation.h>
#include <JMetalInc/DifferentialEvolutionCrossover.h>
#include <JMetalInc/Operator.h>

#include <JMetalInc/HUXCrossover.h>
#include <JMetalInc/SinglePointCrossover.h>
#include <JMetalInc/NonUniformMutation.h>
#include <JMetalInc/UniformMutation.h>
#include <JMetalInc/BestSolutionSelection.h>
#include <JMetalInc/BinaryTournament.h>
#include <JMetalInc/BinaryTournament2.h>
#include <JMetalInc/DifferentialEvolutionSelection.h>
#include <JMetalInc/RandomSelection.h>
#include <JMetalInc/WorstSolutionSelection.h>
#include <JMetalInc/RandomGenerator.h>
#include "TSPProblem.h"

#include <JMetalInc/InversionMutation.h>

#include <JMetalInc/InsertionMutation.h>
#include <JMetalInc/PositionBasedCrossover.h>
#include "GARunner.h"
#include "Optimizer.h"

#include <JMetalInc/OXCrossover.h>
using namespace std;


int main()
{



	//TSPProblem *tsp = new TSPProblem();
   //GARunner *GA= new GARunner(tsp,100,25000,0.9,0,0.2,0,"OCCrossover","BitFlipMutation","BinaryTournament2");
 // SolutionSet * population = GA->RealNumbers();
  //  population->printObjectives();



	Optimizer *op = new Optimizer();
	op->AddMBall("Crossover","OXCrossover");
	op->AddMBall("Crossover","PositionBasedCrossover");

	op->AddMBall("Mutation","InsertionMutation");
	op->AddMBall("Mutation","InversionMutation");
/*
	op->AddMBall("Population","100");
	op->AddMBall("Evaluation","200");
	op->AddMBall("Population","200");
	op->AddMBall("Population","300");
	op->AddMBall("Population","400");
	op->AddMBall("Population","500");
	op->AddMBall("Population","600");
	op->AddMBall("Population","700");
	op->AddMBall("Population","800");
	op->AddMBall("Population","900");
	op->AddMBall("Population","1000");
	op->AddMBall("Evaluation","300");
	op->AddMBall("Evaluation","400");
	op->AddMBall("Evaluation","500");
	op->AddMBall("Evaluation","600");
	op->AddMBall("Evaluation","700");
	op->AddMBall("Evaluation","800");
	op->AddMBall("Evaluation","900");
	op->AddMBall("Evaluation","1000");
	//op->AddMBall("Evaluation","5000");

*/

	for(int i=0; i<2000000;i=i+5000){

		op->AddMBall("Evaluation",std::to_string(i));
	}
	for(int i=100; i<10000;i=i+100){
			op->AddMBall("Population",std::to_string(i));
	}

	op->AddMBall("crossoverProbability","0.9");
	op->AddMBall("mutationProbability","0.2");
	op->AddMBall("Selection","BinaryTournament2");
	try
	    {
		op->Optimize(6,10000);
	    }
	    catch (std::exception const &exc)
	    {
	        std::cerr << "Exception caught " << exc.what() << "\n";
	    }
	    catch (...)
	    {
	        std::cerr << "Unknown exception caught\n";
	    }

	//op->CreateContainer();


	return 0;
}




