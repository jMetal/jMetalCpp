//  BinaryTournament.h
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

#ifndef __BINARY_TOURNAMENT__
#define __BINARY_TOURNAMENT__

#include <SolutionSet.h>
#include <Selection.h>
#include <Comparator.h>
#include <DominanceComparator.h>
#include <PseudoRandom.h>

/**
 * This class implements an binary tournament selection operator
 */
class BinaryTournament : public Selection {

private:
  Comparator * comparator_;

public:
  BinaryTournament(map<string, void *> parameters);
  ~BinaryTournament();
  void *execute(void *);

};

#endif
