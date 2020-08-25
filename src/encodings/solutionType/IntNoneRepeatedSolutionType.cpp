/*
 * InsertionMutation.h
 *
 *  Created on: 9 Feb 2019
 *      Author: Emad Alharbi
 *      University of York,UK
 */


#include <IntNoneRepeatedSolutionType.h>
#include <cstddef>
#include <algorithm>

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

  double LowerBound=problem_->getLowerLimit(1);// Assuming all Variables have same lower and upper bound. If not then can not use this Solution type
  double UpperBound=problem_->getUpperLimit(1);

  int* values = new int[problem_->getNumberOfVariables()];
  int Index=0;

  for (i = LowerBound; i <= UpperBound; i++) {

	  values[Index]=i;
	  Index++;
  }
  random_shuffle(&values[0], &values[problem_->getNumberOfVariables()]);
  for (i = 0; i < problem_->getNumberOfVariables(); i++){
	  Variable * val=new Int(problem_->getLowerLimit(i),problem_->getUpperLimit(i));
	  val->setValue(values[i]);
	  variables[i] = val;
  }


  /*
  for (i = 0; i < problem_->getNumberOfVariables(); i++) {

	  Variable * val=new Int(problem_->getLowerLimit(i),problem_->getUpperLimit(i));
	  bool Repeated=true;
	  while(Repeated==true){
		  Repeated=false;
		  for(int v = 0 ;v < i ; ++v ){
			  if(variables[v]->getValue() ==val->getValue()){
				  Repeated=true;
				  std::cout << " val "<< val->getValue() << std::endl;
				  break;
		  }
		  }
if(Repeated==true)
	val=new Int(problem_->getLowerLimit(i),problem_->getUpperLimit(i));


		  }
	  std::cout << " set val  "<< val->getValue() << std::endl;
    variables[i] = val;
  }
*/
  delete[] values;
  return variables;
} // createVariables
