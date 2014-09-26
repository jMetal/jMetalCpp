//  DominanceComparator.h
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
//       Juan J. Durillo <durillo@lcc.uma.es>
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

#ifndef __DOMINANCE_COMPARATOR__
#define __DOMINANCE_COMPARATOR__

#include <Solution.h>
#include <Comparator.h>
#include <OverallConstraintViolationComparator.h>

/**
 * This class implements a <code>Comparator</code> (a method for comparing
 * <code>Solution</code> objects) based on a constraint violation test +
 * dominance checking, as in NSGA-II.
 */
class DominanceComparator : public Comparator {

private:
  Comparator * overallConstraintViolationComparator_;

public:
  DominanceComparator();
  ~DominanceComparator();
  int compare(void *one, void *two);
};

#endif
