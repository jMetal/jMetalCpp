/**
  * @file WorstSolutionSelection.h
  * @author Esteban López
  * @date 19 January 2012
**/

#ifndef __WORST_SOLUTION_SELECTION__
#define __WORST_SOLUTION_SELECTION__

#include <SolutionSet.h>
#include <Selection.h>
#include <Comparator.h>

/**
 * This class implements a selection operator used for selecting the worst
 * solution in a SolutionSet according to a given comparator
 */
class WorstSolutionSelection : public Selection {

private:
  Comparator * comparator_;

public:
  WorstSolutionSelection(map<string, void *> parameters);
  void *execute(void *);

};

#endif // __WORST_SOLUTION_SELECTION__
