//  NSGAII.cpp
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


#include <NSGAII.h>


/*
 * This class implements the NSGA-II algorithm.
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
NSGAII::NSGAII(Problem *problem) : Algorithm(problem) {
} // NSGAII


/*
 * Runs the NSGA-II algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet * NSGAII::execute() {

  int populationSize;
  int maxEvaluations;
  int evaluations;

//  QualityIndicator * indicators; // QualityIndicator object
  int requiredEvaluations; // Use in the example of use of the
                           // indicators object (see below)

  SolutionSet * population;
  SolutionSet * offspringPopulation;
  SolutionSet * unionSolution;

  Operator * mutationOperator;
  Operator * crossoverOperator;
  Operator * selectionOperator;

  Distance * distance = new Distance();

  //Read the parameters
  populationSize = *(int *) getInputParameter("populationSize");
  maxEvaluations = *(int *) getInputParameter("maxEvaluations");
//  indicators = (QualityIndicator *) getInputParameter("indicators");

  //Initialize the variables
  population = new SolutionSet(populationSize);
  evaluations = 0;

  requiredEvaluations = 0;

  //Read the operators
  mutationOperator = operators_["mutation"];
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
    
    // Create the solutionSet union of solutionSet and offSpring
    unionSolution = population->join(offspringPopulation);
    delete offspringPopulation;

    // Ranking the union
    Ranking * ranking = new Ranking(unionSolution);
    
    int remain = populationSize;
    int index = 0;
    SolutionSet * front = NULL;
    for (int i=0;i<population->size();i++) {
      delete population->get(i);
    }
    population->clear();

    // Obtain the next front
    front = ranking->getSubfront(index);

    while ((remain > 0) && (remain >= front->size())) {
      //Assign crowding distance to individuals
      distance->crowdingDistanceAssignment(front, problem_->getNumberOfObjectives());

      //Add the individuals of this front
      for (int k = 0; k < front->size(); k++) {
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

    // Remain is less than front(index).size, insert only the best one
    if (remain > 0) {  // front contains individuals to insert
      distance->crowdingDistanceAssignment(front, problem_->getNumberOfObjectives());
      Comparator * c = new CrowdingComparator();
      front->sort(c);
      delete c;
      for (int k = 0; k < remain; k++) {
        population->add(new Solution(front->get(k)));
      } // for

      remain = 0;
    } // if

    delete ranking;
    delete unionSolution;

    // This piece of code shows how to use the indicator object into the code
    // of NSGA-II. In particular, it finds the number of evaluations required
    // by the algorithm to obtain a Pareto front with a hypervolume higher
    // than the hypervolume of the true Pareto front.
//    if ((indicators != NULL) && (requiredEvaluations == 0)) {
//      double HV = indicators->getHypervolume(population);
//      if (HV >= (0.98 * indicators->getTrueParetoFrontHypervolume())) {
//        requiredEvaluations = evaluations;
//      } // if
//    } // if

  } // while

  delete distance;

  // Return as output parameter the required evaluations
//  setOutputParameter("evaluations", &requiredEvaluations);

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
