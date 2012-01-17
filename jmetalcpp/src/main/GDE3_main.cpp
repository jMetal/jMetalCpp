/**
 * @file GDE3_main.cpp
 * @author Esteban López
 * @date 16 January 2012
**/

#include <Problem.h>
#include <Algorithm.h>
#include <Solution.h>
#include <Operator.h>
//#include <QualityIndicator.h>
#include <GDE3.h>
#include <Kursawe.h>
#include <DifferentialEvolutionCrossover.h>
#include <DifferentialEvolutionSelection.h>
#include <iostream>
#include <time.h>

int main(int argc, char ** argv) {

  clock_t t_ini, t_fin;

  Problem   * problem   ; // The problem to solve
  Algorithm * algorithm ; // The algorithm to use
  Operator  * crossover ; // Crossover operator
  Operator  * selection ; // Selection operator

  map<string, void *> parameters;

  //TODO: QualityIndicator * indicators;

  problem = new Kursawe("Real", 3);
  //problem = new Water("Real");
  //problem = new ZDT1("ArrayReal", 100);
  //problem = new ConstrEx("Real");
  //problem = new DTLZ1("Real");
  //problem = new OKA2("Real") ;

  cout << "GDE3_main: El numero de objetivos es " << problem->getNumberOfObjectives() << endl;
  cout << "GDE3_main: Problema: " << problem->getName() << endl;

  algorithm = new GDE3(problem);

  cout << "GDE3_main: Algoritmo GDE3 inicializado." << endl;

  // Algorithm parameters
  int populationSizeValue = 100;
  int *populationSizePtr = &populationSizeValue;
  int maxIterationsValue = 250;
  int *maxIterationsPtr = &maxIterationsValue;
  algorithm->setInputParameter("populationSize",populationSizePtr);
  algorithm->setInputParameter("maxIterations",maxIterationsPtr);

  // Crossover operator
  double crParameter = 0.5;
  double fParameter  = 0.5;
  parameters["CR"] =  &crParameter;
  parameters["F"] = &fParameter;
  crossover = new DifferentialEvolutionCrossover(parameters);

  // Selection operator
  parameters.clear();
  selection = new DifferentialEvolutionSelection(parameters) ;

  // Add the operators to the algorithm
  algorithm->addOperator("crossover",crossover);
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
