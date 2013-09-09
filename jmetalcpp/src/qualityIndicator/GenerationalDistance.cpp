//  GenerationalDistance.cpp
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


#include <GenerationalDistance.h>

/*
 * This is the pow used for the distances
 */
const double GenerationalDistance::pow_ = 2.0;


/**
 * Constructor.
 * Creates a new instance of the generational distance metric.
 */
GenerationalDistance::GenerationalDistance() {
  utils_ = new MetricsUtil();
} // GenerationalDistance


/**
 * Destructor
 */
GenerationalDistance::~GenerationalDistance() {
  delete utils_;
} // ~GenerationalDistance


/**
 * Returns the generational distance value for a given front
 * @param front The front
 * @param trueParetoFront The true pareto front
 */
double GenerationalDistance::generationalDistance(vector< vector<double> > front,
      vector< vector<double> > trueParetoFront, int numberOfObjectives) {

  /**
   * Stores the maximum values of true pareto front.
   */
  vector<double> maximumValue;

  /**
   * Stores the minimum values of the true pareto front.
   */
  vector<double> minimumValue;

  /**
   * Stores the normalized front.
   */
  vector< vector<double> > normalizedFront;

  /**
   * Stores the normalized true Pareto front.
   */
  vector< vector<double> > normalizedParetoFront ;

  // STEP 1. Obtain the maximum and minimum values of the Pareto front
  maximumValue = utils_->getMaximumValues(trueParetoFront, numberOfObjectives);
  minimumValue = utils_->getMinimumValues(trueParetoFront, numberOfObjectives);

  // STEP 2. Get the normalized front and true Pareto fronts
  normalizedFront       = utils_->getNormalizedFront(front,
                                                maximumValue,
                                                minimumValue);
  normalizedParetoFront = utils_->getNormalizedFront(trueParetoFront,
                                                maximumValue,
                                                minimumValue);

  // STEP 3. Sum the distances between each point of the front and the
  // nearest point in the true Pareto front
  double sum = 0.0;
  for (int i = 0; i < front.size(); i++)
    sum += pow(utils_->distanceToClosedPoint(normalizedFront[i],
                                             normalizedParetoFront),
                                             pow_);


  // STEP 4. Obtain the sqrt of the sum
  sum = pow(sum,1.0/pow_);

  // STEP 5. Divide the sum by the maximum number of points of the front
  double generationalDistance = sum / normalizedFront.size();

  return generationalDistance;

} // generationalDistance
