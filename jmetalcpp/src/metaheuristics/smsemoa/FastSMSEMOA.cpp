//  FastSMSEMOA.cpp
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


#include <FastSMSEMOA.h>

/*
 * This class implements the SMS-EMOA algorithm using the FastHypervolume
 * class.
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
FastSMSEMOA::FastSMSEMOA(Problem *problem) : Algorithm(problem) {
  utils_ = new MetricsUtil();
  hv_ = new Hypervolume();
} // FastSMSEMOA

/**
 * Destructor
 */
FastSMSEMOA::~FastSMSEMOA() {
  delete utils_;
  delete hv_;
} // ~FastSMSEMOA

/**
* Runs the Fast SMS-EMOA algorithm.
* @return a <code>SolutionSet</code> that is a set of non dominated solutions
* as a result of the algorithm execution
*/
SolutionSet * FastSMSEMOA::execute() {
  int populationSize;
  int maxEvaluations;
  int evaluations;
  double offset;

  QualityIndicator * indicators; // QualityIndicator object
  int requiredEvaluations; // Use in the example of use of the indicators object (see below)

  FastHypervolume * fastHypervolume;

  SolutionSet * population;
  SolutionSet * offspringPopulation;
  SolutionSet * unionSolution;

  Operator * mutationOperator;
  Operator * crossoverOperator;
  Operator * selectionOperator;

  //Read the parameters
  populationSize = *(int *) getInputParameter("populationSize");
  maxEvaluations = *(int *) getInputParameter("maxEvaluations");
  indicators = (QualityIndicator *) getInputParameter("indicators");
  offset = *(double *) getInputParameter("offset");

  //Initialize the variables
  population = new SolutionSet(populationSize);
  evaluations = 0;

  requiredEvaluations = 0;

  fastHypervolume = new FastHypervolume(offset);

  //Read the operator
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

  // Generations ...
  while (evaluations < maxEvaluations) {

    // select parents
    offspringPopulation = new SolutionSet(1);
    /*
    LinkedList<Solution> selectedParents = new LinkedList<Solution>();
    Solution[] parents = new Solution[0];
    while (selectedParents->size() < 2) {
      void * selected = selectionOperator->execute(population);
      try {
        Solution * parent = * (Solution*) selected;
        selectedParents.add(parent);
      } catch (ClassCastException e) {
        Configuration.logger_.log(Level.WARNING, "Class cast exception", e);
        parents = (Solution[]) selected;
        Collections.addAll(selectedParents, parents);
      }
    }
    parents = selectedParents.toArray(parents);
    */
    Solution ** parents = (Solution **) (selectionOperator->execute(population));

    // crossover
    Solution ** offSpring = (Solution **) (crossoverOperator->execute(parents));

    // mutation
    mutationOperator->execute(offSpring[0]);

    // evaluation
    problem_->evaluate(offSpring[0]);
    problem_->evaluateConstraints(offSpring[0]);

    // insert child into the offspring population
    offspringPopulation->add(offSpring[0]);

    evaluations++;

    delete offSpring[1];
    delete[] offSpring;
    delete[] parents;

    // Create the solutionSet union of solutionSet and offSpring
    unionSolution = population->join(offspringPopulation);
    delete offspringPopulation;

    // Ranking the union (non-dominated sorting)
    Ranking * ranking = new Ranking(unionSolution);

    // ensure crowding distance values are up to date
    // (may be important for parent selection)
    for (int j = 0; j < population->size(); j++) {
      population->get(j)->setCrowdingDistance(0.0);
    }

    SolutionSet * lastFront = ranking->getSubfront(ranking->getNumberOfSubfronts() - 1);

    //FastHypervolume fastHypervolume = new FastHypervolume() ;
    fastHypervolume->computeHVContributions(lastFront);
    CrowdingDistanceComparator * cd = new CrowdingDistanceComparator();
    lastFront->sort(cd);
    delete cd;

    // all but the worst are carried over to the survivor population
    SolutionSet * front = NULL;
    for (int i=0;i<population->size();i++) {
      delete population->get(i);
    }
    population->clear();
    for (int i = 0; i < ranking->getNumberOfSubfronts() - 1; i++) {
      front = ranking->getSubfront(i);
      for (int j = 0; j < front->size(); j++) {
        population->add(new Solution(front->get(j)));
      }
    }
    for (int i = 0; i < lastFront->size() - 1; i++) {
      population->add(new Solution(lastFront->get(i)));
    }

    delete unionSolution;
    delete ranking;

    // This piece of code shows how to use the indicator object into the code
    // of SMS-EMOA. In particular, it finds the number of evaluations required
    // by the algorithm to obtain a Pareto front with a hypervolume higher
    // than the hypervolume of the true Pareto front.
    /*
    if (indicators != null && requiredEvaluations == 0) {
      double HV = indicators.getHypervolume(population);
      if (HV >= (0.98 * indicators.getTrueParetoFrontHypervolume())) {
        requiredEvaluations = evaluations;
      }
    }
    */
  }

  // Return as output parameter the required evaluations
  //setOutputParameter("evaluations", requiredEvaluations);

  // Return the first non-dominated front
  Ranking * ranking = new Ranking(population);

  SolutionSet * result = new SolutionSet(ranking->getSubfront(0)->size());
  for (int i=0;i<ranking->getSubfront(0)->size();i++) {
    result->add(new Solution(ranking->getSubfront(0)->get(i)));
  }
  delete ranking;
  delete population;
  delete fastHypervolume;

  return result;

}
