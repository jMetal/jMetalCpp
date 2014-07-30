//  SMPSOD.h
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

#ifndef SMPSOD_H_
#define SMPSOD_H_

#include <Algorithm.h>
#include <SolutionSet.h>

#include <Hypervolume.h>
#include <PseudoRandom.h>
#include <UtilsMOEAD.h>
#include <XReal.h>

#include <math.h>
#include <string.h>

/**
 * SMPSOD11
 */
class SMPSOD : public Algorithm {

private:

  /**
   * Stores the number of particles used
   */
  int particlesSize;

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
   * Stores the best solutions found so far for each particles
   */
  Solution **lBest;

  /**
   * Stores the global best solutions found so far for each particles
   */
  Solution **gBest;

  /**
   * Stores the speed of each particle
   */
  double **speed;

  // Begin MOEA/D parameters.

  /*
   * Z vector (ideal point)
   */
  double *z;

  /**
   * Lambda vectors
   */
  double **lambda;

  /**
   * T: neighbor size
   */
  int T;

  /**
   * Neighborhood
   */
  int **neighborhood;

  /**
   * delta: probability that parent solutions are selected from neighborhood
   */
  double delta;

  /**
   * nr: maximal number of solutions replaced by each child solution
   */
  int nr;

  string functionType = "_TCHE"; //"_PBI";//"_AGG";

  // END MOEA/D parameters.

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

  double *deltaMax;
  double *deltaMin;

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

  void initUniformWeight();
  void initNeighborhood();
  void initIdealPoint();
  void updateReference(Solution *solution);
  void updateGlobalBest(int solution, int type);
  void updateLocalBest(Solution *indiv, int id, int type);
  double fitnessFunction(Solution *sol, double *lambda);

public:

  /**
   * Constructor.
   * @param problem Problem to solve
   */
  SMPSOD(Problem *problem);

  /**
   * Runs of the SMPSO algorithm.
   * @return a <code>SolutionSet</code> that is a set of non dominated solutions
   * as a result of the algorithm execution
   * @throws JMException
   */
  SolutionSet *execute();

};

#endif /* SMPSOD_H_ */
