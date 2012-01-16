/*
  * @file Hypervolume.h
  * @author Esteban López
  * @date 13 December 2011
 */

#ifndef __HYPERVOLUME__
#define __HYPERVOLUME__


/**
 * This class implements the hypervolume indicator. The code is a C++ version
 * of the original metric implementation by Eckart Zitzler.
 * Reference: E. Zitzler and L. Thiele
 *           Multiobjective Evolutionary Algorithms: A Comparative Case Study
 *           and the Strength Pareto Approach,
 *           IEEE Transactions on Evolutionary Computation, vol. 3, no. 4,
 *           pp. 257-271, 1999.
 */

class Hypervolume {

private:
  MetricsUtil * utils_;
  bool dominates(double * point1, double * point2, int noObjectives);
  void swap(double ** front, int i, int j);
  int filterNondominatedSet(double ** front, int noPoints, int noObjectives);
  double surfaceUnchangedTo(double ** front, int noPoints, int objective);
  int reduceNondominatedSet(double ** front, int noPoints, int objective,
           double threshold);
  double ** mergeFronts(double ** front1, int sizeFront1,
      double ** front2, int sizeFront2, int noObjectives);

public:
  Hypervolume();
  double calculateHypervolume(double ** front, int noPoints, int noObjectives);
  double hypervolume(double ** paretoFront, double ** paretoTrueFront,
                              int numberOfObjectives);

};

#endif /* HYPERVOLUME__ */
