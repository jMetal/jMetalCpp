/**
 * @file CrowdingComparator.cpp
 * @author Juan J. Durillo
 * @author Antonio J. Nebro
 * @author Esteban López
 * @date 29 November 2011
**/

#include <RankComparator.h>
#include <CrowdingComparator.h>


/**
 * Compare two solutions.
 * @param o1 Object representing the first <code>Solution</code>.
 * @param o2 Object representing the second <code>Solution</code>.
 * @return -1, or 0, or 1 if o1 is less than, equal, or greater than o2,
 * respectively.
**/
int CrowdingComparator::compare(Solution *o1, Solution *o2) {

  if (o1 == NULL)
    return 1;
  else if (o2 == NULL)
    return -1;

  comparator = new RankComparator();
	int flagComparatorRank = comparator->compare(o1,o2);
	delete comparator;

	if (flagComparatorRank != 0)
		return flagComparatorRank;

	/* His rank is equal, then distance crowding comparator */
	double distance1 = o1->getCrowdingDistance();
	double distance2 = o2->getCrowdingDistance();
	if (distance1 >  distance2)
		return -1;

	if (distance1 < distance2)
		return 1;

	return 0;
} // compare

