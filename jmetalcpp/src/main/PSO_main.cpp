/**
 * @file PSO_mais.cpp
 * @author Esteban López Camacho
 * @date 23 January 2012
**/

#include <Problem.h>
#include <Algorithm.h>
#include <Solution.h>
#include <iostream>
#include <PSO.h>
#include <time.h>
#include <PolynomialMutation.h>
#include <ProblemFactory.h>

int main(int argc, char ** argv) {

  clock_t t_ini, t_fin;

  Problem   * problem   ; // The problem to solve
  Algorithm * algorithm ; // The algorithm to use
  Operator  * mutation  ; // Mutation operator

  if (argc>=2) {
    problem = ProblemFactory::getProblem(argc, argv);
  } else {
    cout << "No problem selected." << endl;
    cout << "Default problem will be used: Sphere" << endl;
//    char * defaultProblem;
//    strcpy(defaultProblem, "Fonseca");
    problem = ProblemFactory::getProblem("Sphere");
    //problem = new Sphere("Real", 20);
  }

  algorithm = new PSO(problem);

  cout << "PSO algorithm initialized." << endl;

  // Algorithm parameters
  int swarmSize = 50;
  int maxIterations = 5000;
  algorithm->setInputParameter("swarmSize",&swarmSize);
  algorithm->setInputParameter("maxIterations",&maxIterations);

  // Mutation operator
  map<string, void *> parameters;
  double probability = 1.0/problem->getNumberOfVariables();
  double distributionIndex = 20.0;
  parameters["probability"] = &probability;
  parameters["distributionIndex"] = &distributionIndex;
  mutation = new PolynomialMutation(parameters);

  // Add the operators to the algorithm
  algorithm->addOperator("mutation",mutation);

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

  delete mutation;
  delete population;
  delete algorithm;

} // main
