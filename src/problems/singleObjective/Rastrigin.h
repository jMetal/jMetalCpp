//  Rastrigin.h
//
//  Authors:
//       Antonio J. Nebro <antonio@lcc.uma.es>
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

#ifndef __RASTRIGIN__
#define __RASTRIGIN__

#include <Problem.h>
#include <math.h>
#include <RealSolutionType.h>
#include <Solution.h>

/**
  * @class Rastrigin
  * @brief Class representing problem Rastrigin
 **/
class Rastrigin : public Problem {
   
public:
	Rastrigin(string solutionType, int numberOfVariables = 10);
	~Rastrigin();
	void evaluate(Solution *solution);
  
private:
  static const double PI;
  
};

#endif /* __RASTRIGIN__ */
