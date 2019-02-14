//  MetricsUtil.h
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

#ifndef __METRICSUTIL__
#define __METRICSUTIL__

#include "JMetalHeader.h"
#include <limits>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <math.h>
#include <SolutionSet.h>
#include <NonDominatedSolutionList.h>

using namespace JMetal;

/**
  * @class MetricsUtil
  * @brief This class provides some utilities to compute quality indicators
**/

class MetricsUtil
{

public:
    MatrixOfDouble readFront(std::string path);
    VectorOfDouble getMaximumValues(MatrixOfDouble front, int noObjectives);
    VectorOfDouble getMinimumValues(MatrixOfDouble front, int noObjectives);
    double distance(VectorOfDouble a, VectorOfDouble b);
    double distanceToClosedPoint(VectorOfDouble point, MatrixOfDouble front);
    double distanceToNearestPoint(VectorOfDouble point, MatrixOfDouble front);
    MatrixOfDouble getNormalizedFront(MatrixOfDouble front,
            VectorOfDouble maximumValue, VectorOfDouble minimumValue);
    MatrixOfDouble invertedFront(MatrixOfDouble front);
    SolutionSet * readNonDominatedSolutionSet(std::string path);
    void readNonDominatedSolutionSet(std::string path, NonDominatedSolutionList * solutionSet);
};

#endif /* __METRICSUTIL__ */
