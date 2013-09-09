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

#include <limits>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <SolutionSet.h>
#include <NonDominatedSolutionList.h>

using namespace std;

/**
  * @class MetricsUtil
  * @brief This class provides some utilities to compute quality indicators
**/

class MetricsUtil {

public:
	vector< vector<double> > readFront(string path);
	vector<double> getMaximumValues(vector< vector<double> > front, int noObjectives);
	vector<double> getMinimumValues(vector< vector<double> > front, int noObjectives);
	double distance(vector<double> a, vector<double> b);
	double distanceToClosedPoint(vector<double> point, vector< vector<double> > front);
	double distanceToNearestPoint(vector<double> point, vector< vector<double> > front);
	vector< vector<double> > getNormalizedFront(vector< vector<double> > front,
	    vector<double> maximumValue, vector<double> minimumValue);
	vector< vector<double> > invertedFront(vector< vector<double> > front);
	SolutionSet * readNonDominatedSolutionSet(string path);
	void readNonDominatedSolutionSet(string path, NonDominatedSolutionList * solutionSet);
};

#endif /* __METRICSUTIL__ */
