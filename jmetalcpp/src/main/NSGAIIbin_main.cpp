/**
 * @file NSGAIIbin_main.cpp
 * @author Antonio J. Nebrp
 * @date 15 December 2011
**/


#include <Problem.h>
#include <Solution.h>
#include <ZDT5.h>
#include <OneMax.h>
#include <RealSolutionType.h>
#include <SinglePointCrossover.h>
#include <BitFlipMutation.h>
#include <BinaryTournament2.h>
#include <iostream>
#include <NSGAII.h>
#include <time.h>


/**
 * Class implementing the NSGA-II algorithm -> binary encoding version
 */
int main(int argc, char ** argv) {

	clock_t t_ini, t_fin;

  Problem   * problem   ; // The problem to solve
  Algorithm * algorithm ; // The algorithm to use
  Operator  * crossover ; // Crossover operator
  Operator  * mutation  ; // Mutation operator
  Operator  * selection ; // Selection operator

	//problem = new ZDT5("Binary");
	problem = new OneMax(200,2);

	cout << "El numero de objetivos es " << problem->getNumberOfObjectives() << endl;


	algorithm = new NSGAII(problem);

	cout << "Algoritmo NGSAII inicializado." << endl;

	// Algorithm parameters
	int populationSizeValue = 100;
	int *populationSizePtr = &populationSizeValue;
	int maxEvaluationsValue = 25000;
	int *maxEvaluationsPtr = &maxEvaluationsValue;
	algorithm->setInputParameter("populationSize",populationSizePtr);
	algorithm->setInputParameter("maxEvaluations",maxEvaluationsPtr);

	map<string, void *> parameters;

	// Mutation operator
	parameters.clear();
	double mutationProbability = 1.0/problem->getNumberOfBits();
	parameters["probability"] = &mutationProbability;
	mutation = new BitFlipMutation(parameters);

	// Crossover operator
	parameters.clear();
	double crossoverProbability = 0.9;
	parameters["probability"] = &crossoverProbability;
	crossover = new SinglePointCrossover(parameters);

	// Selection Operator
	parameters.clear();
	selection = new BinaryTournament2(parameters) ;

	cout << "Adding operators..." << endl;

	// Add the operators to the algorithm
	algorithm->addOperator("crossover",crossover);
	algorithm->addOperator("mutation",mutation);
	algorithm->addOperator("selection",selection);

	// Execute the Algorithm

	t_ini = clock();
	SolutionSet * population = algorithm->execute();
	t_fin = clock();
	double secs = (double) (t_fin - t_ini);

	// Result messages
	cout << "Total execution time: " << secs << "s" << endl;
	cout << "Variables values have been writen to file VAR" << endl;
	population->printVariablesToFile("VAR");
	cout << "Objectives values have been writen to file FUN" << endl;
	population->printObjectivesToFile("FUN");
} // main

