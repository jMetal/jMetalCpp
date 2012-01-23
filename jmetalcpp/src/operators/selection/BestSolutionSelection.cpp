/**
 * @file BestSolutionSelection.cpp
 * @author Esteban López
 * @date 19 January 2012
**/


#include <BestSolutionSelection.h>


/**
 * This class implements a selection operator used for selecting the best
 * solution in a SolutionSet according to a given comparator
 */


/**
 * Constructor
 */
BestSolutionSelection::BestSolutionSelection(map<string, void *> parameters)
: Selection(parameters) {
  comparator_ = NULL;
  if (parameters["comparator"] != NULL) {
    comparator_ = (Comparator *) parameters["comparator"];
  }
}


/**
* Performs the operation
* @param object Object representing a SolutionSet
* @return the best solution found
*/
void * BestSolutionSelection::execute(void * object) {

  SolutionSet * solutionSet = (SolutionSet *)object;

  if (solutionSet->size() == 0) {
    return NULL;
  }

  int bestSolution = 0;

  for (int i = 1; i < solutionSet->size(); i++) {
    if (comparator_->compare(solutionSet->get(i), solutionSet->get(bestSolution)) < 0) {
      bestSolution = i;
    }
  } // for

  //return (void*) bestSolution;
  return &bestSolution;

} // execute
