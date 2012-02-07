//  MetricsUtil.cpp
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


#include <MetricsUtil.h>
#include <iostream>


using namespace std;


int MetricsUtil::getSumaUno(int i) {

	return (i+1);

}


double *MetricsUtil::getMaximumValues(double **front, int frontSize, int noObjectives) {

	double *maximumValue = new double[noObjectives];
	for (int i = 0; i < noObjectives; i++) {
		maximumValue[i] =- std::numeric_limits<double>::max();
	}

	for (int i =0; i < frontSize; i++ ) {
		for (int j = 0; j < noObjectives; j++) {
			if (front[i][j] > maximumValue[j]) {
				maximumValue[j] = front[i][j];
			}
		}
	}

	return maximumValue;

} // getMaximumValues


double *MetricsUtil::getMinimumValues(double ** front, int frontSize, int noObjectives) {

	double *minimumValue = new double[noObjectives];
	for (int i = 0; i < noObjectives; i++) {
		minimumValue[i] = std::numeric_limits<double>::max();
	}

	for (int i =0; i < frontSize; i++ ) {
		for (int j = 0; j < noObjectives; j++) {
			if (front[i][j] < minimumValue[j]) {
				minimumValue[j] = front[i][j];
			}
		}
	}
	return minimumValue;

} // getMinimumValues


double **MetricsUtil::getNormalizedFront(double **front, int frontSizeX, int frontSizeY,
			double *maximumValue, double *minimumValue) {

	double **normalizedFront = new double*[frontSizeX];
	for (int i = 0; i < frontSizeX; i++) {
		normalizedFront[i] = new double[frontSizeY];
		for (int j = 0; j < frontSizeY; j++) {
			normalizedFront[i][j] = (front[i][j] - minimumValue[j]) /
															(maximumValue[j] - minimumValue[j]);
		}
	}
	return normalizedFront;

} // getNormalizedFront


double **MetricsUtil::invertedFront(double ** front, int frontSizeX, int frontSizeY) {

	double **invertedFront = new double*[frontSizeX];

	for (int i = 0; i < frontSizeX; i++) {
		invertedFront[i] = new double[frontSizeY];
		for (int j = 0; j < frontSizeY; j++) {
			if (front[i][j] <= 1.0 && front[i][j]>= 0.0) {
				invertedFront[i][j] = 1.0 - front[i][j];
			} else if (front[i][j] > 1.0) {
				invertedFront[i][j] = 0.0;
			} else if (front[i][j] < 0.0) {
				invertedFront[i][j] = 1.0;
			}
		}
	}
	return invertedFront;

} // invertedFront
