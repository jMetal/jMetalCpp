/*
 * GARunner.h
 *
 *  Created on: 5 Nov 2018
 *      Author: Emad Alharbi
 */

#ifndef SRC_BUCCANEER_GARUNNER_H_
#define SRC_BUCCANEER_GARUNNER_H_
#include <JMetalInc/Problem.h>
#include <JMetalInc/Algorithm.h>
#include <JMetalInc/Solution.h>
#include <JMetalInc/BinaryTournament2.h>
#include <JMetalInc/BitFlipMutation.h>
#include <JMetalInc/SinglePointCrossover.h>
#include <iostream>
#include <JMetalInc/gGA.h>
#include <JMetalInc/SBXCrossover.h>
#include <JMetalInc/PolynomialMutation.h>
#include <JMetalInc/DifferentialEvolutionCrossover.h>
#include <JMetalInc/Operator.h>
#include <clipper/clipper-ccp4.h>
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
#include <JMetalInc/PositionBasedCrossover.h>
#include <JMetalInc/OrderCrossover.h>
#include <JMetalInc/InsertionMutation.h>
#include <JMetalInc/InversionMutation.h>
//namespace GARunner {

class GARunner {
public:

	//GARunner(Problem * probelm);
	GARunner(Problem * probelm , int population , int Evaluations , double crossoverProbability, double distributionIndexValue1 , double mutationProbability, double distributionIndexValue2, std::string crossovertype, std::string mutationtype , std::string selectiontype) ;

	virtual ~GARunner();
	SolutionSet * Binary();
	SolutionSet * RealNumbers();


	Algorithm * algorithm ; // The algorithm to use
	Operator  * crossover ; // Crossover operator
	Operator  * mutation  ; // Mutation operator
	Operator  * selection ; // Selection operator
	int populationSizeValue;
	int maxEvaluationsValue;



private:
	Problem * ProbelmToSolve;
	Operator * crossoverType(std::string type , map<string, void *> parameters );
	Operator * mutationType(std::string type , map<string, void *> parameters);
	Operator * selectionType(std::string type , map<string, void *> parameters);
};

//} /* namespace Balls */

#endif /* SRC_BUCCANEER_GARUNNER_H_ */
