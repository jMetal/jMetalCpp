//  SMPSOhv_main.cpp
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//
//  Copyright (c) 2014 Antonio J. Nebro
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

#include <Algorithm.h>
#include <Problem.h>
#include <Operator.h>
#include <Solution.h>

#include <SMPSOhv.h>

#include <Mutation.h>
#include <PolynomialMutation.h>
#include <ProblemFactory.h>
#include <QualityIndicator.h>

#include <iostream>
#include <time.h>

/**
 * This method executes the SMPSOhv algorithm described in:
 * Antonio J. Nebro, Juan José Durillo, Carlos Artemio Coello Coello:
 * Analysis of leader selection strategies in a multi-objective Particle Swarm Optimizer.
 * IEEE Congress on Evolutionary Computation 2013: 3153-3160
 */

int main(int argc, char ** argv) {

  clock_t t_ini, t_fin;

  Problem   *problem;   // The problem to solve
  Algorithm *algorithm; // The algorithm to use
  Mutation  *mutation;

  QualityIndicator *indicators ; // Object to get quality indicators

  map<string, void *> parameters; // Operator parameters

  indicators = NULL;

  if (argc>=2) {
    problem = ProblemFactory::getProblem(argc, argv);
    cout << "Selected problem: " << problem->getName() << endl;
  } else {
    cout << "No problem selected." << endl;
    cout << "Default problem will be used: Kursawe" << endl;
    problem = ProblemFactory::getProblem(const_cast<char *>("Kursawe"));
  }

  algorithm = new SMPSOhv(problem);

  int maxIterations = 250;
  int swarmSize = 100;
  int archiveSize = 100;

  double distributionIndex = 20.0;
  double mutationProbability = 1.0/problem->getNumberOfVariables();

  // Algorithm parameters
  algorithm->setInputParameter("swarmSize",&swarmSize);
  algorithm->setInputParameter("archiveSize",&archiveSize);
  algorithm->setInputParameter("maxIterations",&maxIterations);

  parameters["probability"] =  &mutationProbability;
  parameters["distributionIndex"] = &distributionIndex;
  mutation = new PolynomialMutation(parameters);

  // Add the operators to the algorithm
  algorithm->addOperator("mutation",mutation);

  // Execute the Algorithm
  t_ini = clock();
  SolutionSet * population = algorithm->execute();
  t_fin = clock();
  double secs = (double) (t_fin - t_ini);
  secs = secs / CLOCKS_PER_SEC;

  // Print the results
  cout << "Total execution time: " << secs << "s" << endl;
  cout << "Variables values have been written to file VAR" << endl;
  population->printVariablesToFile("VAR");
  cout << "Objectives values have been written to file FUN" << endl;
  population->printObjectivesToFile("FUN");

  if (indicators != NULL) {
    cout << "Quality indicators" << endl ;
    cout << "Hypervolume: " << indicators->getHypervolume(population) << endl;
    cout << "GD         : " << indicators->getGD(population) << endl ;
    cout << "IGD        : " << indicators->getIGD(population) << endl ;
    cout << "Spread     : " << indicators->getSpread(population) << endl ;
    cout << "Epsilon    : " << indicators->getEpsilon(population) << endl ;
  } // if

  delete mutation;
  delete population;
  delete algorithm;

} // main
