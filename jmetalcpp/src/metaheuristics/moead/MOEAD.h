//  MOEAD.h
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

#ifndef __MOEAD__
#define __MOEAD__

#include <Algorithm.h>
#include <Problem.h>
#include <SolutionSet.h>

#include <UtilsMOEAD.h>
#include <PseudoRandom.h>

/**
 * This class implements the MOEA/D algorithm.
 */

class MOEAD : public Algorithm {
    
private:

  /**
   * Stores the population size
   */
  int populationSize_;
  /**
   * Stores the population
   */
  SolutionSet * population_;
  /**
   * Z vector (ideal point)
   */
  double * z_;
  /**
   * Lambda vectors
   */
  double ** lambda_;
  /**
   * T: neighbour size
   */
  int T_;
  /**
   * Neighborhood
   */
  int ** neighborhood_;
  /**
   * delta: probability that parent solutions are selected from neighbourhood
   */
  double delta_;
  /**
   * nr: maximal number of solutions replaced by each child solution
   */
  int nr_;
  Solution ** indArray_;
  string functionType_;
  int evaluations_;
  /**
   * Operators
   */
  Operator * crossover_;
  Operator * mutation_;

  string dataDirectory_;
  
  void initUniformWeight();
  void initNeighborhood();
  void initPopulation();
  void initIdealPoint();
  void matingSelection(vector<int> &list, int cid, int size, int type);
  void updateReference(Solution * individual);
  void updateProblem(Solution * indiv, int id, int type);
  double fitnessFunction(Solution * individual, double * lambda);
  void deleteParams();

public:
  MOEAD(Problem * problem);
  SolutionSet * execute();
};

#endif /* __MOEAD__ */

