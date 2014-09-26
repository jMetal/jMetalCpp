//  BestSolutionSelection.cpp
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


#include <BestSolutionSelection.h>


/**
 * This class implements a selection operator used for selecting the best
 * solution in a SolutionSet according to a given comparator
 */


/**
 * Constructor
 */
BestSolutionSelection::BestSolutionSelection(map<string, void *> parameters)
: Selection(parameters) {
  comparator_ = NULL;
  if (parameters["comparator"] != NULL) {
    comparator_ = (Comparator *) parameters["comparator"];
  }
}


/**
* Performs the operation
* @param object Object representing a SolutionSet
* @return the best solution found
*/
void * BestSolutionSelection::execute(void * object) {

  SolutionSet * solutionSet = (SolutionSet *)object;

  if (solutionSet->size() == 0) {
    return NULL;
  }

  int bestSolution = 0;

  for (int i = 1; i < solutionSet->size(); i++) {
    if (comparator_->compare(solutionSet->get(i), solutionSet->get(bestSolution)) < 0) {
      bestSolution = i;
    }
  } // for

  int * intPtr = new int(bestSolution);
  return intPtr;

} // execute
