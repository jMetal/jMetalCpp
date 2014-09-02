//  Schaffer.cpp
//
//  Authors:
//       Antonio J. Nebro <antonio@lcc.uma.es>
//       Juan J. Durillo <durillo@lcc.uma.es>
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

#include <Schaffer.h>

/**
 * Constructor.
 * Creates a new instance of the Schaffer problem.
 * @param solutionType The solution type must "Real", "BinaryReal, and "ArrayReal".
 */
Schaffer::Schaffer(string solutionType) {
	numberOfVariables_   = 1;
	numberOfObjectives_  = 2;
	numberOfConstraints_ = 0;

	lowerLimit_ = new double[numberOfVariables_];
	if (lowerLimit_ == NULL) {
		cout << "Schaffer::Schaffer. Error reserving memory for storing the array of lower limits" << endl;
		exit(-1) ;
	}

	upperLimit_ = new double[numberOfVariables_];
	if (upperLimit_ == NULL) {
		cout << "Schaffer::Schaffer. Error reserving memory for storing the array of upper limits" << endl;
		exit(-1) ;
	}

	int i ;
    for (i = 0; i < numberOfVariables_; i++) {
    	lowerLimit_[i] = -10000.0;
    	upperLimit_[i] =  10000.0;
    }

    // TO-DO: Solution type initialization
    solutionType_ = new RealSolutionType(this);
} // Schaffer


/**
 * Destructor
 */
Schaffer::~Schaffer() {
  delete [] lowerLimit_ ;
  delete [] upperLimit_ ;
  delete solutionType_ ;
} // ~Schaffer


/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void Schaffer::evaluate(Solution *solution) {

	double *fx;
	Variable **variables = solution->getDecisionVariables();

	fx = new double[numberOfObjectives_];
	if (fx == NULL) {
		cout << "Schaffer::evaluate: Error reserving memory while evaluating the problem" << endl;
        exit(-1);
	}

	fx[0] = variables[0]->getValue() *  variables[0]->getValue() ;
	fx[1] = (variables[0]->getValue() - 2.0) * (variables[0]->getValue() - 2.0);

	solution->setObjective(0,fx[0]);
	solution->setObjective(1,fx[1]);

	delete [] fx;

} // evaluate


