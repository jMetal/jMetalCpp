/**
 * @file RealSolutionType.cpp
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 30 November 2011
 */


#include <RealSolutionType.h>
#include <cstddef>


/**
 * Constructor
 * @param problem
 */
RealSolutionType::RealSolutionType(Problem *problem)
: SolutionType(problem) { }


/**
 * Creates the variables of the solution
 * @param decisionVariables
 */
Variable **RealSolutionType::createVariables() {
  int i;

  Variable **variables = new Variable*[problem_->getNumberOfVariables()]; //malloc(sizeof(Real) * problem->getNumberOfVariables());
  if (variables ==  NULL) {
    cout << "Error grave: Impossible to reserve memory for variable type" << endl;
    exit(-1);
  }

  for (i = 0; i < problem_->getNumberOfVariables(); i++) {
    variables[i] = new Real(problem_->getLowerLimit(i),problem_->getUpperLimit(i));
  }

  return variables;
} // createVariables
