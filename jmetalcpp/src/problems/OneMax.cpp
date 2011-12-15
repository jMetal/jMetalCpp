/*
 * OneMax.cpp
 *
 *  Created on: 12/12/2011
 *      Author: antonio
 */

#include <OneMax.h>

OneMax::OneMax(int numberOfBits, int numberOfStrings) {
	numberOfVariables_   = numberOfStrings;
	numberOfObjectives_  = 1;
	numberOfConstraints_ = 0;
	problemName_ 				 = "OneMax";

  solutionType_ = new BinarySolutionType(this) ;
  length_       = new int[numberOfVariables_];
  for (int i = 0; i < numberOfVariables_; i++)
    length_  [i] = numberOfBits ;
}

OneMax::~OneMax() {
  delete []length_ ;
}

 /**
  * Evaluates a solution
  * @param solution The solution to evaluate
  */
void OneMax::evaluate(Solution * solution) {
   Binary * variable ;
   int    counter  ;

   counter = 0 ;
   for (int i = 0; i < numberOfVariables_ ; i++) {
     variable = (Binary *)(solution->getDecisionVariables()[i]) ;
  	 counter += variable->cardinality() ;
   }
   /*
   variable = (Binary *)(solution->getDecisionVariables()[0]) ;
   counter = 0 ;

   for (int i = 0; i < variable->getNumberOfBits() ; i++)
     if (variable->getIth(i) == true)
       counter ++ ;
  */
    // OneMax is a maximization problem: multiply by -1 to minimize
    solution->setObjective(0, - 1.0*counter);
}
