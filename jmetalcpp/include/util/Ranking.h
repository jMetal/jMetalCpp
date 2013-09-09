//  Ranking.h
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

#ifndef __RANKING__
#define __RANKING__

#include <SolutionSet.h>
#include <Solution.h>
#include <DominanceComparator.h>
#include <OverallConstraintViolationComparator.h>
#include <vector>

/**
 * This class implements some facilities for ranking solutions.
 * Given a <code>SolutionSet</code> object, their solutions are ranked
 * according to scheme proposed in NSGA-II; as a result, a set of subsets
 * are obtained. The subsets are numbered starting from 0 (in NSGA-II, the
 * numbering starts from 1); thus, subset 0 contains the non-dominated
 * solutions, subset 1 contains the non-dominated solutions after removing those
 * belonging to subset 0, and so on.
 */
class Ranking {

private:
  SolutionSet * solutionSet_;
  SolutionSet ** ranking_;
  int numberOfSubfronts_;
  DominanceComparator * dominance_;
  OverallConstraintViolationComparator * constraint_;

public:
  Ranking (SolutionSet * solutionSet);
  ~Ranking();
  SolutionSet * getSubfront(int rank);
  int getNumberOfSubfronts();

};

#endif
