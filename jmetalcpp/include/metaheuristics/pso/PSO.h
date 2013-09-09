//  PSO.h
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
#include <math.h>
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
  void initParams();
  void deleteParams();

public:
  PSO(Problem * problem);
  SolutionSet * execute();

};

#endif /* __PSO__ */
