//  SolutionType.h
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

#ifndef __SOLUTION_TYPE__
#define __SOLUTION_TYPE__

#include <Problem.h>
#include <Variable.h>
#include <stddef.h>
#include <string>

class Problem;

/**
 * This class is aimed at defining a Type for every solution.
 * The type of a solution (a.k.a SolutionType) will define the type
 * of the variables composing that solution.
 * Advantages: Flexibility for defining different types of solutions
 * (mixing variable types, etc)
**/
class SolutionType {

protected:
  Problem *problem_;

public:
  SolutionType(Problem *problem);
  virtual ~SolutionType();
  virtual Variable **createVariables() = 0;
  Variable **copyVariables(Variable **vars);

}; // SolutionType

#endif
