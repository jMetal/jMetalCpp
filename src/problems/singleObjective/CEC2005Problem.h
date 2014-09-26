//  CEC2005Problem.h
//
//  Authors:
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

#ifndef __CEC_2005_PROBLEM__
#define __CEC_2005_PROBLEM__

#include <Problem.h>
#include <Solution.h>
#include <RealSolutionType.h>
#include <BinaryRealSolutionType.h>

#include <Benchmark.h>
#include <TestFunc.h>

#include <math.h>

/**
  * @class CEC2005Problem
  * @brief Class representing all problems in CEC2005
 **/
class CEC2005Problem : public Problem {

private:
  TestFunc * testFunction_ ;
  static const double PI;

public:
  CEC2005Problem(string solutionType, int problemID, int numberOfVariables = 10);
	~CEC2005Problem();
	void evaluate(Solution *solution);
};

#endif /* __CEC_2005_PROBLEM__ */
