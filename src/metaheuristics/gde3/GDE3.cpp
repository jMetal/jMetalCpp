//  GDE3.cpp
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


#include <GDE3.h>


/*
 * This class implements the GDE3 algorithm.
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
GDE3::GDE3(Problem *problem) : Algorithm(problem) {
} // GDE3


/*
 * Runs the GDE3 algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet * GDE3::execute() {

  int populationSize;
  int maxIterations;
  int evaluations;
  int iterations;

  SolutionSet * population;
  SolutionSet * offspringPopulation;

  Distance * distance;
  Comparator * dominance;

  Operator * crossoverOperator;
  Operator * selectionOperator;

  distance  = new Distance();
  dominance = new DominanceComparator();

  Solution ** parent;

  //Read the parameters
  populationSize = *(int *) getInputParameter("populationSize");
  maxIterations  = *(int *) getInputParameter("maxIterations");

  //Initialize the variables
  population  = new SolutionSet(populationSize);
  evaluations = 0;
  iterations  = 0;

  //Read the operators
  crossoverOperator = operators_["crossover"];
  selectionOperator = operators_["selection"];

  // Create the initial solutionSet
  Solution * newSolution;
  for (int i = 0; i < populationSize; i++) {
    newSolution = new Solution(problem_);
    problem_->evaluate(newSolution);
    problem_->evaluateConstraints(newSolution);
    evaluations++;
    population->add(newSolution);
  } //for

  // Generations ...
  while (iterations < maxIterations) {
    // Create the offSpring solutionSet
    offspringPopulation  = new SolutionSet(populationSize * 2);

    for (int i = 0; i < populationSize; i++){
      // Obtain parents. Two parameters are required: the population and the
      //                 index of the current individual
      void ** object1 = new void*[2];
      object1[0] = population;
      object1[1] = &i;
      parent = (Solution **) (selectionOperator->execute(object1));
      delete[] object1;

      Solution * child ;
      // Crossover. Two parameters are required: the current individual and the
      //            array of parents
      void ** object2 = new void*[2];
      object2[0] = population->get(i);
      object2[1] = parent;
      child = (Solution *) (crossoverOperator->execute(object2));
      delete[] object2;
      delete[] parent;

      problem_->evaluate(child) ;
      problem_->evaluateConstraints(child);
      evaluations++ ;

      // Dominance test
      int result  ;
      result = dominance->compare(population->get(i), child) ;
      if (result == -1) { // Solution i dominates child
        offspringPopulation->add(new Solution(population->get(i)));
        delete child;
      } // if
      else if (result == 1) { // child dominates
        offspringPopulation->add(child) ;
      } // else if
      else { // the two solutions are non-dominated
        offspringPopulation->add(child) ;
        offspringPopulation->add(new Solution(population->get(i)));
      } // else
    } // for

    // Ranking the offspring population
    Ranking * ranking = new Ranking(offspringPopulation);

    int remain = populationSize;
    int index  = 0;
    SolutionSet * front = NULL;
    for (int i = 0; i < populationSize; i++) {
      delete population->get(i);
    }
    population->clear();

    // Obtain the next front
    front = ranking->getSubfront(index);

    while ((remain > 0) && (remain >= front->size())){
      //Assign crowding distance to individuals
      distance->crowdingDistanceAssignment(front,problem_->getNumberOfObjectives());
      //Add the individuals of this front
      for (int k = 0; k < front->size(); k++ ) {
        population->add(new Solution(front->get(k)));
      } // for

      //Decrement remain
      remain = remain - front->size();

      //Obtain the next front
      index++;
      if (remain > 0) {
        front = ranking->getSubfront(index);
      } // if
    } // while

    // remain is less than front(index).size, insert only the best one
    if (remain > 0) {  // front contains individuals to insert
      while (front->size() > remain) {
         distance->crowdingDistanceAssignment(front,problem_->getNumberOfObjectives());
         Comparator * crowdingComparator = new CrowdingComparator();
         int indexWorst = front->indexWorst(crowdingComparator);
         delete crowdingComparator;
         delete front->get(indexWorst);
         front->remove(indexWorst);
      }
      for (int k = 0; k < front->size(); k++) {
        population->add(new Solution(front->get(k)));
      }

      remain = 0;
    } // if

    delete ranking;
    delete offspringPopulation;

    iterations ++ ;
  } // while

  delete dominance;
  delete distance;

  // Return the first non-dominated front
  Ranking * ranking = new Ranking(population);
  SolutionSet * result = new SolutionSet(ranking->getSubfront(0)->size());
  for (int i=0;i<ranking->getSubfront(0)->size();i++) {
    result->add(new Solution(ranking->getSubfront(0)->get(i)));
  }
  delete ranking;
  delete population;

  return result;

} // execute
