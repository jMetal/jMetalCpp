//  PolynomialMutation.h
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

#ifndef __POLYNOMIAL_MUTATION__
#define __POLYNOMIAL_MUTATION__

#include <Mutation.h>
#include <Solution.h>
#include <math.h>
#include <float.h>
#include <PseudoRandom.h>
#include <XReal.h>

/**
  * @class Mutation
  * @brief This class implements a polynomial mutation operator.
**/
class PolynomialMutation : public Mutation {

public:

  static const double ETA_M_DEFAULT_;
  static const double eta_m_;

  PolynomialMutation(map<string, void *> parameters);
  ~PolynomialMutation();

  void * execute(void *);

private:
  double mutationProbability_;
  double distributionIndex_;

  void * doMutation(double probability, Solution * solution);
  // TODO: VALID_TYPES;

}; // PolynomialMutation

#endif
