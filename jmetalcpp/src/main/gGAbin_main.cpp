/**
 * @file gGAbin_main.cpp
 * @author Antonio J. Nebro
 * @date 02 December 2011
**/


#include <Problem.h>
#include <Algorithm.h>
#include <Solution.h>
#include <BinarySolutionType.h>
#include <BinaryTournament2.h>
#include <BitFlipMutation.h>
#include <SinglePointCrossover.h>
#include <iostream>
#include <OneMax.h>
#include <gGA.h>
#include <time.h>

int main(int argc, char ** argv) {

	clock_t t_ini, t_fin;

  Problem   * problem   ; // The problem to solve
  Algorithm * algorithm ; // The algorithm to use
  Operator  * crossover ; // Crossover operator
  Operator  * mutation  ; // Mutation operator
  Operator  * selection ; // Selection operator

  int bits = 200 ;
	problem = new OneMax(bits, 2);

	cout << "El numero de objetivos es " << problem->getNumberOfObjectives() << endl;
	cout << "Problema: " << problem->getName() << endl;

	algorithm = new gGA(problem);

	cout << "Algoritmo gGA inicializado." << endl;

	// Algorithm parameters
	int populationSizeValue = 100;
	int *populationSizePtr = &populationSizeValue;
	int maxEvaluationsValue = 25000;
	int *maxEvaluationsPtr = &maxEvaluationsValue;
	algorithm->setInputParameter("populationSize",populationSizePtr);
	algorithm->setInputParameter("maxEvaluations",maxEvaluationsPtr);

	map<string, void *> parameters;

	parameters.clear();
	double mutationProbability = 1.0/problem->getNumberOfBits();
	parameters["probability"] = &mutationProbability;
	mutation = new BitFlipMutation(parameters);

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
