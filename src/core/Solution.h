//  Solution.h
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
//       Juan J. Durillo <durillo@lcc.uma.es>
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

#ifndef __SOLUTION__
#define __SOLUTION__

#include <string>
#include <sstream>
#include <limits>
#include <stdlib.h>
#include <stddef.h>
#include "Problem.h"
#include "Variable.h"
#include "SolutionType.h"


//using namespace std;
//
class Problem ;
class Variable ;
class SolutionType ;

/**
 * @class Solution
 * @brief Class representing a solution for a problem
**/
class Solution {

private:
  Problem * problem_;
  SolutionType * type_;
  Variable ** variable_;
  int numberOfVariables_;
  double *objective_;
  int numberOfObjectives_;
  double fitness_;
  bool marked_;
  int rank_;
  double overallConstraintViolation_;
  int numberOfViolatedConstraints_;
  int location_;
  double kDistance_;
  double crowdingDistance_;
  double distanceToSolutionSet_;
    
public:
  Solution ();
  Solution (int numberOfObjectives);
  Solution (Problem * problem);
  //getNewsolution (Problem *problem);
  Solution(Problem * problem, Variable ** variables);
  Solution (Solution * solution);

  ~Solution();

  void setDistanceToSolutionSet(double distance);
  double getDistanceToSolutionSet();
  void setKDistance(double distance);
  double getKDistance();
  void setCrowdingDistance(double distance);
  double getCrowdingDistance();
  void setFitness(double fitness);
  double getFitness();
  void setObjective(int i, double value);
  double getObjective(int i);
  int getNumberOfObjectives();
  int getNumberOfVariables();
  string toString();
  Variable ** getDecisionVariables();
  void setDecisionVariables(Variable ** variables);
  bool isMarked();
  void mark();
  void unMark();
  void setRank(int value);
  int getRank();
  void setOverallConstraintViolation(double value);
  double getOverallConstraintViolation();
  void setNumberOfViolatedConstraints(int value);
  int getNumberOfViolatedConstraints();
  void setLocation(int location);
  int getLocation();
  void setType(SolutionType * type);
  SolutionType *getType();
  double getAggregativeValue();
  Problem * getProblem() ;
  //int getNumberOfBits();

};

#endif
