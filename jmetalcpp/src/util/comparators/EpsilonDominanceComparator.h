//  EpsilonDominanceComparator.h
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

#ifndef __EPSILON_DOMINANCE_COMPARATOR__
#define __EPSILON_DOMINANCE_COMPARATOR__

#include <Solution.h>
#include <Comparator.h>
#include <OverallConstraintViolationComparator.h>

/**
 * This class implements a <code>Comparator</code> (a method for comparing
 * <code>Solution</code> objects) based on epsilon dominance.
 */
class EpsilonDominanceComparator : public Comparator {

private:

  /**
   * Stores the value of eta, needed for epsilon-dominance.
   */
  double eta_;

  /**
   * Stores a comparator for check the OverallConstraintComparator
   */
  Comparator *overallConstraintViolationComparator_;

public:

  /**
   * Constructor.
   *  @param eta Value for epsilon-dominance.
   */
  EpsilonDominanceComparator(double eta);

  /**
   * Destructor.
   */
  ~EpsilonDominanceComparator();

  /**
   * Compares two solutions.
   * @param o1 Object representing the first <code>Solution</code>.
   * @param o1 Object representing the second <code>Solution</code>.
   * @return -1, or 0, or 1 if o1 dominates o2, both are
   * non-dominated, or o1 is dominated by o2, respectively.
   */
  int compare(void *o1, void *o2);
};

#endif
