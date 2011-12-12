/*
 * OneMax.cpp
 *
 *  Created on: 12/12/2011
 *      Author: antonio
 */

#include <OneMax.h>

OneMax::OneMax(int numberOfBits) {
	numberOfVariables_   = 1;
	numberOfObjectives_  = 1;
	numberOfConstraints_ = 0;
	problemName_ 				 = "OneMax";

  solutionType_ = new BinarySolutionType(this) ;
  length_       = new int[numberOfVariables_];
  length_      [0] = numberOfBits ;
}

OneMax::~OneMax() {
	// TODO Auto-generated destructor stub
}

 /**
  * Evaluates a solution
  * @param solution The solution to evaluate
  */
void OneMax::evaluate(Solution * solution) {
   Binary * variable ;
}
