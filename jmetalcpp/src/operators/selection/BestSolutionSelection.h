/**
  * @file BestSolutionSelection.h
  * @author Esteban López
  * @date 19 January 2012
**/

#ifndef __BEST_SOLUTION_SELECTION__
#define __BEST_SOLUTION_SELECTION__

#include <SolutionSet.h>
#include <Selection.h>
#include <Comparator.h>

/**
 * This class implements a selection operator used for selecting the best
 * solution in a SolutionSet according to a given comparator
 */
class BestSolutionSelection : public Selection {

private:
  Comparator * comparator_;

public:
  BestSolutionSelection(map<string, void *> parameters);
  void *execute(void *);

};

#endif // __BEST_SOLUTION_SELECTION__
