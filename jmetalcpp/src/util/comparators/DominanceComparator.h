/**
 * @file DominanceComparator.h
 * @author Juan J. Durillo
 * @author Antonio J. Nebro
 * @author Esteban López
 * @date 01 December 2011
**/

#ifndef __DOMINANCE_COMPARATOR__
#define __DOMINANCE_COMPARATOR__

#include <Solution.h>
#include <Comparator.h>

/**
 * This class implements a <code>Comparator</code> (a method for comparing
 * <code>Solution</code> objects) based on a constraint violation test +
 * dominance checking, as in NSGA-II.
 */
class DominanceComparator : public Comparator {

private:
	Comparator * overallConstraintViolationComparator_;

public:
   int compare(Solution *one, Solution *two);
};

#endif
