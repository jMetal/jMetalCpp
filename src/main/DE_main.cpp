//  DE_main.cpp
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
#include <DE.h>
#include <ProblemFactory.h>
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

  if (argc>=2) {
    problem = ProblemFactory::getProblem(argc, argv);
    cout << "Selected problem: " << problem->getName() << endl;
  } else {
    cout << "No problem selected." << endl;
    cout << "Default problem will be used: Sphere" << endl;
    problem = ProblemFactory::getProblem(const_cast<char *>("Sphere"));
  }

  algorithm = new DE(problem);

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
  secs = secs / CLOCKS_PER_SEC;

  // Result messages
  cout << "Total execution time: " << secs << "s" << endl;
  cout << "Variables values have been written to file VAR" << endl;
  population->printVariablesToFile("VAR");
  cout << "Objectives values have been written to file FUN" << endl;
  population->printObjectivesToFile("FUN");

  delete crossover;
  delete selection;
  delete population;
  delete algorithm;

} // main
