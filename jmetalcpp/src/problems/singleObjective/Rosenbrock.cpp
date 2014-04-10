//  Rosenbrock.cpp
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

#include <Rosenbrock.h>

/**
 * Constructor.
 * Creates a new instance of the Rosenbrock problem.
 * @param solutionType The solution type must "Real", "BinaryReal, and "ArrayReal".
 * @param numberOfVariables Number of variables of the problem
 */
Rosenbrock::Rosenbrock(string solutionType, int numberOfVariables) {
	numberOfVariables_   = numberOfVariables;
	numberOfObjectives_  = 1;
	numberOfConstraints_ = 0;
	problemName_ 				 = "Rosenbrock";

	lowerLimit_ = new double[numberOfVariables_];
	if (lowerLimit_ == NULL) {
		cout << "Rosenbrock::Rosenbrock. Error reserving memory for storing the array of lower limits" << endl;
		exit(-1) ;
	}	
	
	upperLimit_ = new double[numberOfVariables_];
	if (upperLimit_ == NULL) {
		cout << "Rosenbrock::Rosenbrock. Error reserving memory for storing the array of upper limits" << endl;
		exit(-1) ;
	}
	
	int i ;
    for (i = 0; i < numberOfVariables_; i++) {
    	lowerLimit_[i] = -5.12;
    	upperLimit_[i] =  5.12;
    }

    // TODO: Solution type initialization
    solutionType_ = new RealSolutionType(this);	
} // Rosenbrock


/**
 * Destructor
 */
Rosenbrock::~Rosenbrock() {
  delete [] lowerLimit_ ;
  delete [] upperLimit_ ;
  delete solutionType_ ;
} // ~Rosenbrock


/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void Rosenbrock::evaluate(Solution *solution) {
	//double fx [numberOfObjectives_] ;
  //double x [numberOfVariables_];
	Variable **variables = solution->getDecisionVariables();

	double * fx = new double[numberOfObjectives_]; //(double *)malloc(sizeof(double) * numberOfObjectives_);
	if (fx == NULL) {
		cout << "Rosenbrock::evaluate: Error reserving memory while evaluating the problem" << endl;
        exit(-1);
	}
	
  double * x = new double[numberOfVariables_];
  if (x == NULL) {
    cout << "Rosenbrock::evaluate: Error reserving memory for the variable values array" << endl;
    exit(-1);
  } // if

  for (int i = 0; i < numberOfVariables_; i++)
    x[i] = variables[i]->getValue() ;

  double sum = 0.0;
  for (int var = 0; var < numberOfVariables_-1; var++) {
    sum += 100.0 * (x[var+1]-x[var]*x[var])*(x[var+1]-x[var]*x[var]) +(x[var]-1)*(x[var]-1) ;
  }
  
	fx[0] = sum ;
		
	solution->setObjective(0,fx[0]);
  delete[]fx ;
  delete[]x;
} // evaluate

