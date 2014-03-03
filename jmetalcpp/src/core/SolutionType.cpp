//  SolutionType.cpp
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


#include <SolutionType.h>


/**
 * Constructor
 * @param problem The problem to solve
**/
SolutionType::SolutionType(Problem *problem) {
  problem_ = problem;
}

/**
 * Destructor
 */
SolutionType::~SolutionType() { }


/**
 * Copies the decision variables
 * @param decisionVariables
 * @return An array of variables
**/
Variable ** SolutionType::copyVariables(Variable **vars) {
  int numberOfVar = problem_->getNumberOfVariables();
  int var;
  Variable ** variables = new Variable*[numberOfVar];

  if (variables == NULL)  {
    cout << "Error grave: Impossible to reserve memory for allocating a copy of variables" << endl;
    exit(-1);
  }

  for (var = 0; var < numberOfVar; var++) {
    variables[var] = vars[var]->deepCopy();
  }

  return variables;
} // copyVariables
