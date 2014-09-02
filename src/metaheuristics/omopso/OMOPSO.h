//  OMOPSO.h
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

#ifndef OMOPSO_H_
#define OMOPSO_H_

#include <Algorithm.h>
#include <SolutionSet.h>

#include <CrowdingArchive.h>
#include <Distance.h>
#include <EpsilonDominanceComparator.h>
#include <NonDominatedSolutionList.h>
#include <PseudoRandom.h>
#include <XReal.h>

/**
 * This class implements an asynchronous version of OMOPSO algorithm
 */
class OMOPSO : public Algorithm {
    
private:
    
  /**
   * Stores the number of particles used
   */
  int particlesSize;

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
   * Stores the perturbation used by the non-uniform mutation
   */
  double perturbation;

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
  CrowdingArchive *leaders;

  /**
   * Stores the epsilon-archive
   */
  NonDominatedSolutionList *eArchive;

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
   * Stores a operator for uniform mutations
   */
  Operator *uniformMutation;

  /**
   * Stores a operator for non uniform mutations
   */
  Operator *nonUniformMutation;

  /**
   * eta_ value
   */
  double eta = 0.0075;

  /**
   * Initialize all parameter of the algorithm
   */
  void initParams();

  /**
   * Free all the memory reserved by the algorithm
   */
  void deleteParams();

  /**
   * Update the speed of each particle
   */
  void computeSpeed();

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
   * Constructor
   * @param problem Problem to solve
   */
  OMOPSO(Problem *problem);

  /**
   * Runs of the SMPSO algorithm.
   * @return a <code>SolutionSet</code> that is a set of non dominated solutions
   * as a result of the algorithm execution
   */
  SolutionSet *execute();
    
};

#endif /* OMOPSO_H_ */
