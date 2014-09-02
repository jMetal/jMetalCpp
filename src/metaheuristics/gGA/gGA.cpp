//  gGA.cpp
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
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

#include <gGA.h>

/*
 * This class implements the NSGA-II algorithm.
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
gGA::gGA(Problem *problem) : Algorithm(problem) {
} // gGA


/*
 * Runs the NSGA-II algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet * gGA::execute() {

  int populationSize;
  int maxEvaluations;
  int evaluations;

  SolutionSet * population;
  SolutionSet * offspringPopulation;

  Operator * mutationOperator;
  Operator * crossoverOperator;
  Operator * selectionOperator;

  Comparator * comparator = new ObjectiveComparator(0) ;

  //Read the parameters
  populationSize = *(int *) getInputParameter("populationSize");
  maxEvaluations = *(int *) getInputParameter("maxEvaluations");
  // TODO: indicators = (QualityIndicator) getInputParameter("indicators");
//  cout << "populationSize = " << populationSize << endl;
//  cout << "maxEvaluations = " << maxEvaluations << endl;

  //Initialize the variables
  population = new SolutionSet(populationSize);
  evaluations = 0;

//  cout << "Poblacion inicializada con maxsize = " << population->getMaxSize() << endl;
//  cout << "Poblacion inicializada con size = " << population->size() << endl;
//  cout << "Problema: " << problem_->getName() << endl;

  //Read the operators
  mutationOperator = operators_["mutation"];
  crossoverOperator = operators_["crossover"];
  selectionOperator = operators_["selection"];

//  cout << "Comienza la inicializacion de la poblacion con size " << populationSize << endl;

  // Create the initial solutionSet
  Solution * newSolution;
  for (int i = 0; i < populationSize; i++) {
    newSolution = new Solution(problem_);
    problem_->evaluate(newSolution);
    problem_->evaluateConstraints(newSolution);
    evaluations++;
    population->add(newSolution);
  } //for

//  cout << "gGA: Poblacion inicializada con size = " << population->size() << endl;
//  cout << "gGA: Maximo de evaluaciones: " << maxEvaluations << endl;

  // Generations
  while (evaluations < maxEvaluations) {
  
    // Create the offSpring solutionSet
    offspringPopulation = new SolutionSet(populationSize);
    Solution ** parents = new Solution*[2];

    for (int i = 0; i < (populationSize / 2); i++) {
      if (evaluations < maxEvaluations) {
        //obtain parents
        parents[0] = (Solution *) (selectionOperator->execute(population));
        parents[1] = (Solution *) (selectionOperator->execute(population));
        Solution ** offSpring = (Solution **) (crossoverOperator->execute(parents));
        mutationOperator->execute(offSpring[0]);
        mutationOperator->execute(offSpring[1]);
        problem_->evaluate(offSpring[0]);
        problem_->evaluateConstraints(offSpring[0]);
        problem_->evaluate(offSpring[1]);
        problem_->evaluateConstraints(offSpring[1]);

        offspringPopulation->add(offSpring[0]);
        offspringPopulation->add(offSpring[1]);
        evaluations += 2;
        delete[] offSpring;
      } // if
    } // for
    delete[] parents;

    population->sort(comparator) ;
    offspringPopulation->sort(comparator) ;

    delete offspringPopulation->get(offspringPopulation->size()-1);
    delete offspringPopulation->get(offspringPopulation->size()-2);
    offspringPopulation->replace(offspringPopulation->size()-1, new Solution(population->get(0))) ;
    offspringPopulation->replace(offspringPopulation->size()-2, new Solution(population->get(1))) ;

    for (int i=0;i<population->size();i++) {
      delete population->get(i);
    }
    population->clear() ;

    for (int i = 0; i < offspringPopulation->size(); i++)
      population->add(offspringPopulation->get(i)) ;
    offspringPopulation->clear() ;
    delete offspringPopulation;
  }

  delete comparator;

  SolutionSet * resultPopulation  = new SolutionSet(1) ;
  resultPopulation->add(new Solution(population->get(0))) ;
  delete population;

  return resultPopulation ;
} // execute
