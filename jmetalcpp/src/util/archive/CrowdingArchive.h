/**
 * @file CrowdingArchive.h
 * @author Esteban López
 * @version 1.0
 * @date 13 December 2011
 */

#ifndef __CROWDINGARCHIVE__
#define __CROWDINGARCHIVE__

#include <Archive.h>
#include <Comparator.h>
#include <CrowdingDistanceComparator.h>
#include <Distance.h>
#include <DominanceComparator.h>
#include <EqualSolutions.h>
#include <Solution.h>

/**
 * This class implements a bounded archive based on crowding distances (as
 * defined in NSGA-II).
 */
class CrowdingArchive : public Archive {

private:
  int maxSize_;
  int objectives_;
  Comparator * dominance_;
  Comparator * equals_;
  Comparator * crowdingDistance_;
  Distance * distance_;

public:
  CrowdingArchive(int maxSize, int numberOfObjectives);
  bool add(Solution * solution);

};


#endif
