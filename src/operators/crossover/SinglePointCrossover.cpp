//  SinglePointCrossover.cpp
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
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


#include <SinglePointCrossover.h>


/**
 * @class SinglePointCrossover
 * @brief This class is aimed at representing a SinglePointCrossover operator
 **/


/**
 * Constructor
 * Create a new SBX crossover operator whit a default
 * index given by <code>DEFAULT_INDEX_CROSSOVER</code>
 */
SinglePointCrossover::SinglePointCrossover(map<string, void *> parameters)
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
Solution ** SinglePointCrossover::doCrossover(double probability, Solution *parent1, Solution *parent2) {

  Solution** offSpring = new Solution*[2];

  if (offSpring == NULL) {
    cout << "Error grave: Impossible reserve memory for allocating new solutions when performing SinglePointCrossover " << endl;
    exit(-1);
  }

  offSpring[0] = new Solution(parent1);
  offSpring[1] = new Solution(parent2);

  if (PseudoRandom::randDouble() < probability) {
    //1. Compute the total number of bits
    int totalNumberOfBits = 0;
    for (int i = 0; i < parent1->getProblem()->getNumberOfVariables(); i++) {
      totalNumberOfBits +=
          ((Binary *)(parent1->getDecisionVariables()[0]))->getNumberOfBits() ;
    }

    //2. Calculate the point to make the crossover
    int crossoverPoint = PseudoRandom::randInt(0, totalNumberOfBits - 1);

    //3. Compute the variable containing the crossoverPoint bit
    int variable = 0;
    int acountBits =
        ((Binary *)(parent1->getDecisionVariables()[variable]))->getNumberOfBits() ;

    while (acountBits < (crossoverPoint + 1)) {
      variable++;
      acountBits +=
          ((Binary *)(parent1->getDecisionVariables()[variable]))->getNumberOfBits() ;
    }

    //4. Compute the bit into the variable selected
    int diff = acountBits - crossoverPoint;
    int intoVariableCrossoverPoint =
        ((Binary *)(parent1->getDecisionVariables()[variable]))->getNumberOfBits() - diff;


    //5. Make the crossover into the the gene;
    Variable* offSpring1, * offSpring2;
    Binary * of1, *of2 ;
    offSpring1 =
        ((parent1->getDecisionVariables()[variable]))->deepCopy();

    offSpring2 =
        ((parent2->getDecisionVariables()[variable]))->deepCopy();
    of1 = (Binary *)offSpring1 ;
    of2 = (Binary *)offSpring2 ;

    for (int i = intoVariableCrossoverPoint;
        i < of1->getNumberOfBits();
        i++) {
      bool swap = of1->getIth(i) ;
      of1->setIth(i, of2->getIth(i)) ;
      of2->setIth(i, swap) ;
    }

    delete offSpring[0]->getDecisionVariables()[variable];
    delete offSpring[1]->getDecisionVariables()[variable];
    offSpring[0]->getDecisionVariables()[variable] = of1 ;
    offSpring[1]->getDecisionVariables()[variable] = of2 ;

    //6. Apply the crossover to the other variables
    for (int i = 0; i < variable; i++) {

      delete offSpring[0]->getDecisionVariables()[i];
      offSpring[0]->getDecisionVariables()[i] =
          parent2->getDecisionVariables()[i]->deepCopy();

      delete offSpring[1]->getDecisionVariables()[i];
      offSpring[1]->getDecisionVariables()[i] =
          parent1->getDecisionVariables()[i]->deepCopy();

    }

    //7. Decode the results
    //  for (int i = 0; i < offSpring[0].getDecisionVariables().length; i++) {
    //    ((Binary) offSpring[0].getDecisionVariables()[i]).decode();
    //    ((Binary) offSpring[1].getDecisionVariables()[i]).decode();
    //  }

  } // Binary or BinaryReal

  return offSpring;
} // doCrossover


/**
 * Executes the operation
 * @param object An object containing an array of two parents
 * @return An object containing the offSprings
 */
void * SinglePointCrossover::execute(void *object) {
  Solution ** parents = (Solution **) object;
  // TODO: Comprobar la longitud de parents
  // TODO: Chequear el tipo de parents

  Solution ** offSpring = (Solution **)doCrossover(crossoverProbability_, parents[0], parents[1]);

  return offSpring;
} // execute
