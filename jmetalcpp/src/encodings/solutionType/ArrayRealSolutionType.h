//  ArrayRealSolutionType.h
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

#ifndef __ARRAY_REAL_SOLUTION_TYPE__
#define __ARRAY_REAL_SOLUTION_TYPE__

#include <SolutionType.h>
#include <ArrayReal.h>

/**
  * Class representing the solution type of solutions composed of an ArrayReal
  * variable
  */
class ArrayRealSolutionType : public SolutionType {

public:
  ArrayRealSolutionType(Problem *problem);
  Variable **createVariables();
  Variable **copyVariables(Variable ** vars);

};

#endif
