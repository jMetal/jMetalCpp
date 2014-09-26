//  Problem.h
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

#ifndef __PROBLEM__
#define __PROBLEM__

#include <string>
#include <iostream>
#include <SolutionType.h>
#include <Solution.h>
#include <stddef.h>

using namespace std;

class SolutionType;
class Solution;

/**
 * Abstract class representing a multiobjective optimization problem
 */
class Problem {

private:
  static const int DEFAULT_PRECISSION;

protected:
  int numberOfVariables_;
  int numberOfObjectives_;
  int numberOfConstraints_;
  string problemName_;
  SolutionType *solutionType_;
  double *lowerLimit_;
  double *upperLimit_;
  int *precision_;
  int *length_;
   
public:
  Problem();
  Problem(SolutionType * solutionType);
  virtual ~Problem() = 0;
  int getNumberOfVariables();
  void setNumberOfVariables(int numberOfVariables);
  int getNumberOfObjectives();
  void setNumberOfObjectives(int numberOfObjectives);
  double getLowerLimit(int i);
  double getUpperLimit(int i);
  virtual void evaluate(Solution * solution) = 0;
  int getNumberOfConstraints();
  virtual void evaluateConstraints(Solution * solution);
  int getPrecision(int var);
  int * getPrecision();
  void setPrecision(int * precision);
  int getLength(int var);
  void setSolutionType(SolutionType * type);
  SolutionType * getSolutionType();
  string getName();
  int getNumberOfBits();

}; // Problem

#endif
