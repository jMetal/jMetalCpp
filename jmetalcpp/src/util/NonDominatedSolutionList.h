//  NonDominatedSolutionList.h
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

#ifndef __NONDOMINATEDSOLUTIONLIST__
#define __NONDOMINATEDSOLUTIONLIST__

#include <Comparator.h>
#include <DominanceComparator.h>
#include <SolutionComparator.h>
#include <SolutionSet.h>

/**
 * This class implements an unbound list of non-dominated solutions
 */

class NonDominatedSolutionList : public SolutionSet {

private:
  Comparator * dominance;
  Comparator * equal;

public:
  NonDominatedSolutionList();
  NonDominatedSolutionList(Comparator *dominance);
  ~NonDominatedSolutionList();

  bool add(Solution *solution);

}; // NonDominatedSolutionList

#endif /* __NONDOMINATEDSOLUTIONLIST__ */
