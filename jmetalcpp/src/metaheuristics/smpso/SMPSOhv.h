//  SMPSOhv.h
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//
//  Copyright (c) 2014 Antonio J. Nebro
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

#ifndef SMPSO_HV_H_
#define SMPSO_HV_H_

#include <Algorithm.h>
#include <SolutionSet.h>

#include <CrowdingDistanceComparator.h>
#include <Distance.h>
#include <FastHypervolumeArchive.h>
#include <Hypervolume.h>
#include <XReal.h>

/**
 * This class implements the SMPSOhv algorithm described in:
 * A.J Nebro, J.J. Durillo, C.A. Coello Coello. Analysis of Leader Selection Strategies in a
 * Multi-Objective Particle Swarm Optimizer. 2013 IEEE Congress on Evolutionary Computation. June 2013
 */
class SMPSOhv : public Algorithm {

private:

  /**
   * Stores the number of particles used
   */
  int swarmSize;

  /**
   * Stores the maximum size for the archive
   */
  int archiveSize;

  /**
   * Stores the maximum number of iteration_
   */
  int maxIterations;

  /**
   * Stores the current number of iteration_
   */
  int iteration;

  /**
   * Stores the particles
   */
  SolutionSet *particles;

  /**
   * Stores the best solutions founds so far for each particles
   */
  Solution **best;

  /**
   * Stores the leaders
   */
  FastHypervolumeArchive *leaders;

  /**
   * Stores the speed of each particle
   */
  double **speed;

  /**
   * Stores a comparator for checking dominance
   */
  Comparator *dominance;

  /**
   * Stores a comparator for crowding checking
   */
  Comparator *crowdingDistanceComparator;

  /**
   * Stores a <code>Distance</code> object
   */
  Distance *distance;

  /**
   * Stores a operator for polynomial mutations
   */
  Operator *polynomialMutation;

  //QualityIndicator *indicators; // QualityIndicator object

  double r1Max;
  double r1Min;
  double r2Max;
  double r2Min;
  double C1Max;
  double C1Min;
  double C2Max;
  double C2Min;
  double WMax;
  double WMin;
  double ChVel1;
  double ChVel2;

  double trueHypervolume;
  Hypervolume *hy;
  SolutionSet *trueFront;
  double *deltaMax;
  double *deltaMin;
  bool success;

  /**
   * Initialize all parameter of the algorithm
   */
  void initParams();

  /**
   * Free all the memory reserved by the algorithm
   */
  void deleteParams();

  /**
   * Adaptive inertia
   */
  double inertiaWeight(int iter, int miter, double wma, double wmin);

  /**
   * constriction coefficient (M. Clerc)
   */
  double constrictionCoefficient(double c1, double c2);

  /**
   * velocity bounds
   */
  double velocityConstriction(double v, double *deltaMax,
        double *deltaMin, int variableIndex,
        int particleIndex);

  /**
   * Update the speed of each particle
   */
  void computeSpeed(int iter, int miter);

  /**
   * Update the position of each particle
   */
  void computeNewPositions();

  /**
   * Apply a mutation operator to some particles in the swarm
   */
  void mopsoMutation(int actualIteration, int totalIterations);

public:

  /**
   * Constructor.
   * @param problem Problem to solve
   */
  SMPSOhv(Problem *problem);

  /**
   * Runs of the SMPSO algorithm.
   * @return a <code>SolutionSet</code> that is a set of non dominated solutions
   * as a result of the algorithm execution
   * @throws JMException
   */
  SolutionSet *execute();

};

#endif /* SMPSO_HV_H_ */
