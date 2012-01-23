/*
 * @file PSO.h
 * @author Esteban López
 * @date 23 January 2012
 */

#ifndef __PSO__
#define __PSO__

#include <Algorithm.h>
#include <BestSolutionSelection.h>
#include <ObjectiveComparator.h>
#include <Problem.h>
//#include <QualityIndicator.h>
#include <SolutionSet.h>
#include <XReal.h>
#include <PseudoRandom.h>
#include <Math.h>
#include <string>

/**
 * Class implementing a single-objective PSO algorithm
 */

class PSO : public Algorithm {

private:

  /**
   * Stores the number of particles_ used
   */
  int particlesSize_;
  /**
   * Stores the maximum number of iteration_
   */
  int maxIterations_;
  /**
   * Stores the current number of iteration_
   */
  int iteration_;
  /**
   * Stores the particles
   */
  SolutionSet * particles_;
  /**
   * Stores the local best solutions found so far for each particles
   */
  Solution ** localBest_;
  /**
   * Stores the global best solution found
   */
  Solution * globalBest_;
  /**
   * Stores the speed_ of each particle
   */
  double ** speed_;
  /**
   * Stores a operator for non uniform mutations
   */
  Operator * polynomialMutation_;

  int evaluations_ ;

  /**
   * Comparator object
   */
  Comparator * comparator_  ;

  Operator * findBestSolution_ ;

  double r1Max_;
  double r1Min_;
  double r2Max_;
  double r2Min_;
  double C1Max_;
  double C1Min_;
  double C2Max_;
  double C2Min_;
  double WMax_;
  double WMin_;
  double ChVel1_;
  double ChVel2_;

  SolutionSet * trueFront_;
  double * deltaMax_;
  double * deltaMin_;
  bool success_;

  double inertiaWeight(int iter, int miter, double wmax,
                                             double wmin);
  double constrictionCoefficient(double c1, double c2);
  double velocityConstriction(double v, double * deltaMax,
                                        double * deltaMin,
                                        int variableIndex,
                                        int particleIndex);
  void computeSpeed(int iter, int miter);
  void computeNewPositions();
  void mopsoMutation(int actualIteration, int totalIterations);

public:
  PSO(Problem * problem);
  void initParams();
  SolutionSet * execute();
};

#endif /* __PSO__ */
