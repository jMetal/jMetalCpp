/*
 * ZDT6.cpp
 *
 *  Created on: 10/12/2011
 *      Author: antonio
 */

#include <ZDT6.h>

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
		cout << "Tipo seleccionado Real" << endl;
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
	fx_[0] = 1.0 - exp(-4.0*x1) * pow(sin(6.0*M_PI*x1), 6.0) ;
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
