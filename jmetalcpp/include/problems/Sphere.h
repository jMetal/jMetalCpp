//  Sphere.h
//
//  Authors:
//       Antonio J. Nebro <antonio@lcc.uma.es>
//       Juan J. Durillo <durillo@lcc.uma.es>
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

#ifndef __SPHERE__
#define __SPHERE__

#include <Problem.h>
#include <math.h>
#include <RealSolutionType.h>
#include <Solution.h>

/**
  * @class Sphere
  * @brief Class representing problem Sphere
 **/
class Sphere : public Problem {
   
public:
	Sphere(string solutionType, int numberOfVariables = 10);
	~Sphere();
	void evaluate(Solution *solution);
};

#endif
