//  Griewank.h
//
//  Authors:
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

#ifndef __GRIEWANK__
#define __GRIEWANK__

#include <Problem.h>
#include <math.h>
#include <RealSolutionType.h>
#include <BinaryRealSolutionType.h>
#include <Solution.h>

/**
  * @class Griewank
  * @brief Class representing problem Griewank
 **/
class Griewank : public Problem {
   
public:
  Griewank(string solutionType, int numberOfVariables = 10);
	~Griewank();
	void evaluate(Solution *solution);
};

#endif /* __GRIEWANK__ */
