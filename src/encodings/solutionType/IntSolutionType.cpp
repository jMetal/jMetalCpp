/*
 * InsertionMutation.h
 *
 *  Created on: 9 Feb 2019
 *      Author: Emad Alharbi
 *      University of York,UK
 */

#include <IntSolutionType.h>
#include <cstddef>


/**
 * Constructor
 * @param problem
 */
IntSolutionType::IntSolutionType(Problem *problem)
: SolutionType(problem) {


}


/**
 * Creates the variables of the solution
 * @param decisionVariables
 */
Variable **IntSolutionType::createVariables() {
  int i;

  Variable **variables = new Variable*[problem_->getNumberOfVariables()]; //malloc(sizeof(Int) * problem->getNumberOfVariables());
  if (variables ==  NULL) {
    cout << "Error grave: Impossible to reserve memory for variable type" << endl;
    exit(-1);
  }

  for (i = 0; i < problem_->getNumberOfVariables(); i++) {
    variables[i] = new Int(problem_->getLowerLimit(i),problem_->getUpperLimit(i));
  }

  return variables;
} // createVariables
