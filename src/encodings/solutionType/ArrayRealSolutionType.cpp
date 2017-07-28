//  ArrayRealSolutionType.cpp
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


#include <ArrayRealSolutionType.h>
#include <cstddef>


/**
 * Constructor
 * @param problem
 */
ArrayRealSolutionType::ArrayRealSolutionType(Problem * problem)
    : SolutionType(problem) { }


/**
 * Creates the variables of the solution
 */
Variable ** ArrayRealSolutionType::createVariables()
{
    int i;

    Variable **variables = snew Variable*[1]; //malloc(sizeof(Real) * problem->getNumberOfVariables());
    if (problem_->getSolutionType() ==  nullptr)
    {
        std::cout << "Error grave: Impossible to reserve memory for variable type" << std::endl;
        exit(-1);
    }

    variables[0] = snew ArrayReal(problem_->getNumberOfVariables(),problem_);

    return variables;
} // createVariables


/**
 * Copy the variables
 * @param decisionVariables
 * @return An array of variables
 */
Variable ** ArrayRealSolutionType::copyVariables(Variable ** vars)
{
    Variable **variables = snew Variable*[1];
    variables[0] = vars[0]->deepCopy();
    return variables ;
} // copyVariables
