/**
 * @file SolutionType.cpp
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 23 November 2011
**/

#include <SolutionType.h>


/**
 * Constructor
 * @param problem The problem to solve
**/
SolutionType::SolutionType(Problem *problem) {
	problem_ = problem;
}


/**
 * Copies the decision variables
 * @param decisionVariables
 * @return An array of variables
**/
Variable ** SolutionType::copyVariables(Variable **vars) {
	int numberOfVar = problem_->getNumberOfVariables();
	int var;
	//Variable *variables =(Variable *)malloc(sizeof(*vars));
	Variable ** variables = new Variable*[numberOfVar];

	if (variables == NULL)	{
		cout << "Error grave: Impossible to reserve memory for allocating a copy of variables" << endl;
		exit(-1);
	}
	
	for (var = 0; var < numberOfVar; var++) {
		variables[var] = vars[var]->deepCopy();
	}
	
	return variables;
} // copyVariables
