/**
 * @file DE_main.cpp
 * @author Esteban López
 * @date 17 January 2012
**/

#include <Problem.h>
#include <Algorithm.h>
#include <Solution.h>
#include <Operator.h>
//#include <QualityIndicator.h>
#include <DE.h>
#include <Sphere.h>
#include <DifferentialEvolutionCrossover.h>
#include <DifferentialEvolutionSelection.h>
#include <iostream>
#include <time.h>

int main(int argc, char ** argv) {

  clock_t t_ini, t_fin;

  Problem   * problem   ; // The problem to solve
  Algorithm * algorithm ; // The algorithm to use
  Operator  * crossover ; // Crossover operator
  Operator  * mutation  ; // Mutation operator
  Operator  * selection ; // Selection operator

  map<string, void *> parameters;

  //TODO: QualityIndicator * indicators;

  problem = new Sphere("Real", 20);
  //problem = new Easom("Real");
  //problem = new Griewank("Real", 10);

  cout << "DE_main: El numero de objetivos es " << problem->getNumberOfObjectives() << endl;
  cout << "DE_main: Problema: " << problem->getName() << endl;

  algorithm = new DE(problem);

  cout << "DE_main: Algoritmo DE inicializado." << endl;

  // Algorithm parameters
  int populationSizeValue = 100;
  int maxEvaluationsValue = 1000000;
  algorithm->setInputParameter("populationSize",&populationSizeValue);
  algorithm->setInputParameter("maxEvaluations",&maxEvaluationsValue);

  // Crossover operator
  double crParameter = 0.5;
  double fParameter  = 0.5;
  parameters["CR"] =  &crParameter;
  parameters["F"] = &fParameter;
  string deVariantParameter = "rand/1/bin";
  parameters["DE_VARIANT"] = &deVariantParameter;
  crossover = new DifferentialEvolutionCrossover(parameters);

  // Selection operator
  parameters.clear();
  selection = new DifferentialEvolutionSelection(parameters) ;

  // Add the operators to the algorithm
  algorithm->addOperator("crossover",crossover);
  algorithm->addOperator("selection",selection);

  // Add the indicator object to the algorithm
  //algorithm->setInputParameter("indicators", indicators);

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

  delete crossover;
  delete selection;
  delete population;
  delete algorithm;

} // main
