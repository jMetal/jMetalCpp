/*
 * DTLZ4.cpp
 *
 *  Created on: 09/12/2011
 *      Author: antonio
 */

#include <DTLZ4.h>

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
		cout << "Tipo seleccionado Real" << endl;
	}
	else if (solutionType.compare("ArrayReal") == 0)
		solutionType_ = new ArrayRealSolutionType(this) ;
	else {
		cout << "Error: solution type " << solutionType << " invalid" << endl;
		exit(-1) ;
	}
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

	double * fx = new double[numberOfObjectives_] ;
  double * x = new double[numberOfVariables_];
  int k = numberOfVariables_ - numberOfObjectives_ + 1;
  double alpha = 100.0;

  for (int i = 0; i < numberOfVariables_; i++)
    x[i] = vars->getValue(i);

  double g = 0.0;
  for (int i = numberOfVariables_ - k; i < numberOfVariables_; i++)
    g += (x[i] - 0.5)*(x[i] - 0.5);

  for (int i = 0; i < numberOfObjectives_; i++)
    fx[i] = 1.0 + g;

  for (int i = 0; i < numberOfObjectives_; i++) {
    for (int j = 0; j < numberOfObjectives_ - (i + 1); j++)
      fx[i] *= cos(pow(x[j],alpha)*(M_PI/2.0));
      if (i != 0){
        int aux = numberOfObjectives_ - (i + 1);
        fx[i] *= sin(pow(x[aux],alpha)*(M_PI/2.0));
      } //if
  } // for

  for (int i = 0; i < numberOfObjectives_; i++)
    solution->setObjective(i, fx[i]);

	delete [] fx ;
	delete [] x ;
	delete vars ;
} // evaluate
