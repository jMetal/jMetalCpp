//  SinglePointCrossover.cpp
//
//  Author:
//       Juanjo
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


#include <HUXCrossover.h>


/**
 * Constructor
 * Create a new SBX crossover operator whit a default
 * index given by <code>DEFAULT_INDEX_CROSSOVER</code>
 */
HUXCrossover::HUXCrossover(map<string, void *> parameters)
: Crossover(parameters) {
  crossoverProbability_ = 0.0 ;
  //TODO: crossoverProbability_ = NULL;
  if (parameters["probability"] != NULL)
    crossoverProbability_ = *(double *)parameters["probability"];
} // SinglePointCrossover


/**
 * Perform the crossover operation.
 * @param probability Crossover probability
 * @param parent1 The first parent
 * @param parent2 The second parent
 * @return An array containing the two offsprings
 **/
Solution ** HUXCrossover::doCrossover(double probability, Solution *parent1, Solution *parent2) {

  Solution** offSpring = new Solution*[2];

  if (offSpring == NULL) {
    cout << "Error grave: Impossible reserve memory for allocating new solutions when performing SinglePointCrossover " << endl;
    exit(-1);
  }

  offSpring[0] = new Solution(parent1);
  offSpring[1] = new Solution(parent2);

  if (PseudoRandom::randDouble() < probability) {
	for (int var = 0; var < parent1->getNumberOfVariables(); var++) {
		Binary *p1 = (Binary *)parent1->getDecisionVariables()[var];
		Binary *p2 = (Binary *)parent2->getDecisionVariables()[var];
		for (int bit = 0; bit < p1->getNumberOfBits(); bit++) {
			if (PseudoRandom::randDouble() < 0.5) {
				Binary *o1, *o2;
				o1 = (Binary *) offSpring[0]->getDecisionVariables()[var];
				o2 = (Binary *) offSpring[1]->getDecisionVariables()[var];
				o1->setIth(bit,p2->getIth(bit));
				o2->setIth(bit,p1->getIth(bit));
					
			}
		}	
	}
	for (int var = 0; var < parent1->getNumberOfVariables(); var++) {
		((Binary *)offSpring[0]->getDecisionVariables()[var])->decode();
		((Binary *)offSpring[0]->getDecisionVariables()[var])->decode();
	}
  }
  return offSpring;

  return offSpring;
} // doCrossover


/**
 * Executes the operation
 * @param object An object containing an array of two parents
 * @return An object containing the offSprings
 */
void * HUXCrossover::execute(void *object) {
  Solution ** parents = (Solution **) object;
  // TODO: Comprobar la longitud de parents
  // TODO: Chequear el tipo de parents

  Solution ** offSpring = (Solution **)doCrossover(crossoverProbability_, parents[0], parents[1]);

  return offSpring;
} // execute
