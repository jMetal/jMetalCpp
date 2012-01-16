/*
  * @file Hypervolume.cpp
  * @author Esteban López
  * @date 13 December 2011
 */

#include <Hypervolume.h>


/**
 * Constructor
 * Creates a new instance of Hypervolume
 */
Hypervolume::Hypervolume() {
  utils_ = new MetricsUtil();
} // Hypervolume


/*
 returns true if 'point1' dominates 'points2' with respect to the
 to the first 'noObjectives' objectives
 */
bool Hypervolume::dominates(double * point1, double * point2, int noObjectives) {

  int i;
  int betterInAnyObjective;

  betterInAnyObjective = 0;
  for (i = 0; i < noObjectives && point1[i] >= point2[i]; i++) {
    if (point1[i] > point2[i]) {
      betterInAnyObjective = 1;
    }
  }

  return ((i >= noObjectives) && (betterInAnyObjective>0));

} // dominates


void Hypervolume::swap(double ** front, int i, int j) {

  double * temp;

  temp = front[i];
  front[i] = front[j];
  front[j] = temp;

} // swap


/* all nondominated points regarding the first 'noObjectives' dimensions
are collected; the points referenced by 'front[0..noPoints-1]' are
considered; 'front' is resorted, such that 'front[0..n-1]' contains
the nondominated points; n is returned */
int Hypervolume::filterNondominatedSet(double ** front,
    int noPoints, int noObjectives) {

  int i, j;
  int n;

  n = noPoints;
  i = 0;

  while (i < n) {
    j = i + 1;
    while (j < n) {
      if (dominates(front[i], front[j], noObjectives)) {
        /* remove point 'j' */
        n--;
        swap(front, j, n);
      } else if (dominates(front[j], front[i], noObjectives)) {
        /* remove point 'i'; ensure that the point copied to index 'i'
           is considered in the next outer loop (thus, decrement i) */
        n--;
        swap(front, i, n);
        i--;
        break;
      } else {
        j++;
      }
    }
    i++;
  }

  return n;

} // filterNondominatedSet


/* calculate next value regarding dimension 'objective'; consider
   points referenced in 'front[0..noPoints-1]' */
double Hypervolume::surfaceUnchangedTo(double ** front,
    int noPoints, int objective) {

  int i;
  double minValue, value;

  if (noPoints < 1) {
    cout << "run-time error" << endl;
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


/* remove all points which have a value <= 'threshold' regarding the
   dimension 'objective'; the points referenced by
   'front[0..noPoints-1]' are considered; 'front' is resorted, such that
   'front[0..n-1]' contains the remaining points; 'n' is returned */
int Hypervolume::reduceNondominatedSet(double ** front, int noPoints, int objective,
       double threshold){

  int n;
  int i;

  n = noPoints;
  for (i = 0; i < n; i++) {
    if (front[i][objective] <= threshold) {
      n--;
      swap(front, i, n);
    }
  }

  return n;

} // ReduceNondominatedSet


double Hypervolume::calculateHypervolume(double ** front,
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
      }
      tempVolume = front[0][0];
    } else {
      tempVolume = calculateHypervolume(front,
                                        noNondominatedPoints,
                                        noObjectives - 1);
    }

    tempDistance = surfaceUnchangedTo(front, n, noObjectives - 1);
    volume += tempVolume * (tempDistance - distance);
    distance = tempDistance;
    n = reduceNondominatedSet(front, n, noObjectives - 1, distance);
  }

  return volume;

} // calculateHypervolume


/* merge two fronts */
double ** Hypervolume::mergeFronts(double ** front1, int sizeFront1,
   double ** front2, int sizeFront2, int noObjectives) {

  int i, j;
  int noPoints;
  double ** frontPtr;

  /* allocate memory */
  noPoints = sizeFront1 + sizeFront2;
  frontPtr = new double[noPoints][noObjectives];
  /* copy points */
  noPoints = 0;
  for (i = 0; i < sizeFront1; i++) {
    for (j = 0; j < noObjectives; j++)
      frontPtr[noPoints][j] = front1[i][j];
    noPoints++;
  }
  for (i = 0; i < sizeFront2; i++) {
    for (j = 0; j < noObjectives; j++)
      frontPtr[noPoints][j] = front2[i][j];
    noPoints++;
  }

  return frontPtr;

} // mergeFronts


/**
 * Returns the hypevolume value of the paretoFront. This method call to the
 * calculate hipervolume one
 * @param paretoFront The pareto front
 * @param paretoTrueFront The true pareto front
 * @param numberOfObjectives Number of objectives of the pareto front
 */
double Hypervolume::hypervolume(double ** paretoFront,
                          double ** paretoTrueFront,
                          int numberOfObjectives) {

  /**
   * Stores the maximum values of true pareto front.
   */
  double * maximumValues;

  /**
   * Stores the minimum values of the true pareto front.
   */
  double * minimumValues;

  /**
   * Stores the normalized front.
   */
  double ** normalizedFront;

  /**
   * Stores the inverted front. Needed for minimization problems
   */
  double ** invertedFront;

  // STEP 1. Obtain the maximum and minimum values of the Pareto front
  maximumValues = utils_->getMaximumValues(paretoTrueFront,numberOfObjectives);
  minimumValues = utils_->getMinimumValues(paretoTrueFront,numberOfObjectives);

  // STEP 2. Get the normalized front
  normalizedFront = utils_->getNormalizedFront(paretoFront,
                                              maximumValues,
                                              minimumValues);

  // STEP 3. Inverse the pareto front. This is needed because of the original
  //metric by Zitzler is for maximization problems
  invertedFront = utils_->invertedFront(normalizedFront);

  // STEP4. The hypervolumen (control is passed to java version of Zitzler code)
  return this->calculateHypervolume(invertedFront,invertedFront.length,numberOfObjectives);

}// hypervolume
