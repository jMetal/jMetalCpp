//  ZDT5.cpp
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

#include "ZDT5.h"

ZDT5::ZDT5(string solutionType, int numberOfVariables) {
	cout << "Solutiontype: " << solutionType << endl ;
	numberOfVariables_   = numberOfVariables;
	numberOfObjectives_  = 2;
	numberOfConstraints_ = 0;
	problemName_ 				 = "ZDT5";

	cout << "Problem: " << problemName_ << endl ;

  length_ = new int[numberOfVariables_];
  length_[0] = 30;
  for (int var = 1; var < numberOfVariables_; var++) {
    length_[var] = 5;
  }

	if (solutionType.compare("Binary") == 0)
		solutionType_ = new BinarySolutionType(this) ;
	else {
		cout << "Error: solution type " << solutionType << " invalid" << endl;
		exit(-1) ;
	}
	fx_ = new double[numberOfObjectives_] ;
} // ZDT5::ZDT5

ZDT5::~ZDT5() {
  delete [] length_ ;
  delete [] fx_ ;
}

/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void ZDT5::evaluate(Solution *solution) {
  Binary * variable ;
  int    counter  ;

  variable = (Binary *)(solution->getDecisionVariables()[0]) ;

  fx_[0]        = 1 + variable->cardinality();

  double g    = evalG(solution)  ;
  double h    = evalH(fx_[0],g)  ;
  fx_[1]        = h * g          ;

  solution->setObjective(0,fx_[0]);
  solution->setObjective(1,fx_[1]);


} // evaluate

double ZDT5::evalG(Solution * solution) {
  double res = 0.0;
  Binary * variable ;

  for (int i = 1; i < numberOfVariables_; i++) {
  	variable = (Binary *)(solution->getDecisionVariables()[i]) ;
    res += evalV(variable->cardinality());
  }

  return res;
}

double ZDT5::evalH(double f, double g) {
  return 1 / f;
}

double ZDT5::evalV(double value) {
  if (value < 5.0) {
    return 2.0 + value;
  } else {
    return 1.0;
  }
}
