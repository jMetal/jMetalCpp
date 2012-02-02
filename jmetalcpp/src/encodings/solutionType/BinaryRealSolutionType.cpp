/**
 * @file BinaryRealSolutionType.cpp
 * @author Esteban López
 * @version 1.0
 * @date 02 December 2011
 */


#include <BinaryRealSolutionType.h>
#include <cstddef>


/**
 * Constructor
 * @param problem
 */
BinaryRealSolutionType::BinaryRealSolutionType(Problem *problem)
: SolutionType(problem) { }


/**
 * Creates the variables of the solution
 * @param decisionVariables
 */
Variable ** BinaryRealSolutionType::createVariables() {
	int i;
	
	Variable **variables = new Variable*[problem_->getNumberOfVariables()]; //malloc(sizeof(Real) * problem->getNumberOfVariables());

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
	} // for
	
  return variables;
} // createVariables

