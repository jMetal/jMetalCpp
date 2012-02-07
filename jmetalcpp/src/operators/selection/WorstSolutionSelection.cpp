/**
 * @file WorstSolutionSelection.cpp
 * @author Esteban López
 * @date 19 January 2012
**/


#include <WorstSolutionSelection.h>


/**
 * This class implements a selection operator used for selecting the worst
 * solution in a SolutionSet according to a given comparator
 */


/**
 * Constructor
 */
WorstSolutionSelection::WorstSolutionSelection(map<string, void *> parameters)
: Selection(parameters) {
  comparator_ = NULL;
  if (parameters["comparator"] != NULL) {
    comparator_ = (Comparator *) parameters["comparator"];
  }
}


/**
* Performs the operation
* @param object Object representing a SolutionSet
* @return the worst solution found
*/
void * WorstSolutionSelection::execute(void * object) {

  SolutionSet * solutionSet = (SolutionSet *)object;

  if (solutionSet->size() == 0) {
    return NULL;
  }

  int worstSolution = 0;

  for (int i = 1; i < solutionSet->size(); i++) {
    if (comparator_->compare(solutionSet->get(i), solutionSet->get(worstSolution)) > 0) {
      worstSolution = i;
    }
  } // for

  int * intPtr = new int(worstSolution);
  return intPtr;

} // execute
