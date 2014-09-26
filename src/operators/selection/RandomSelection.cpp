//  RandomSelection.cpp
//
//  Author:
//       Cristian Zambrano V. <cristian_uteq@hotmail.com>
//
//  Copyright (c) 2013 Antonio J. Nebro, Juan J. Durillo
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


#include <RandomSelection.h>

/**
 * @class RandomSelection
 * @brief This class implements a random selection operator used for selecting two
 * random parents
**/


/**
 * Constructor
 * Creates a new RandomSelection operator using a BinaryTournamentComparator
 */
RandomSelection::RandomSelection(map<string, void *> parameters): Selection(parameters) {
} // RandomSelection


/**
 * Destructor
 */
RandomSelection::~RandomSelection() { } // ~RandomSelection


/**
 * Performs the operation
 * @param object Object representing a SolutionSet.
 * @return an object representing an array with the selected parents
 */
void * RandomSelection::execute(void * object) {

  SolutionSet * population = (SolutionSet *) object;
  int pos1 = PseudoRandom::randInt(0,population->size()-1);
  int pos2 = PseudoRandom::randInt(0,population->size()-1);


  while ((pos1 == pos2)  && (population->size()>1) ) {
     pos2 = PseudoRandom::randInt(0,population->size()-1);
  }

  Solution ** parents = new Solution*[2];
  parents[0] = population->get(pos1);
  parents[1] = population->get(pos2);
  return parents;

} // execute
