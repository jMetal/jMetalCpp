//  DominanceComparator.cpp
//
//  Authors:
//       Juan J. Durillo <durillo@lcc.uma.es>
//       Antonio J. Nebro <antonio@lcc.uma.es>
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

#include <DominanceComparator.h>

/**
  * @class DominanceComparator
  * @brief This class is aimed at implementing a Dominance comparator.
    It returns true if solution one dominates to solution two. It returns
    false in other case. Author must notice that two solutions are 
    non dominated only if: !compare(one,two) = false and !compare(two,one)
**/


/**
 * Constructor
 */
DominanceComparator::DominanceComparator() : Comparator() {
  overallConstraintViolationComparator_ = new OverallConstraintViolationComparator();
} // DominanceComparator


/**
 * Destructor
 */
DominanceComparator::~DominanceComparator() {
  delete overallConstraintViolationComparator_;
} // ~DominanceComparator


/**
 * Compare two solutions.
 * @param o1 Object representing the first <code>Solution</code>.
 * @param o2 Object representing the second <code>Solution</code>.
 * @return -1, or 0, or 1 if o1 is less than, equal, or greater than o2,
 * respectively.
**/
int DominanceComparator::compare(void * o1, void * o2) {

  if (o1==NULL)
    return 1;
  else if (o2 == NULL)
    return -1;

  Solution * one = (Solution *) o1;
  Solution * two = (Solution *) o2;

  int dominate1 ; // dominate1 indicates if some objective of solution1
                  // dominates the same objective in solution2. dominate2
  int dominate2 ; // is the complementary of dominate1.

  dominate1 = 0 ;
  dominate2 = 0 ;

  int flag; //stores the result of the comparison
  
  if (one->getOverallConstraintViolation()!=
      two->getOverallConstraintViolation() &&
     ((one->getOverallConstraintViolation() < 0) ||
     (two->getOverallConstraintViolation() < 0))){
    int returnValue = overallConstraintViolationComparator_->compare(one,two);
    return returnValue;
  }
  
  // Equal number of violated constraints. Applying a dominance Test then
  double value1, value2;
  for (int i = 0; i < one->getNumberOfObjectives(); i++) {
    value1 = one->getObjective(i);
    value2 = two->getObjective(i);
    if (value1 < value2) {
      flag = -1;
    } else if (value1 > value2) {
      flag = 1;
    } else {
      flag = 0;
    }

    if (flag == -1) {
      dominate1 = 1;
    }

    if (flag == 1) {
      dominate2 = 1;
    }
  }

  if (dominate1 == dominate2) {
    return 0; //No one dominate the other
  }
  if (dominate1 == 1) {
    return -1; // solution1 dominate
  }
  return 1;    // solution2 dominate

} // compare
