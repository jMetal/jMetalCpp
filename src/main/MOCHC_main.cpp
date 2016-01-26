//  NSGAII_main.cpp
//  //
//  //  Author:
//  //       Juanjo
//  //
//  //  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
//  //
//  //  This program is free software: you can redistribute it and/or modify
//  //  it under the terms of the GNU Lesser General Public License as published by
//  //  the Free Software Foundation, either version 3 of the License, or
//  //  (at your option) any later version.
//  //
//  //  This program is distributed in the hope that it will be useful,
//  //  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  //  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  //  GNU Lesser General Public License for more details.
//  //
//  //  You should have received a copy of the GNU Lesser General Public License
//  //  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <Problem.h>
#include <Solution.h>
#include <HUXCrossover.h>
#include <BitFlipMutation.h>
#include <BinaryTournament.h>
#include <iostream>
#include <MOCHC.h>
#include <ProblemFactory.h>
#include <string.h>
#include <time.h>
#include <MOCHC.h>


/**
 * Class implementing the NSGA-II algorithm.
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
  HUXCrossover  * crossover ; // Crossover operator
  BitFlipMutation  * mutation  ; // Mutation operator
  BinaryTournament  * selection ; // Selection operator

  if (argc>=2) {
    problem = ProblemFactory::getProblem(argc, argv);
    cout << "Selected problem: " << problem->getName() << endl;
  } else {
    cout << "No problem selected." << endl;
    cout << "Default problem will be used: Fonseca" << endl;
    problem = ProblemFactory::getProblem(const_cast<char *>("ZDT5"));
  }
  
//  QualityIndicator * indicators ; // Object to get quality indicators
//	indicators = NULL ;

	algorithm = new MOCHC(problem);

  // Algorithm parameters
  int populationSize = 100;
  int maxEvaluations = 25000;
  double initialConvergenceCount = 0.25;
  double preservedPopulation = 0.05;
  int convergenceValue = 3;
  algorithm->setInputParameter("populationSize",&populationSize);
  algorithm->setInputParameter("maxEvaluations",&maxEvaluations);
  algorithm->setInputParameter("initialConvergenceCount",&initialConvergenceCount);
  algorithm->setInputParameter("preservedPopulation",&preservedPopulation);
  algorithm->setInputParameter("convergenceValue",&convergenceValue);

	// Mutation and Crossover for Real codification
	map<string, void *> parameters;

  double crossoverProbability = 1.0;
  double crossoverDistributionIndex = 20.0;
  parameters["probability"] =  &crossoverProbability;
  crossover = new HUXCrossover(parameters);

	parameters.clear();
	 double mutationProbability = 0.35;
	  parameters["probability"] = &mutationProbability;

	  mutation = new BitFlipMutation(parameters);

		// Selection Operator
	parameters.clear();
	selection = new BinaryTournament(parameters);

	// Add the operators to the algorithm
	algorithm->addOperator("crossover",crossover);
	algorithm->addOperator("mutation",mutation);
	algorithm->addOperator("parentSelection",selection);

	// Add the indicator object to the algorithm
//	algorithm->setInputParameter("indicators", indicators) ;

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
  

  delete selection;
  delete mutation;
  delete crossover;
  delete population;
  delete algorithm;

} // main
