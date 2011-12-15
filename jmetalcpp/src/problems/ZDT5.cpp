/*
 * ZDT5.cpp
 *
 *  Created on: 15/12/2011
 *      Author: antonio
 */

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
