/**
 * @file RankComparator.h
 * @author Esteban López
 * @date 29 November 2011
**/

#ifndef __RANK_COMPARATOR__
#define __RANK_COMPARATOR__

#include <Comparator.h>
#include <Solution.h>

/**
 * This class implements a <code>Comparator</code> (a method for comparing
 * <code>Solution</code> objects) based on the rank of the solutions.
 */
class RankComparator : public Comparator {

public:
	int compare(Solution * o1, Solution * o2);

};

#endif
