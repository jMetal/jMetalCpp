//  Griewank.cpp
//
//  Authors:
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


#include <Griewank.h>


/**
 * Constructor.
 * Creates a new instance of the Griewank problem.
 * @param solutionType The solution type must "Real", "BinaryReal, and "ArrayReal".
 * @param numberOfVariables Number of variables of the problem
 */
Griewank::Griewank(string solutionType, int numberOfVariables) {
	numberOfVariables_   = numberOfVariables;
	numberOfObjectives_  = 1;
	numberOfConstraints_ = 0;
	problemName_ 				 = "Griewank";

	lowerLimit_ = new double[numberOfVariables_];
	if (lowerLimit_ == NULL) {
		cout << "Griewank::Griewank. Error reserving memory for storing the array of lower limits" << endl;
		exit(-1) ;
	}	// if
	
	upperLimit_ = new double[numberOfVariables_];
	if (upperLimit_ == NULL) {
		cout << "Griewank::Griewank. Error reserving memory for storing the array of upper limits" << endl;
		exit(-1) ;
	} // if
	
  for (int i = 0; i < numberOfVariables_; i++) {
    lowerLimit_[i] = -600.0;
    upperLimit_[i] =  600.0;
  } // for

  if (solutionType.compare("BinaryReal") == 0)
    solutionType_ = new BinaryRealSolutionType(this) ;
  else if (solutionType.compare("Real") == 0)
    solutionType_ = new RealSolutionType(this) ;
  else {
    cout << "Error: solution type " << solutionType << " invalid" << endl;
    exit(-1) ;
  } // if
} // Griewank


/**
 * Destructor
 */
Griewank::~Griewank() {
  delete [] lowerLimit_ ;
  delete [] upperLimit_ ;
  delete solutionType_ ;
} // ~Griewank


/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void Griewank::evaluate(Solution *solution) {
	Variable **decisionVariables = solution->getDecisionVariables();
	
  double sum  = 0.0    ;
  double mult = 1.0    ;
  double d    = 4000.0 ;

  for (int var = 0; var < numberOfVariables_; var++) {
    sum += decisionVariables[var]->getValue() *
           decisionVariables[var]->getValue() ;
    mult *= cos(decisionVariables[var]->getValue()/sqrt(var+1)) ;
  }        

  solution->setObjective(0, 1.0/d * sum - mult + 1.0) ;

} // evaluate
