//  BinarySolutionType.cpp
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


#include <BinarySolutionType.h>
#include <cstddef>


/**
 * Constructor
 * @param problem
 */
BinarySolutionType::BinarySolutionType(Problem *problem)
: SolutionType(problem) { }


/**
 * Creates the variables of the solution
 * @param decisionVariables
 */
Variable **BinarySolutionType::createVariables() {
  //BinaryReal * binaryReal;

  Variable **variables = new Variable*[problem_->getNumberOfVariables()]; //malloc(sizeof(Real) * problem->getNumberOfVariables());
//  if (problem_->variableType_ ==  NULL) {
//    cout << "Error grave: Impossible to reserve memory for variable type" << endl;
//    exit(-1);
//  }
   
  for (int var = 0; var < problem_->getNumberOfVariables(); var++)
    variables[var] = new Binary(problem_->getLength(var));
  /*
  for (int var = 0; var < problem_->getNumberOfVariables(); var++) {
    if (problem_->getPrecision() == NULL) {
      int * precision = new int[problem_->getNumberOfVariables()] ;
      for (int i = 0; i < problem_->getNumberOfVariables(); i++)
        precision[i] = BinaryReal::DEFAULT_PRECISION ;
      problem_->setPrecision(precision) ;
    } // if
    variables[var] = new BinaryReal(problem_->getPrecision(var),
                                    problem_->getLowerLimit(var),
                                    problem_->getUpperLimit(var));
  }
  */
/*
  Variable[]  variables = new Variable[problem_.getNumberOfVariables()];

  for (int var = 0; var < problem_.getNumberOfVariables(); var++)
    variables[var] = new Binary(problem_.getLength(var));

  return variables ;
*/
  return variables;
} // createVariables
