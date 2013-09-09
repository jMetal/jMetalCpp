//  DifferentialEvolutionCrossover.h
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

#ifndef __DIFFERENTIAL_EVOLUTION_CROSSOVER__
#define __DIFFERENTIAL_EVOLUTION_CROSSOVER__

#include <string>
#include <Crossover.h>
#include <Solution.h>
#include <PseudoRandom.h>
#include <XReal.h>

/**
 * Differential evolution crossover operators
 * Comments:
 * - The operator receives two parameters: the current individual and an array
 *   of three parent individuals
 * - The best and rand variants depends on the third parent, according whether
 *   it represents the current of the "best" individual or a randon one.
 *   The implementation of both variants are the same, due to that the parent
 *   selection is external to the crossover operator.
 * - Implemented variants:
 *   - rand/1/bin (best/1/bin)
 *   - rand/1/exp (best/1/exp)
 *   - current-to-rand/1 (current-to-best/1)
 *   - current-to-rand/1/bin (current-to-best/1/bin)
 *   - current-to-rand/1/exp (current-to-best/1/exp)
 */
class DifferentialEvolutionCrossover : public Crossover {

public:
  DifferentialEvolutionCrossover(map<string, void *> parameters);
  void *execute(void *);

protected:
  static const double DEFAULT_CR;
  static const double DEFAULT_F;
  static const double DEFAULT_K;
  static const string DEFAULT_DE_VARIANT;

private:
  double CR_  ;
  double F_   ;
  double K_   ;
  string DE_Variant_ ; // DE variant (rand/1/bin, rand/1/exp, etc.)
  //TODO: A�adir VALID_TYPES;

};

#endif // __DIFFERENTIAL_EVOLUTION_CROSSOVER__
