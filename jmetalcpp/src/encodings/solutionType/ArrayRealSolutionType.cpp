/**
 * @file ArrayRealSolutionType.cpp
 * @author Esteban López
 * @version 1.0
 * @date 30 November 2011
 */


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
 * @param decisionVariables
 */
Variable ** ArrayRealSolutionType::createVariables() {
	int i;
	
	Variable **variables = new Variable*[1]; //malloc(sizeof(Real) * problem->getNumberOfVariables());
	if (problem_->getSolutionType() ==  NULL) {
		cout << "Error grave: Impossible to reserve memory for variable type" << endl;
		exit(-1);
  }
   
  for (i = 0; i < problem_->getNumberOfVariables(); i++) {
  	variables[0] = new ArrayReal(problem_->getNumberOfVariables(),problem_);
  }
	
  return variables;
} // createVariables


/**
 * Copy the variables
 * @param decisionVariables
 * @return An array of variables
 */
Variable ** ArrayRealSolutionType::copyVariables(Variable ** vars) {
	Variable **variables = new Variable*[1];
	variables[0] = vars[0]->deepCopy();
	return variables ;
} // copyVariables
