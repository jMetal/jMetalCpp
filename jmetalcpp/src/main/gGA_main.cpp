/**
 * @file gGA_main.cpp
 * @author Antonio J. Nebro
 * @date 02 December 2011
**/

#include <Problem.h>
#include <Algorithm.h>
#include <Solution.h>
#include <SBXCrossover.h>
#include <PolynomialMutation.h>
#include <BinaryTournament2.h>
#include <ProblemFactory.h>
#include <iostream>
#include <gGA.h>
#include <time.h>

int main(int argc, char ** argv) {

	clock_t t_ini, t_fin;

  Problem   * problem   ; // The problem to solve
  Algorithm * algorithm ; // The algorithm to use
  Operator  * crossover ; // Crossover operator
  Operator  * mutation  ; // Mutation operator
  Operator  * selection ; // Selection operator

  if (argc>=2) {
    problem = ProblemFactory::getProblem(argc, argv);
  } else {
    // char * defaultProblem;
    // strcpy(defaultProblem, "Sphere");
    cout << "No problem selected." << endl;
    cout << "Default problem will be used: Sphere" << endl;
    problem = ProblemFactory::getProblem("Sphere");
  }

	algorithm = new gGA(problem);

	cout << "Generational genetic algorithm initialized." << endl;

	// Algorithm parameters
  int populationSizeValue = 100;
  int maxEvaluationsValue = 250000;
  algorithm->setInputParameter("populationSize",&populationSizeValue);
  algorithm->setInputParameter("maxEvaluations",&maxEvaluationsValue);

	// Mutation and Crossover for Real codification
  map<string, void *> parameters;
  double crossoverProbability = 0.9;
  double distributionIndexValue1 = 20.0;
  parameters["probability"] =  &crossoverProbability ;
  parameters["distributionIndex"] = &distributionIndexValue1 ;
  crossover = new SBXCrossover(parameters);

	parameters.clear();
  double mutationProbability = 1.0/problem->getNumberOfVariables();
  double distributionIndexValue2 = 20.0;
  parameters["probability"] = &mutationProbability;
  parameters["distributionIndex"] = &distributionIndexValue2 ;
  mutation = new PolynomialMutation(parameters);

	// Selection Operator
	parameters.clear();
	selection = new BinaryTournament2(parameters) ;

	// Add the operators to the algorithm
	algorithm->addOperator("crossover",crossover);
	algorithm->addOperator("mutation",mutation);
	algorithm->addOperator("selection",selection);

	// Add the indicator object to the algorithm
	//algorithm->setInputParameter("indicators", indicators) ;

	// Execute the Algorithm
	t_ini = clock();
	SolutionSet * population = algorithm->execute();
	t_fin = clock();
	double secs = (double) (t_fin - t_ini);

	// Result messages
	cout << "Total execution time: " << secs << "s" << endl;
	cout << "Variables values have been written to file VAR" << endl;
	population->printVariablesToFile("VAR");
	cout << "Objectives values have been written to file FUN" << endl;
	population->printObjectivesToFile("FUN");

  delete crossover;
  delete mutation;
  delete selection;
  delete population;
  delete algorithm;

} // main
