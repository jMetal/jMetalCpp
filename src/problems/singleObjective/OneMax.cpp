//  OneMax.cpp
//
//  Authors:
//       Antonio J. Nebro <antonio@lcc.uma.es>
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

#include <OneMax.h>

/**
 * Class constructor
 */
OneMax::OneMax(int numberOfBits, int numberOfStrings) {
	numberOfVariables_   = numberOfStrings;
	numberOfObjectives_  = 1;
	numberOfConstraints_ = 0;
	problemName_ 				 = "OneMax";

  solutionType_ = new BinarySolutionType(this) ;
  length_       = new int[numberOfVariables_];
  for (int i = 0; i < numberOfVariables_; i++)
    length_  [i] = numberOfBits ;
} // OneMax

OneMax::~OneMax() {
  delete []length_ ;
  delete solutionType_;
} // ~OneMax

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
} // evaluate
