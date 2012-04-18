//  Hypervolume.cpp
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

#include <Hypervolume.h>


/**
 * Constructor
 * Creates a new instance of Hypervolume
 */
Hypervolume::Hypervolume() {
  utils_ = new MetricsUtil();
} // Hypervolume


/**
 * Destructor
 */
Hypervolume::~Hypervolume() {
  delete utils_;
} // ~Hypervolume


/*
 * returns true if 'point1' dominates 'points2' with respect to the
 * to the first 'noObjectives' objectives
 */
bool Hypervolume::dominates(vector<double> point1, vector<double> point2,
    int noObjectives) {

  int i;
  bool betterInAnyObjective = false;

  for (i = 0; i < noObjectives && point1[i] >= point2[i]; i++) {
    if (point1[i] > point2[i]) {
      betterInAnyObjective = true;
    } // if
  } // for

  return ((i >= noObjectives) && betterInAnyObjective);

} // dominates


void Hypervolume::swap(vector< vector<double> > * front, int i, int j) {

  vector<double> temp;

  temp = front->at(i);
  front->at(i) = front->at(j);
  front->at(j) = temp;

} // swap


/*
 * all nondominated points regarding the first 'noObjectives' dimensions
 * are collected; the points referenced by 'front[0..noPoints-1]' are
 * considered; 'front' is resorted, such that 'front[0..n-1]' contains
 * the nondominated points; n is returned
 */
int Hypervolume::filterNondominatedSet(vector< vector<double> > * front,
    int noPoints, int noObjectives) {

  int i, j;
  int n;

  n = noPoints;
  i = 0;

  while (i < n) {
    j = i + 1;
    while (j < n) {
      if (dominates(front->at(i), front->at(j), noObjectives)) {
        /* remove point 'j' */
        n--;
        swap(front, j, n);
      } else if (dominates(front->at(j), front->at(i), noObjectives)) {
        /* remove point 'i'; ensure that the point copied to index 'i'
           is considered in the next outer loop (thus, decrement i) */
        n--;
        swap(front, i, n);
        i--;
        break;
      } else {
        j++;
      }
    } // while
    i++;
  } // while

  return n;

} // filterNondominatedSet


/*
 * calculate next value regarding dimension 'objective'; consider
 * points referenced in 'front[0..noPoints-1]'
 */
double Hypervolume::surfaceUnchangedTo(vector< vector<double> > front,
    int noPoints, int objective) {

  int i;
  double minValue, value;

  if (noPoints < 1) {
    cout << "run-time error" << endl;
    exit(-1);
  }

  minValue = front[0][objective];
  for (i = 1; i < noPoints; i++) {
    value = front[i][objective];
    if (value < minValue) {
      minValue = value;
    }
  }
  
  return minValue;

} // surfaceUnchangedTo


/*
 * remove all points which have a value <= 'threshold' regarding the
 * dimension 'objective'; the points referenced by
 * 'front[0..noPoints-1]' are considered; 'front' is resorted, such that
 * 'front[0..n-1]' contains the remaining points; 'n' is returned
 */
int Hypervolume::reduceNondominatedSet(vector< vector<double> > * front,
    int noPoints, int objective, double threshold) {

  int n;
  int i;

  n = noPoints;
  for (i = 0; i < n; i++) {
    if (front->at(i)[objective] <= threshold) {
      n--;
      swap(front, i, n);
    } // if
  } // for

  return n;

} // ReduceNondominatedSet


double Hypervolume::calculateHypervolume(vector< vector<double> > * front,
    int noPoints, int noObjectives){

  int n;
  double volume, distance;

  volume = 0;
  distance = 0;
  n = noPoints;
  while (n > 0) {

    int noNondominatedPoints;
    double tempVolume, tempDistance;

    noNondominatedPoints = filterNondominatedSet(front, n, noObjectives - 1);
    tempVolume = 0;
    if (noObjectives < 3) {
      if (noNondominatedPoints < 1) {
        cout << "run-time error" << endl;
        exit(-1);
      } // if
      tempVolume = front->at(0)[0];
    } else {
      tempVolume = calculateHypervolume(front,
                                        noNondominatedPoints,
                                        noObjectives - 1);
    } // if

    tempDistance = surfaceUnchangedTo(*front, n, noObjectives - 1);
    volume += tempVolume * (tempDistance - distance);
    distance = tempDistance;
    n = reduceNondominatedSet(front, n, noObjectives - 1, distance);
  } // while

  return volume;

} // calculateHypervolume


/*
 * merge two fronts
 */
vector< vector<double> > Hypervolume::mergeFronts(vector< vector<double> > front1,
    vector< vector<double> > front2) {

  int i, j;
  int noPoints;
  vector< vector<double> > frontPtr;

  for (i = 0; i < front1.size(); i++) {
    frontPtr.push_back(front1[i]);
  }
  for (i = 0; i < front2.size(); i++) {
    frontPtr.push_back(front2[i]);
  }

  return frontPtr;

} // mergeFronts


/**
 * Returns the hypervolume value of the paretoFront. This method call to the
 * calculate hipervolume one
 * @param paretoFront The pareto front
 * @param paretoTrueFront The true pareto front
 * @param numberOfObjectives Number of objectives of the pareto front
 */
double Hypervolume::hypervolume(vector< vector<double> > paretoFront,
    vector< vector<double> > paretoTrueFront, int numberOfObjectives) {

  /**
   * Stores the maximum values of true pareto front.
   */
  vector<double> maximumValues;

  /**
   * Stores the minimum values of the true pareto front.
   */
  vector<double> minimumValues;

  /**
   * Stores the normalized front.
   */
  vector< vector<double> > normalizedFront;

  /**
   * Stores the inverted front. Needed for minimization problems
   */
  vector< vector<double> > invertedFront;

  // STEP 1. Obtain the maximum and minimum values of the Pareto front
  maximumValues = utils_->getMaximumValues(paretoTrueFront, numberOfObjectives);
  minimumValues = utils_->getMinimumValues(paretoTrueFront, numberOfObjectives);

  // STEP 2. Get the normalized front
  normalizedFront = utils_->getNormalizedFront(paretoFront,
                                              maximumValues,
                                              minimumValues);

  // STEP 3. Inverse the pareto front. This is needed because of the original
  //metric by Zitzler is for maximization problems
  invertedFront = utils_->invertedFront(normalizedFront);

  // STEP4. The hypervolume (control is passed to java version of Zitzler code)
  return this->calculateHypervolume(&invertedFront,invertedFront.size(),numberOfObjectives);

}// hypervolume
