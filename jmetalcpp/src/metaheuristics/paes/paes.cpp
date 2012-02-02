/*
 * paes.cpp
 *
 *  Created on: 25/01/2012
 *      Author: Cristian
 */


#include <paes.h>

paes::paes(Problem * problem) : Algorithm(problem){
	cout << "Inicializado por segunda vez..." << endl;
}

/**
   * Tests two solutions to determine which one becomes be the guide of PAES
   * algorithm
   * @param solution The actual guide of PAES
   * @param mutatedSolution A candidate guide
  */

Solution * paes::test(Solution * solution, Solution * mutatedSolution,
                       AdaptiveGridArchive * archive){

    int originalLocation = archive->getGrid()->location(solution);
    int mutatedLocation  = archive->getGrid()->location(mutatedSolution);

    if (originalLocation == -1) {
      return new Solution(mutatedSolution);
    }

    if (mutatedLocation == -1) {
      return new Solution(solution);
    }

    if (archive->getGrid()->getLocationDensity(mutatedLocation) <
        archive->getGrid()->getLocationDensity(originalLocation)) {
      return new Solution(mutatedSolution);
    }

    return new Solution(solution);
  } // test

  /**
  * Runs of the Paes algorithm.
  * @return a <code>SolutionSet</code> that is a set of non dominated solutions
  * as a result of the algorithm execution
   * @throws JMException
  */

SolutionSet * paes::execute() {
    int bisections, archiveSize, maxEvaluations, evaluations;
    AdaptiveGridArchive * archive;

    Operator * mutationOperator;
    Comparator * dominance;

    //Read the params
    bisections = *(int *) getInputParameter("biSections");
    maxEvaluations = *(int *) getInputParameter("maxEvaluations");
    archiveSize = *(int *) getInputParameter("archiveSize");

    //Read the operators
    mutationOperator = operators_["mutation"];

    //Initialize the variables
    evaluations = 0;
    archive     = new AdaptiveGridArchive(archiveSize,bisections,problem_->getNumberOfObjectives());
    dominance = new DominanceComparator();

    //-> Create the initial solution and evaluate it and his constraints
    Solution * solution = new Solution(problem_);

    problem_->evaluate(solution);
    problem_->evaluateConstraints(solution);
    evaluations++;

    // Add it to the archive
    archive->add(new Solution(solution),evaluations );

    //Iterations....
    do {
      // Create the mutate one
      Solution * mutatedIndividual = new Solution(solution);
      mutationOperator->execute(mutatedIndividual);

      problem_->evaluate(mutatedIndividual);
      problem_->evaluateConstraints(mutatedIndividual);
      evaluations++;
      //<-

      // Check dominance
      int flag = dominance->compare(solution,mutatedIndividual);

      if (flag == 1) { //If mutate solution dominate
        solution = new Solution(mutatedIndividual);
        archive->add(mutatedIndividual,evaluations );
      } else if (flag == 0) { //If none dominate the other
    	//cout << "Va a Agregar Mutada Eval " << evaluations << endl;
        if (archive->add(mutatedIndividual,evaluations )) {
        	  //cout << "OK Agregada Mutada Eval " << evaluations << endl;;
//          //solution = test(solution,mutatedIndividual,archive);
        }
      }


    } while (evaluations < maxEvaluations);


    //Return the  population of non-dominated solution
    return archive;
	//return NULL;
  }  // execute

