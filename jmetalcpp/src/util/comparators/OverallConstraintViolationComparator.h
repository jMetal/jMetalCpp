/**
 * @file OverallConstraintViolationComparator.h
 * @author Esteban López
 * @date 01 December 2011
**/

#ifndef __OVERALL_CONSTRAINT_VIOLATION_COMPARATOR__
#define __OVERALL_CONSTRAINT_VIOLATION_COMPARATOR__

#include <Comparator.h>
#include <Solution.h>

/**
 * This class implements a <code>Comparator</code> (a method for comparing
 * <code>Solution</code> objects) based on the overall constraint violation of
 * the solucions, as in NSGA-II.
 */
class OverallConstraintViolationComparator : public Comparator {

public:
	int compare(Solution * o1, Solution * o2);

};

#endif
