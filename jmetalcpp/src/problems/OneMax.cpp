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
   int    counter  ;

   variable = (Binary *)(solution->getDecisionVariables()[0]) ;
   counter = 0 ;

   for (int i = 0; i < variable->getNumberOfBits() ; i++)
     if (variable->getIth(i) == true)
       counter ++ ;
    // OneMax is a maximization problem: multiply by -1 to minimize
    solution->setObjective(0, - 1.0*counter);
}
