/*
 * InsertionMutation.h
 *
 *  Created on: 9 Feb 2019
 *      Author: Emad Alharbi
 *      University of York,UK
 */


#include <IntNoneRepeatedSolutionType.h>
#include <cstddef>


/**
 * Constructor
 * @param problem
 */
IntNoneRepeatedSolutionType::IntNoneRepeatedSolutionType(Problem *problem)
: SolutionType(problem) {


}


/**
 * Creates the variables of the solution
 * @param decisionVariables
 */
Variable **IntNoneRepeatedSolutionType::createVariables() {
  int i;

  Variable **variables = new Variable*[problem_->getNumberOfVariables()]; //malloc(sizeof(Int) * problem->getNumberOfVariables());
  if (variables ==  NULL) {
    cout << "Error grave: Impossible to reserve memory for variable type" << endl;
    exit(-1);
  }

  for (i = 0; i < problem_->getNumberOfVariables(); i++) {

	  Variable * val=new Int(problem_->getLowerLimit(i),problem_->getUpperLimit(i));
	  bool Repeated=true;
	  while(Repeated==true){
		  Repeated=false;
		  for(int v = 0 ;v < i ; ++v ){
			  if(variables[v]->getValue() ==val->getValue()){
				  Repeated=true;
		  }
		  }
if(Repeated==true)
	val=new Int(problem_->getLowerLimit(i),problem_->getUpperLimit(i));
		  }
    variables[i] = val;
  }

  return variables;
} // createVariables
