//  Spread.cpp
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


#include <Spread.h>


/**
 * Constructor
 * Creates a new instance of a Spread object
 */
Spread::Spread() {
  utils_ = new MetricsUtil();
} // Spread


/**
 * Destructor
 */
Spread::~Spread() {
  delete utils_;
} // ~Spread


bool Spread::compareFront(vector<double> pointOne, vector<double> pointTwo) {

  int value;
  bool result = false;

  LexicoGraphicalComparator * c = new LexicoGraphicalComparator();
  value = c->compare(&pointOne, &pointTwo);
  delete c;

  if (value == -1) {
    result = true;
  }

  return result;

} // compareFront


/** Calculates the Spread metric. Given the front, the true pareto front as
 * <code>double []</code>, and the number of objectives,
 * the method returns the value of the metric.
 *  @param front The front.
 *  @param trueParetoFront The true pareto front.
 *  @param numberOfObjectives The number of objectives.
 */
double Spread::spread(vector <vector<double> > front,
    vector <vector<double> > trueParetoFront, int numberOfObjectives) {

  /**
   * Stores the maximum values of true pareto front.
   */
  vector<double> maximumValue ;

  /**
   * Stores the minimum values of the true pareto front.
   */
  vector<double> minimumValue ;

  /**
   * Stores the normalized front.
   */
  vector <vector<double> > normalizedFront ;

  /**
   * Stores the normalized true Pareto front.
   */
  vector <vector<double> > normalizedParetoFront ;

  // STEP 1. Obtain the maximum and minimum values of the Pareto front
  maximumValue = utils_->getMaximumValues(trueParetoFront, numberOfObjectives);
  minimumValue = utils_->getMinimumValues(trueParetoFront, numberOfObjectives);

  // STEP 2. Get the normalized front and true Pareto fronts
  normalizedFront = utils_->getNormalizedFront(front,
                                               maximumValue,
                                               minimumValue);
  normalizedParetoFront = utils_->getNormalizedFront(trueParetoFront,
                                                     maximumValue,
                                                     minimumValue);

  // STEP 3. Sort normalizedFront and normalizedParetoFront;
  sort(normalizedFront.begin(), normalizedFront.end(), Spread::compareFront);
  sort(normalizedParetoFront.begin(), normalizedParetoFront.end(), Spread::compareFront);

  int numberOfPoints = normalizedFront.size();
  // int numberOfTruePoints = normalizedParetoFront.length;

  // STEP 4. Compute df and dl (See specifications in Deb's description of
  // the metric)
  double df = utils_->distance(normalizedFront[0],normalizedParetoFront[0]);
  double dl = utils_->distance(normalizedFront[normalizedFront.size()-1],
             normalizedParetoFront[normalizedParetoFront.size()-1]);

  double mean = 0.0;
  double diversitySum = df + dl;

  // STEP 5. Calculate the mean of distances between points i and (i - 1).
  // (the poins are in lexicografical order)
  for (int i = 0; i < (normalizedFront.size()-1); i++) {
    mean += utils_->distance(normalizedFront[i],normalizedFront[i+1]);
  } // for

  mean = mean / (double)(numberOfPoints - 1);

  // STEP 6. If there are more than a single point, continue computing the
  // metric. In other case, return the worse value (1.0, see metric's
  // description).
  if (numberOfPoints > 1) {
    for (int i = 0; i < (numberOfPoints -1); i++) {
      diversitySum += fabs(utils_->distance(normalizedFront[i],
                           normalizedFront[i+1]) - mean);
    } // for
    return diversitySum / (df + dl + (numberOfPoints-1)*mean);
  }
  else
    return 1.0;
} // spread
