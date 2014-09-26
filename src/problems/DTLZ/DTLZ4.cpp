//  DTLZ4.cpp
//
//  Author:
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

#include <DTLZ4.h>

const double DTLZ4::PI = 3.141592653589793;

DTLZ4::DTLZ4(string solutionType, int numberOfVariables, int numberOfObjectives) {
	numberOfVariables_   = numberOfVariables;
	numberOfObjectives_  = numberOfObjectives;
	numberOfConstraints_ = 0;
	problemName_ 				 = "DTLZ4";

	lowerLimit_ = new double[numberOfVariables_];//(double *)malloc(sizeof(double)*numberOfVariables);
	if (lowerLimit_ == NULL) {
		cout << "Impossible to reserve memory for storing the variable lower limits" << endl;
		exit(-1);
	}

	upperLimit_ = new double[numberOfVariables_];//(double *)malloc(sizeof(double)*numberOfVariables);
	if (upperLimit_ == NULL) {
		cout << "Impossible to reserve memory for storing the variable lower limits" << endl;
		exit(-1);
	}

	for (int i = 0; i < numberOfVariables_; i++) {
		lowerLimit_[i] = 0.0;
		upperLimit_[i] = 1.0;
	}

	if (solutionType.compare("BinaryReal") == 0)
		solutionType_ = new BinaryRealSolutionType(this) ;
	else if (solutionType.compare("Real") == 0) {
		solutionType_ = new RealSolutionType(this) ;
		// cout << "Tipo seleccionado Real" << endl;
	}
	else if (solutionType.compare("ArrayReal") == 0)
		solutionType_ = new ArrayRealSolutionType(this) ;
	else {
		cout << "Error: solution type " << solutionType << " invalid" << endl;
		exit(-1) ;
	}

	fx_ = new double[numberOfObjectives_] ;
  x_ = new double[numberOfVariables_];
}

DTLZ4::~DTLZ4() {
  delete [] lowerLimit_ ;
  delete [] upperLimit_ ;
  delete solutionType_ ;
}

/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void DTLZ4::evaluate(Solution *solution) {
	XReal * vars = new XReal(solution);

  int k = numberOfVariables_ - numberOfObjectives_ + 1;
  double alpha = 100.0;

  for (int i = 0; i < numberOfVariables_; i++)
    x_[i] = vars->getValue(i);

  double g = 0.0;
  for (int i = numberOfVariables_ - k; i < numberOfVariables_; i++)
    g += (x_[i] - 0.5)*(x_[i] - 0.5);

  for (int i = 0; i < numberOfObjectives_; i++)
    fx_[i] = 1.0 + g;

  for (int i = 0; i < numberOfObjectives_; i++) {
    for (int j = 0; j < numberOfObjectives_ - (i + 1); j++)
      fx_[i] *= cos(pow(x_[j],alpha)*(PI/2.0));
      if (i != 0){
        int aux = numberOfObjectives_ - (i + 1);
        fx_[i] *= sin(pow(x_[aux],alpha)*(PI/2.0));
      } //if
  } // for

  for (int i = 0; i < numberOfObjectives_; i++)
    solution->setObjective(i, fx_[i]);

	delete vars ;
} // evaluate
