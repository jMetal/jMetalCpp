//  BinaryTournament2.cpp
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


#include <BinaryTournament.h>


/**
 * @class BinaryTournament
 * @brief This class implements a binary tournament selection operator
**/


/**
 * Constructor
 * Creates a new Binary tournament operator using a BinaryTournamentComparator
 */
BinaryTournament::BinaryTournament(map<string, void *> parameters)
: Selection(parameters) {
  if (parameters["comparator"] != NULL)
    comparator_ = (Comparator *) parameters["comparator"];
  else
    comparator_ = new DominanceComparator();
} // BinaryTournament


/**
 * Destructor
 */
BinaryTournament::~BinaryTournament() {
  delete comparator_;
} // ~BinaryTournament


/**
* Performs the operation
* @param object Object representing a SolutionSet
* @return the selected solution
*/
void * BinaryTournament::execute(void * object) {

  SolutionSet * solutionSet = (SolutionSet *) object;
  int index1 = PseudoRandom::randInt(0,solutionSet->size()-1);
  int index2 = PseudoRandom::randInt(0,solutionSet->size()-1);

  if (solutionSet->size() >= 2) {
    while (index1 == index2) {
      index2 = PseudoRandom::randInt(0,solutionSet->size()-1);
    }
  }

  Solution * solution1 = solutionSet->get(index1);
  Solution * solution2 = solutionSet->get(index2);

  int flag = comparator_->compare(solution1,solution2);
  if (flag == -1)
    return solution1;
  else if (flag == 1)
    return solution2;
  else
    if (PseudoRandom::randDouble()<0.5)
      return solution1;
    else
      return solution2;

} // execute
