/**
 * @file EqualSolutions.h
 * @author Esteban López
 * @date 13 December 2011
**/

#ifndef __EQUAL_SOLUTIONS__
#define __EQUAL_SOLUTIONS__

#include <Solution.h>
#include <Comparator.h>
#include <ObjectiveComparator.h>

/**
 * This class implements a <code>Comparator</code> (a method for comparing
 * <code>Solution</code> objects) based whether all the objective values are
 * equal or not. A dominance test is applied to decide about what solution
 * is the best.
 */
class EqualSolutions : public Comparator {

public:
  int compare(Solution *solution1, Solution *solution2);
};

#endif
