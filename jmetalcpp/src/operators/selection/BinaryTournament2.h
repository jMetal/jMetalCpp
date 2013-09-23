//  BinaryTournament2.h
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

#ifndef __BINARY_TOURNAMENT_2__
#define __BINARY_TOURNAMENT_2__

#include <SolutionSet.h>
#include <Selection.h>
#include <Comparator.h>
#include <PermutationUtility.h>
#include <DominanceComparator.h>

/**
 * This class implements an operator for binary selections using the same code
 * in Deb's NSGA-II implementation
 */
class BinaryTournament2 : public Selection {

private:
  Comparator * dominance_;
  int * a_;
  int index_;

public:
  BinaryTournament2(map<string, void *> parameters);
  ~BinaryTournament2();
  void *execute(void *);

};

#endif
