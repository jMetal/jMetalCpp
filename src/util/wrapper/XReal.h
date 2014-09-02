//  XReal.h
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

#ifndef XREAL_H_
#define XREAL_H_

#include <Solution.h>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <ArrayReal.h>

/**
 * This class allows to apply a SBX crossover operator using two parent
 * solutions.
**/
class XReal {

public:
  XReal();
  XReal(Solution * solution);
  double getValue(int index);
  void setValue(int index, double value);
  double getLowerBound(int index);
  double getUpperBound(int index);
  int getNumberOfDecisionVariables();
  int size();

private:
  Solution * solution_;
  SolutionType * type_;

};

#endif /* XREAL_H_ */
