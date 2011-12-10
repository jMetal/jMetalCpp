/**
 * @file CrowdingComparator.h
 * @author Juan J. Durillo
 * @author Antonio J. Nebro
 * @author Esteban López
 * @date 29 November 2011
**/

#ifndef __CROWDING_COMPARATOR__
#define __CROWDING_COMPARATOR__

#include <Comparator.h>
#include <Solution.h>

/**
 * This class implements a <code>Comparator</code> (a method for comparing
 * <code>Solution</code> objects) based on the crowding distance, as in NSGA-II.
 */
class CrowdingComparator : public Comparator {

private:
	Comparator * comparator;

public:
	int compare(Solution * o1, Solution * o2);

};

#endif
