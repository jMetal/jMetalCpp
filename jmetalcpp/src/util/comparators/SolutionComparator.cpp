//  SolutionComparator.cpp
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


#include <SolutionComparator.h>


/**
 * Establishes a value of allowed dissimilarity
 */
double SolutionComparator::EPSILON  = 1e-10;


/**
 * Compares two solutions.
 * @param o1 Object representing the first <code>Solution</code>.
 * @param o2 Object representing the second <code>Solution</code>.
 * @return 0, if both solutions are equals with a certain dissimilarity, -1
 * otherwise.
**/
int SolutionComparator::compare(void *o1, void *o2) {

  Solution * solution1 = (Solution *) o1;
  Solution * solution2 = (Solution *) o2;

  int res = -1;

  if (solution1->getNumberOfVariables() != solution2->getNumberOfVariables())
    return res;

  Distance * d = new Distance();
  if (d->distanceBetweenSolutions(solution1,solution2) < EPSILON) {
    res = 0;
  }
  delete d;

  return res;

} // compare

