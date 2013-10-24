//  Srinivas.cpp
//
//  Authors:
//       Esteban López-Camacho <esteban@lcc.uma.es>
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

#include <Srinivas.h>

/**
 * Constructor.
 * Creates a new instance of the Srinivas problem.
 * @param solutionType The solution type must "Real" or "BinaryReal
 */
Srinivas::Srinivas(string solutionType) {
	numberOfVariables_   = 2;
	numberOfObjectives_  = 2;
	numberOfConstraints_ = 2;
	problemName_ 				 = "Srinivas";

	lowerLimit_ = new double[numberOfVariables_];
	if (lowerLimit_ == NULL) {
		cout << "Srinivas::Srinivas. Error reserving memory for storing the array of lower limits" << endl;
		exit(-1) ;
	}	
	
	upperLimit_ = new double[numberOfVariables_];
	if (upperLimit_ == NULL) {
		cout << "Srinivas::Srinivas. Error reserving memory for storing the array of upper limits" << endl;
		exit(-1) ;
	}
	
  for (int var = 0; var < numberOfVariables_; var++){
    lowerLimit_[var] = -20.0;
    upperLimit_[var] =  20.0;
  } // for
  
  if (solutionType.compare("BinaryReal")==0) {
    solutionType_ = new BinaryRealSolutionType(this);
  } else if (solutionType.compare("Real")==0) {
    solutionType_ = new RealSolutionType(this);
  } else {
    cout << "Error: solution type " << solutionType << " invalid" << endl;
    exit(-1);
  }
} // Srinivas


/**
 * Destructor
 */
Srinivas::~Srinivas() {
  delete [] lowerLimit_ ;
  delete [] upperLimit_ ;
  delete solutionType_ ;
} // ~Srinivas


/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void Srinivas::evaluate(Solution *solution) {
  
  Variable **variables = solution->getDecisionVariables();
  
  double * fx = new double[numberOfObjectives_];
	if (fx == NULL) {
		cout << "Srinivas::evaluate: Error reserving memory while evaluating the problem" << endl;
        exit(-1);
	}
	
  double * x = new double[numberOfVariables_];
  if (x == NULL) {
    cout << "Srinivas::evaluate: Error reserving memory for the variable values array" << endl;
    exit(-1);
  } // if
  
  double x1 = variables[0]->getValue();
  double x2 = variables[1]->getValue();
  
  fx[0] = 2.0 + (x1-2.0)*(x1-2.0) + (x2-1.0)*(x2-1.0);                        
  fx[1] = 9.0 * x1 - (x2-1.0)*(x2-1.0);   
  
  solution->setObjective(0,fx[0]);
  solution->setObjective(1,fx[1]);

  delete[]fx;
  delete[]x;
  
} // evaluate

/**
 * Evaluates the constraint overhead of a solution
 * @param solution The solution
 */
void Srinivas::evaluateConstraints(Solution *solution) {
  
  double * constraint = new double[this->getNumberOfConstraints()];
  
  double x1 = solution->getDecisionVariables()[0]->getValue();
  double x2 = solution->getDecisionVariables()[1]->getValue();
  
  constraint[0] = 1.0 - (x1*x1 + x2*x2)/225.0;
  constraint[1] = (3.0*x2 - x1)/10.0 - 1.0;
  
  int number = 0;
  double total = 0.0;
  for (int i = 0; i < this->getNumberOfConstraints(); i++) {
    if (constraint[i]<0.0){
      number++;
      total+=constraint[i];
    }
  }
  
  solution->setOverallConstraintViolation(total);    
  solution->setNumberOfViolatedConstraints(number);
  
} // evaluateConstraints

