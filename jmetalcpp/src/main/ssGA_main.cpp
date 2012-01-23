/**
 * @file ssGA_main.cpp
 * @author Esteban López Camacho
 * @date 20 January 2011
**/

#include <Problem.h>
#include <Algorithm.h>
#include <Solution.h>
#include <RealSolutionType.h>
#include <SBXCrossover.h>
#include <PolynomialMutation.h>
#include <BinaryTournament2.h>
#include <iostream>
#include <ssGA.h>
#include <time.h>
#include <ProblemFactory.h>

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
    cout << "No problem selected." << endl;
    cout << "Default problem will be used: Sphere" << endl;
//    char * defaultProblem;
//    strcpy(defaultProblem, "Fonseca");
    problem = ProblemFactory::getProblem("Sphere");
  }


  //algorithm = new gGA(problem) ; // Generational GA
  algorithm = new ssGA(problem); // Steady-state GA
  //algorithm = new scGA(problem) ; // Synchronous cGA
  //algorithm = new acGA(problem) ;   // Asynchronous cGA

  cout << "Algoritmo ssGA inicializado." << endl;
  system("pause");

  // Algorithm parameters
  int populationSize = 100;
  int maxEvaluations = 250000;
  algorithm->setInputParameter("populationSize",&populationSize);
  algorithm->setInputParameter("maxEvaluations",&maxEvaluations);

  // Mutation and Crossover for Real codification
  map<string, void *> parameters;
  double crossoverProbability = 0.9;
  double distributionIndex1 = 20.0;
  parameters["probability"] =  &crossoverProbability ;
  parameters["distributionIndex"] = &distributionIndex1 ;
  crossover = new SBXCrossover(parameters);

  parameters.clear();
  double mutationProbability = 1.0/problem->getNumberOfVariables();
  double distributionIndex2 = 20.0;
  parameters["probability"] = &mutationProbability;
  parameters["distributionIndex"] = &distributionIndex2 ;
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
  cout << "Variables values have been writen to file VAR" << endl;
  population->printVariablesToFile("VAR");
  cout << "Objectives values have been writen to file FUN" << endl;
  population->printObjectivesToFile("FUN");
} // main
