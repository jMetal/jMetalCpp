//  EpsilonObjectiveComparator.h
//
//  Author:
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

#ifndef __EPSILON_OBJECTIVE_COMPARATOR__
#define __EPSILON_OBJECTIVE_COMPARATOR__

#include <Solution.h>
#include <Comparator.h>

/**
 * This class implements a <code>Comparator</code> (a method for comparing
 * <code>Solution</code> objects) based on epsilon dominance over a given
 * objective function.
 */
class EpsilonObjectiveComparator : public Comparator {

private:

  /**
   * Stores the objective index to compare
   */
  int objective_;

  /**
   * Stores the eta value for epsilon-dominance
   */
  double eta_;

public:

  /**
   * Constructor.
   * @param nObj Index of the objective to compare.
   * @param eta Value for epsilon-dominance.
   */
  EpsilonObjectiveComparator(int nObj, double eta);

  /**
   * Compares two solutions.
   * @param o1 Object representing the first <code>Solution</code>.
   * @param o2 Object representing the second <code>Solution</code>.
   * @return -1, or 0, or 1 if o1 is less than, equal, or greater than o2,
   * respectively.
   */
  int compare(void *one, void *two);
};

#endif
