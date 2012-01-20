/**
 * @file NSGAIIFactory_main.cpp
 * @author Esteban López
 * @date 20 January 2011
**/


#include <Problem.h>
#include <Solution.h>
#include <SBXCrossover.h>
#include <PolynomialMutation.h>
#include <BinaryTournament2.h>
#include <iostream>
#include <NSGAII.h>
#include <ProblemFactory.h>
#include <string.h>
#include <time.h>


/**
 * Class implementing the NSGA-II algorithm
 *    (Version using a problem factory)
 * This implementation of NSGA-II makes use of a QualityIndicator object
 *  to obtained the convergence speed of the algorithm. This version is used
 *  in the paper:
 *     A.J. Nebro, J.J. Durillo, C.A. Coello Coello, F. Luna, E. Alba
 *     "A Study of Convergence Speed in Multi-Objective Metaheuristics."
 *     To be presented in: PPSN'08. Dortmund. September 2008.
 *
 *   Besides the classic NSGA-II, a steady-state version (ssNSGAII) is also
 *   included (See: J.J. Durillo, A.J. Nebro, F. Luna and E. Alba
 *                  "On the Effect of the Steady-State Selection Scheme in
 *                  Multi-Objective Genetic Algorithms"
 *                  5th International Conference, EMO 2009, pp: 183-197.
 *                  April 2009)
 */
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
    cout << "Default problem will be used: Fonseca" << endl;
//    char * defaultProblem;
//    strcpy(defaultProblem, "Fonseca");
    problem = ProblemFactory::getProblem("Fonseca");
  }

  //TODO: Quality Indicators
  //QualityIndicator indicators ; // Object to get quality indicators
  //indicators = null ;

  cout << "Problema: " << problem->getName() << endl;
  cout << "El numero de objetivos es " << problem->getNumberOfObjectives() << endl;
  cout << "El numero de variables es " << problem->getNumberOfVariables() << endl;

  system("pause");

  algorithm = new NSGAII(problem);

  cout << "Algoritmo NGSAII inicializado." << endl;

  // Algorithm parameters
  int populationSizeValue = 100;
  int *populationSizePtr = &populationSizeValue;
  int maxEvaluationsValue = 25000;
  int *maxEvaluationsPtr = &maxEvaluationsValue;
  algorithm->setInputParameter("populationSize",populationSizePtr);
  algorithm->setInputParameter("maxEvaluations",maxEvaluationsPtr);

  // Mutation and Crossover for Real codification
  map<string, void *> parameters;
  double probabilityValue1 = 0.9;
  double *probabilityPtr1 = &probabilityValue1;
  double distributionIndexValue1 = 20.0;
  double *distributionIndexPtr1 = &distributionIndexValue1;
  parameters["probability"] =  probabilityPtr1 ;
  parameters["distributionIndex"] = distributionIndexPtr1 ;
  crossover = new SBXCrossover(parameters);

  parameters.clear();
  double probabilityValue2 = 1.0/problem->getNumberOfVariables();
  double *probabilityPtr2 = &probabilityValue2;
  double distributionIndexValue2 = 20.0;
  double *distributionIndexPtr2 = &distributionIndexValue2;
  parameters["probability"] = probabilityPtr2;
  parameters["distributionIndex"] = distributionIndexPtr2 ;
  mutation = new PolynomialMutation(parameters);

  // Selection Operator
  parameters.clear();
  selection = new BinaryTournament2(parameters) ;

  cout << "Adding operators..." << endl;

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

