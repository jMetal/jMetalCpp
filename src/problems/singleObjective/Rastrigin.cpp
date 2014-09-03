//  Rastrigin.cpp
//
//  Authors:
//       Antonio J. Nebro <antonio@lcc.uma.es>
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

#include <Rastrigin.h>

const double Rastrigin::PI = 3.141592653589793;

/**
 * Constructor.
 * Creates a new instance of the Rastrigin problem.
 * @param solutionType The solution type must "Real", "BinaryReal, and "ArrayReal".
 * @param numberOfVariables Number of variables of the problem
 */
Rastrigin::Rastrigin(string solutionType, int numberOfVariables) {
	numberOfVariables_   = numberOfVariables;
	numberOfObjectives_  = 1;
	numberOfConstraints_ = 0;
	problemName_ 				 = "Rastrigin";

	lowerLimit_ = new double[numberOfVariables_];
	if (lowerLimit_ == NULL) {
		cout << "Rastrigin::Rastrigin. Error reserving memory for storing the array of lower limits" << endl;
		exit(-1) ;
	}	
	
	upperLimit_ = new double[numberOfVariables_];
	if (upperLimit_ == NULL) {
		cout << "Rastrigin::Rastrigin. Error reserving memory for storing the array of upper limits" << endl;
		exit(-1) ;
	}
	
  for (int i = 0; i < numberOfVariables_; i++) {
    lowerLimit_[i] = -5.12;
    upperLimit_[i] =  5.12;
  }

  // TODO: Solution type initialization
  solutionType_ = new RealSolutionType(this);	
} // Rastrigin


/**
 * Destructor
 */
Rastrigin::~Rastrigin() {
  delete [] lowerLimit_ ;
  delete [] upperLimit_ ;
  delete solutionType_ ;
} // ~Rastrigin


/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void Rastrigin::evaluate(Solution *solution) {
	//double fx [numberOfObjectives_] ;
  //double x [numberOfVariables_];
	Variable **variables = solution->getDecisionVariables();

	double * fx = new double[numberOfObjectives_]; //(double *)malloc(sizeof(double) * numberOfObjectives_);
	if (fx == NULL) {
		cout << "Rastrigin::evaluate: Error reserving memory while evaluating the problem" << endl;
        exit(-1);
	}
	
  double * x = new double[numberOfVariables_];
  if (x == NULL) {
    cout << "Rastrigin::evaluate: Error reserving memory for the variable values array" << endl;
    exit(-1);
  } // if

  for (int i = 0; i < numberOfVariables_; i++)
    x[i] = variables[i]->getValue() ;

  // First function
  double result = 0.0 ;
  double a = 10.0 ;
  double w = 2*PI ;
  
  for (int i = 0; i < numberOfVariables_; i++) {
    result += x[i]*x[i] - a*cos(w*x[i]) ;
  }
  
	fx[0] = a*numberOfVariables_ + result ;
		
	solution->setObjective(0,fx[0]);
  delete[]fx ;
  delete[]x;
} // evaluate

