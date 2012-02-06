/**
 * @file BinarySolutionType.cpp
 * @author Esteban López
 * @version 1.0
 * @date 30 November 2011
 */


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
