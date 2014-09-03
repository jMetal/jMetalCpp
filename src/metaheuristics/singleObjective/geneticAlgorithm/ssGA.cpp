//  ssGA.cpp
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


#include <ssGA.h>


/**
 * Class implementing a steady-state genetic algorithm
 */


/**
 * Constructor
 * Create a new SSGA instance.
 * @param problem Problem to solve
 */
ssGA::ssGA(Problem *problem) : Algorithm(problem) {
} // ssGA


/*
 * Execute the SSGA algorithm
 */
SolutionSet * ssGA::execute() {

  int populationSize;
  int maxEvaluations;
  int evaluations;

  SolutionSet * population;

  Operator * mutationOperator;
  Operator * crossoverOperator;
  Operator * selectionOperator;

  Comparator * comparator = new ObjectiveComparator(0); // Single objective comparator

  Operator * findWorstSolution;
  map<string, void *> parameters; // Operator parameters
  parameters["comparator"] = comparator;

  findWorstSolution = new WorstSolutionSelection(parameters) ;

  //Read the parameters
  populationSize = *(int *) getInputParameter("populationSize");
  maxEvaluations = *(int *) getInputParameter("maxEvaluations");

  //Initialize the variables
  population = new SolutionSet(populationSize);
  evaluations = 0;

  //Read the operators
  mutationOperator = operators_["mutation"];
  crossoverOperator = operators_["crossover"];
  selectionOperator = operators_["selection"];

  // Create the initial population
  Solution * newIndividual;
  for (int i = 0; i < populationSize; i++) {
    newIndividual = new Solution(problem_);
    problem_->evaluate(newIndividual);
    evaluations++;
    population->add(newIndividual);
  } // for

  // main loop
  while (evaluations < maxEvaluations) {
    Solution ** parents = new Solution*[2];

    // Selection
    parents[0] = (Solution*)selectionOperator->execute(population);
    parents[1] = (Solution*)selectionOperator->execute(population);

    // Crossover
    Solution ** offspring = (Solution **) crossoverOperator->execute(parents);

    // Mutation
    mutationOperator->execute(offspring[0]);

    // Evaluation of the new individual
    problem_->evaluate(offspring[0]);

    evaluations ++;

    // Replacement: replace the last individual is the new one is better
    int * worstIndividualPtr = (int *) findWorstSolution->execute(population);
    int worstIndividual = *worstIndividualPtr;
    delete worstIndividualPtr;

    if (comparator->compare(population->get(worstIndividual), offspring[0]) > 0) {
      delete population->get(worstIndividual);
      population->remove(worstIndividual);
      population->add(new Solution(offspring[0]));
    } // if

    delete offspring[0];
    delete offspring[1];
    delete [] offspring;
    delete [] parents;

  } // while

  // Return a population with the best individual

  SolutionSet * resultPopulation  = new SolutionSet(1);
  resultPopulation->add(new Solution(population->best(comparator)));

  delete population;
  delete comparator;
  delete findWorstSolution;

  return resultPopulation;
} // execute
