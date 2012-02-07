//  MetricsUtil.h
//
//  Author:
//       Esteban López <esteban@lcc.uma.es>
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

/**
  * @class MetricsUtil
  * @brief This class provides some utilities to compute quality indicators
**/

class MetricsUtil {
private:
  int populationSize_;
  //int maxEvaluations_;
  //QualityIndicator *indicators_;
  //Problem *problem_;
public:
	int getSumaUno(int i);
	//TODO: double **readFront(string path);
	double *getMaximumValues(double **front, int frontSize, int noObjectives);
	double *getMinimumValues(double **front, int frontSize, int noObjectives);
	//TODO: double distance(double *a, double *b);
	//TODO: double distanceToClosedPoint(double *point, double **front);
	//TODO: double distanceToNearestPoint(double *point, double **front);
	double **getNormalizedFront(double **front, int frontSizeX, int frontSizeY,
			double *maximumValue, double *minimumValue);
	double **invertedFront(double **front, int frontSizeX, int frontSizeY);
	//TODO: SolutionSet readNonDominatedSolutionSet(string path);
};

#endif /* __METRICSUTIL__ */
