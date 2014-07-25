//  UniformMutation.cpp
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

#include <UniformMutation.h>

/**
 * This class implements a uniform mutation operator.
 */

/**
 * Valid solution types to apply this operator.
 */
const string UniformMutation::VALID_TYPES[] = {"Real", "ArrayReal"};

/**
 * Constructor
 * Creates a new uniform mutation operator instance
 */
UniformMutation::UniformMutation(map<string, void *> parameters)
: Mutation(parameters) {
  if (parameters["probability"] != NULL) {
    mutationProbability_ = *(double *) parameters["probability"];
  }
  if (parameters["perturbation"] != NULL) {
    perturbation_ = *(double *) parameters["perturbation"];
  }
} // UniformMutation

/**
 * Performs the operation
 * @param probability Mutation probability
 * @param solution The solution to mutate
 */
void UniformMutation::doMutation(double probability, Solution *solution) {

  XReal * x = new XReal(solution);

  for (int var=0; var < solution->getNumberOfVariables(); var++) {
    if (PseudoRandom::randDouble() < probability) {
      double rand = PseudoRandom::randDouble();
      double tmp = (rand - 0.5)*perturbation_;

      tmp += x->getValue(var);

      if (tmp < x->getLowerBound(var)) {
        tmp = x->getLowerBound(var);
      } else if (tmp > x->getUpperBound(var)) {
        tmp = x->getUpperBound(var);
      }

      x->setValue(var, tmp) ;
    } // if
  } // for

  delete x;

} // doMutation

/**
 * Executes the operation
 * @param object An object containing a solution
 * @return An object containing the mutated solution
 */
void *UniformMutation::execute(void *object) {
  Solution *solution = (Solution *)object;
  // TODO: VALID_TYPES?
  doMutation(mutationProbability_,solution);
  return solution;
} // execute
