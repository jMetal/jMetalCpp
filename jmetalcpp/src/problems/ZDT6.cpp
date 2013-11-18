//  ZDT6.cpp
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

#include <ZDT6.h>

const double ZDT6::PI = 3.141592653589793;

ZDT6::ZDT6(string solutionType, int numberOfVariables) {
	numberOfVariables_   = numberOfVariables;
	numberOfObjectives_  = 2;
	numberOfConstraints_ = 0;
	problemName_ 				 = "ZDT6";

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
		//cout << "Tipo seleccionado Real" << endl;
	}
	else if (solutionType.compare("ArrayReal") == 0)
		solutionType_ = new ArrayRealSolutionType(this) ;
	else {
		cout << "Error: solution type " << solutionType << " invalid" << endl;
		exit(-1) ;
	}
	fx_ = new double[numberOfObjectives_] ;
}


ZDT6::~ZDT6() {
  delete [] lowerLimit_ ;
  delete [] upperLimit_ ;
  delete solutionType_ ;
	delete [] fx_ ;
}

/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void ZDT6::evaluate(Solution *solution) {
	XReal * x = new XReal(solution);

	double x1 = x->getValue(0) ;
	fx_[0] = 1.0 - exp(-4.0*x1) * pow(sin(6.0*PI*x1), 6.0) ;
  double g = evalG(x) ;
  double h = evalH(fx_[0], g) ;
	fx_[1] = h * g ;

	solution->setObjective(0,fx_[0]);
	solution->setObjective(1,fx_[1]);

	delete x ;
} // evaluate

double ZDT6::evalG(XReal * x) {
	double g = 0.0 ;
	for (int i = 1; i < x->getNumberOfDecisionVariables(); i++)
		g += x->getValue(i) ;

	g = g / (numberOfVariables_ - 1) ;
	g = pow(g, 0.25) ;
  g = 0.9 * g ;
  g = g + 1.0 ;
	return g;
}

double ZDT6::evalH(double f, double g) {
	return 1.0 - pow((f/g), 2.0) ;
}
