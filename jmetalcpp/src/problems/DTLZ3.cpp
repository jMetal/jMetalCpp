/*
 * DTLZ3.cpp
 *
 *  Created on: 09/12/2011
 *      Author: antonio
 */

#include <DTLZ3.h>

DTLZ3::DTLZ3(string solutionType, int numberOfVariables, int numberOfObjectives) {
	numberOfVariables_   = numberOfVariables;
	numberOfObjectives_  = numberOfObjectives;
	numberOfConstraints_ = 0;
	problemName_ 				 = "DTLZ3";

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
  x_ = new double[numberOfVariables_];
}

DTLZ3::~DTLZ3() {
  delete [] lowerLimit_ ;
  delete [] upperLimit_ ;
  delete solutionType_ ;
}

/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void DTLZ3::evaluate(Solution *solution) {
	XReal * vars = new XReal(solution);

  int k = numberOfVariables_ - numberOfObjectives_ + 1;

  for (int i = 0; i < numberOfVariables_; i++)
    x_[i] = vars->getValue(i);

  double g = 0.0;
  for (int i = numberOfVariables_ - k; i < numberOfVariables_; i++)
    g += (x_[i] - 0.5)*(x_[i] - 0.5) - cos(20.0 * M_PI * (x_[i] - 0.5));

  g = 100.0 * (k + g);
  for (int i = 0; i < numberOfObjectives_; i++)
    fx_[i] = 1.0 + g;

  for (int i = 0; i < numberOfObjectives_; i++){
    for (int j = 0; j < numberOfObjectives_ - (i + 1); j++)
      fx_[i] *= cos(x_[j]*0.5*M_PI);
      if (i != 0){
        int aux = numberOfObjectives_ - (i + 1);
        fx_[i] *= sin(x_[aux]*0.5*M_PI);
      } // if
  } //for

	delete vars ;
} // evaluate
