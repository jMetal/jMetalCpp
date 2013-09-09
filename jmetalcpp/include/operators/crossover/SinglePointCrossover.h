//  SinglePointCrossover.h
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

#ifndef __SPX_CROSSOVER__
#define __SPX_CROSSOVER__

#include <Crossover.h>
#include <Binary.h>
#include <Solution.h>
#include <math.h>

/**
 * This class allows to apply a SBX crossover operator using two parent
 * solutions.
**/
class SinglePointCrossover : public Crossover {

public:
  SinglePointCrossover(map<string, void *> parameters);
  void *execute(void *);

private:
  double crossoverProbability_;
  Solution ** doCrossover(double probability,
      Solution * parent1, Solution * parent2);
};

#endif
