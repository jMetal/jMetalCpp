//  Distance.h
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

#ifndef __DISTANCE__
#define __DISTANCE__

#include <SolutionSet.h>
#include <Solution.h>
#include <float.h>
#include <ObjectiveComparator.h>
#include <math.h>

using namespace std;


/**
 * This class implements some utilities for calculating distances
 */
class Distance {

public:
  Distance();
  double ** distanceMatrix(SolutionSet * solutionSet);
  double distanceToSolutionSetInObjectiveSpace(Solution * solution,
                                               SolutionSet * solutionSet);
  double distanceToSolutionSetInSolutionSpace(Solution * solution,
                                              SolutionSet * solutionSet);
  double distanceBetweenSolutions(Solution * solutionI, Solution * solutionJ);
  double distanceBetweenObjectives(Solution * solutionI, Solution * solutionJ);
  void crowdingDistanceAssignment(SolutionSet * solutionSet, int nObjs);

};


#endif
