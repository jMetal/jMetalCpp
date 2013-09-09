//  DifferentialEvolutionSelection.h
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

#ifndef __DIFFERENTIAL_EVOLUTION_SELECTION__
#define __DIFFERENTIAL_EVOLUTION_SELECTION__

#include <Selection.h>
#include <Solution.h>
#include <SolutionSet.h>
#include <PseudoRandom.h>

/**
 * Class implementing the selection operator used in DE: three different solutions
 * are returned from a population.
 */
class DifferentialEvolutionSelection : public Selection {

public:
  DifferentialEvolutionSelection(map<string, void *> parameters);
  void *execute(void *);

};

#endif // __DIFFERENTIAL_EVOLUTION_SELECTION__
