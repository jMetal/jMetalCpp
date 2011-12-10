/**
 * @file OverallConstraintViolationComparator.cpp
 * @author Esteban López
 * @date 01 December 2011
**/


#include <OverallConstraintViolationComparator.h>


/**
 * Compares two solutions.
 * @param o1 Object representing the first <code>Solution</code>.
 * @param o2 Object representing the second <code>Solution</code>.
 * @return -1, or 0, or 1 if o1 is less than, equal, or greater than o2,
 * respectively.
 */
int OverallConstraintViolationComparator::compare(Solution *o1, Solution *o2) {
  double overall1, overall2;
  overall1 = o1->getOverallConstraintViolation();
  overall2 = o2->getOverallConstraintViolation();

  if ((overall1 < 0) && (overall2 < 0)) {
    if (overall1 > overall2){
      return -1;
    } else if (overall2 > overall1){
      return 1;
    } else {
      return 0;
    }
  } else if ((overall1 == 0) && (overall2 < 0)) {
    return -1;
  } else if ((overall1 < 0) && (overall2 == 0)) {
    return 1;
  } else {
    return 0;
  }
} // compare

