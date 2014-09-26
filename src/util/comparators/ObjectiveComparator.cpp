//  ObjectiveComparator.cpp
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//
//  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include <ObjectiveComparator.h>


/**
 * Constructor.
 * @param nObj The index of the objective to compare
 */
ObjectiveComparator::ObjectiveComparator(int nObj) {
  this->nObj = nObj;
  ascendingOrder_ = true;
} // ObjectiveComparator

/**
 * Constructor.
 * @param nObj The index of the objective to compare
 * @param descendingOrder TRUE if use a descending order, FALSE otherwise
 */
ObjectiveComparator::ObjectiveComparator(int nObj, bool descendingOrder) {
  this->nObj = nObj;
  ascendingOrder_ = !descendingOrder;
} // ObjectiveComparator

/**
 * Compare two solutions.
 * @param o1 Object representing the first <code>Solution</code>.
 * @param o2 Object representing the second <code>Solution</code>.
 * @return -1, or 0, or 1 if o1 is less than, equal, or greater than o2,
 * respectively.
**/
int ObjectiveComparator::compare(void *o1, void *o2) {
  if (o1==NULL)
    return 1;
  else if (o2 == NULL)
    return -1;

  double objetive1 = ((Solution *) o1)->getObjective(this->nObj);
  double objetive2 = ((Solution *) o2)->getObjective(this->nObj);
  if (ascendingOrder_) {
    if (objetive1 < objetive2) {
      return -1;
    } else if (objetive1 > objetive2) {
      return 1;
    } else {
      return 0;
    }
  } else {
    if (objetive1 < objetive2) {
      return 1;
    } else if (objetive1 > objetive2) {
      return -1;
    } else {
      return 0;
    }
  }

} // compare
