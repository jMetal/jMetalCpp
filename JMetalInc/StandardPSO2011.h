//  StandardPSO2011.h
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//       Antonio J. Nebro <antonio@lcc.uma.es>
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

#ifndef __STANDARD_PSO_2011__
#define __STANDARD_PSO_2011__

#include <JMetalInc/Algorithm.h>
#include <JMetalInc/Problem.h>
#include <JMetalInc/SolutionSet.h>
#include <JMetalInc/XReal.h>
#include <JMetalInc/Comparator.h>
#include <JMetalInc/Distance.h>
#include <JMetalInc/ObjectiveComparator.h>
#include <JMetalInc/BestSolutionSelection.h>
#include <JMetalInc/AdaptiveRandomNeighborhood.h>

#include <math.h>

/**
 * Class implementing a Standard PSO 2011 algorithm
 */
class StandardPSO2011 : public Algorithm {

private:

  SolutionSet * swarm_;
  int swarmSize_;
  int maxIterations_;
  int iteration_;
  int numberOfParticlesToInform_ ; // Referred a K in the SPSO document
  Solution ** localBest_;
  Solution ** neighborhoodBest_;
  double ** speed_;
  AdaptiveRandomNeighborhood * neighborhood_ ;

  int evaluations_ ;

  /**
   * Comparator object
   */
  Comparator  * comparator_  ;

  Operator * findBestSolution_ ;

  double W_;
  double C_;
  double ChVel_;

  void initParams();
  void deleteParams();
  Solution * getNeighborBest(int i);
  void computeSpeed();
  void computeNewPositions();

public:

  double getW();
  double getC();

  StandardPSO2011(Problem * problem);
  ~StandardPSO2011();
  SolutionSet * execute();

}; // StandardPSO2011

#endif /* __STANDARD_PSO_2011__ */
