//  SMPSO_main.cpp
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//
//  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
    cout << "Selected problem: " << problem->getName() << endl;
  } else {
    cout << "No problem selected." << endl;
    cout << "Default problem will be used: Kursawe" << endl;
    problem = ProblemFactory::getProblem(const_cast<char *>("Kursawe"));
  }

  algorithm = new SMPSO(problem);

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
  secs = secs / CLOCKS_PER_SEC;

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
