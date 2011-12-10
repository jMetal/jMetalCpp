/**
 * @file RankComparator.cpp
 * @author Esteban López
 * @date 29 November 2011
**/


#include <RankComparator.h>


/**
 * Compares two solutions.
 * @param o1 Object representing the first <code>Solution</code>.
 * @param o2 Object representing the second <code>Solution</code>.
 * @return -1, or 0, or 1 if o1 is less than, equal, or greater than o2,
 * respectively.
 */
int RankComparator::compare(Solution *o1, Solution *o2) {

	if (o1 == NULL)
		return 1;
	else if (o2 == NULL)
		return -1;

	if (o1->getRank() < o2->getRank()) {
	return -1;
	}

	if (o1->getRank() > o2->getRank()) {
	return 1;
	}

	return 0;

} // compare

