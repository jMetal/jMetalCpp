/**
 * @file ObjectiveComparator.cpp
 * @author Esteban López
 * @date 29 November 2011
**/


#include <ObjectiveComparator.h>


/**
 * Constructor.
 * @param nObj The index of the objective to compare
 */
ObjectiveComparator::ObjectiveComparator(int nObj) {
  this->nObj = nObj;
} // ObjectiveComparator


/**
 * Compare two solutions.
 * @param o1 Object representing the first <code>Solution</code>.
 * @param o2 Object representing the second <code>Solution</code>.
 * @return -1, or 0, or 1 if o1 is less than, equal, or greater than o2,
 * respectively.
**/
int ObjectiveComparator::compare(Solution *o1, Solution *o2) {
  if (o1==NULL)
    return 1;
  else if (o2 == NULL)
    return -1;

  double objetive1 = o1->getObjective(this->nObj);
  double objetive2 = o2->getObjective(this->nObj);
  if (objetive1 < objetive2) {
    return -1;
  } else if (objetive1 > objetive2) {
    return 1;
  } else {
    return 0;
  }
} // compare

