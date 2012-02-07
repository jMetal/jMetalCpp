/**
 * @file SMPSO_main.cpp
 * @author Esteban López
 * @date 18 January 2012
**/

#include <Problem.h>
#include <Algorithm.h>
#include <Solution.h>
#include <Operator.h>
//#include <QualityIndicator.h>
#include <ProblemFactory.h>
#include <SMPSO.h>
#include <PolynomialMutation.h>
#include <iostream>
#include <time.h>

/**
 * This main executes the SMPSO algorithm described in:
 * A.J. Nebro, J.J. Durillo, J. Garcia-Nieto, C.A. Coello Coello, F. Luna and E. Alba
 * "SMPSO: A New PSO-based Metaheuristic for Multi-objective Optimization".
 * IEEE Symposium on Computational Intelligence in Multicriteria Decision-Making
 * (MCDM 2009), pp: 66-73. March 2009
 */

int main(int argc, char ** argv) {

  clock_t t_ini, t_fin;

  Problem   * problem;   // The problem to solve
  Algorithm * algorithm; // The algorithm to use
  Operator  * mutation;  // "Turbulence" operator

  map<string, void *> parameters; // Operator parameters

  //TODO: QualityIndicator * indicators; // Object to get quality indicators

  if (argc>=2) {
    problem = ProblemFactory::getProblem(argc, argv);
  } else {
    cout << "No problem selected." << endl;
    cout << "Default problem will be used: Kursawe" << endl;
		// char * defaultProblem;
		// strcpy(defaultProblem, "Kursawe");
    problem = ProblemFactory::getProblem("Kursawe");
  }

  cout << "SMPSO_main: Number of objectives: " << problem->getNumberOfObjectives() << endl;
  cout << "SMPSO_main: Problem: " << problem->getName() << endl;

  algorithm = new SMPSO(problem);

  cout << "SMPSO_main: SMPSO algorithm initialized." << endl;

  // Algorithm parameters
  int swarmSizeValue = 100;
  int archiveSizeValue = 100;
  int maxIterationsValue = 250;
  algorithm->setInputParameter("swarmSize",&swarmSizeValue);
  algorithm->setInputParameter("archiveSize",&archiveSizeValue);
  algorithm->setInputParameter("maxIterations",&maxIterationsValue);

  // Mutation operator
  double probabilityParameter = 1.0/(problem->getNumberOfVariables());
  double distributionIndexParameter = 20.0;
  parameters["probability"] =  &probabilityParameter;
  parameters["distributionIndex"] = &distributionIndexParameter;
  mutation = new PolynomialMutation(parameters);

  // Add the operators to the algorithm
  algorithm->addOperator("mutation",mutation);

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

  delete mutation;
  delete population;
  delete algorithm;

} // main
