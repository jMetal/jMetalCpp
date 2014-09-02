//  UniformMutation.h
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

#ifndef __UNIFORM_MUTATION__
#define __UNIFORM_MUTATION__

#include <Mutation.h>
#include <Solution.h>
#include <PseudoRandom.h>
#include <XReal.h>

/**
 * This class implements a uniform mutation operator.
 */
class UniformMutation : public Mutation {

private:

  /**
   * Valid solution types to apply this operator.
   */
  static const string VALID_TYPES[];

  /**
   * Stores the value used in a uniform mutation operator.
   */
  double perturbation_;

  double mutationProbability_;

  /**
   * Performs the operation.
   * @param probability Mutation probability
   * @param solution The solution to mutate
   * @throws JMException
   */
  void doMutation(double probability, Solution *solution);

public:

  /**
   * Constructor.
   * Creates a new uniform mutation operator instance.
   */
  UniformMutation(map<string, void *> parameters);

  /**
   * Executes the operation
   * @param object An object containing the solution to mutate
   */
  void *execute(void *);

}; // UniformMutation

#endif
