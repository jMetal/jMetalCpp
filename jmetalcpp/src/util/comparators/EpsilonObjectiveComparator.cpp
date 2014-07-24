//  EpsilonObjectiveComparator.cpp
//
//  Authors:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//
//  Copyright (c) 2014 Antonio J. Nebro
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

#include <EpsilonObjectiveComparator.h>

/**
 * This class implements a <code>Comparator</code> (a method for comparing
 * <code>Solution</code> objects) based on epsilon dominance over a given
 * objective function.
 */

/**
 * Constructor.
 * @param nObj Index of the objective to compare.
 * @param eta Value for epsilon-dominance.
 */
EpsilonObjectiveComparator::EpsilonObjectiveComparator(int nObj, double eta) : Comparator() {
  objective_ = nObj;
  eta_       = eta;
} // EpsilonObjectiveComparator


/**
 * Compares two solutions.
 * @param o1 Object representing the first <code>Solution</code>.
 * @param o2 Object representing the second <code>Solution</code>.
 * @return -1, or 0, or 1 if o1 is less than, equal, or greater than o2,
 * respectively.
 */
int EpsilonObjectiveComparator::compare(void *o1, void *o2) {

  if (o1==NULL)
    return 1;
  else if (o2 == NULL)
    return -1;

  double objetive1 = ((Solution *) o1)->getObjective(objective_);
  double objetive2 = ((Solution *) o2)->getObjective(objective_);

  //Objetive implements comparable!!!
  if (objetive1/(1 + eta_) < objetive2) {
    return -1;
  } else if (objetive1/(1 + eta_) > objetive2) {
    return 1;
  } else {
    return 0;
  }

} // compare
