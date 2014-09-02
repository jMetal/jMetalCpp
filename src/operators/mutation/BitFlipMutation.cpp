//  BitFlipMutation.cpp
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


#include <BitFlipMutation.h>


/**
 * Constructor
 * Creates a new instance of the polynomial mutation operator
 */
BitFlipMutation::BitFlipMutation(map<string, void *> parameters)
: Mutation(parameters) {
  mutationProbability_ = 0.0 ;
  if (parameters["probability"] != NULL)
    mutationProbability_ = *(double *) parameters["probability"];
} // BitFlipMutation


/**
 * Destructor
 */
BitFlipMutation::~BitFlipMutation() { } // ~BitFlipMutation


/**
 * Perform the mutation operation
 * @param probability Mutation probability
 * @param solution The solution to mutate
 */
void * BitFlipMutation::doMutation(double probability, Solution *solution) {
  int numberOfVariables = solution->getNumberOfVariables() ;

  for (int i = 0 ; i < numberOfVariables ; i++) {
    Binary * variable = (Binary *)(solution->getDecisionVariables()[i]) ;
    for (int j = 0; j < variable->getNumberOfBits() ; j++)
      if (PseudoRandom::randDouble() <= mutationProbability_)
        variable->flip(j) ;
  }
} // doMutation


/**
 * Executes the operation
 * @param object An object containing a solution
 * @return An object containing the mutated solution
 * @throws JMException
 */
void * BitFlipMutation::execute(void *object) {
  Solution *solution = (Solution *)object;
  // TODO: VALID_TYPES?

  doMutation(mutationProbability_, solution)  ;

  return solution;
} // execute
