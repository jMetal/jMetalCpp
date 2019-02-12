// IntSolutionType.cpp
//
//  Author:
//       Juan J. Durillo <durillo@lcc.uma.es>
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
