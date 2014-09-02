//  SBXCrossover.h
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

#ifndef __SBX_CROSSOVER__
#define __SBX_CROSSOVER__

#include <Crossover.h>
#include <XReal.h>
#include <Solution.h>
#include <math.h>

/**
 * This class allows to apply a SBX crossover operator using two parent
 * solutions.
**/
class SBXCrossover : public Crossover {

public:
  SBXCrossover(map<string, void *> parameters);
  ~SBXCrossover();
  void *execute(void *);

protected:
  static const double ETA_C_DEFAULT_;
  static const double EPS;

private:
  double crossoverProbability_;
  double distributionIndex_;
  //TODO: A�adir VALID_TYPES;
  Solution ** doCrossover(double probability,
      Solution * parent1, Solution * parent2);
};

#endif
