/**
 * @file CrowdingDistanceComparator.h
 * @author Esteban López
 * @date 13 December 2011
**/

#ifndef __CROWDING_DISTANCE_COMPARATOR__
#define __CROWDING_DISTANCE_COMPARATOR__

#include <Comparator.h>
#include <Solution.h>

/**
 * This class implements a <code>Comparator</code> (a method for comparing
 * <code>Solution</code> objects) based on the crowding distance, as in NSGA-II.
 */
class CrowdingDistanceComparator : public Comparator {

private:

public:
  int compare(Solution * o1, Solution * o2);

};

#endif
