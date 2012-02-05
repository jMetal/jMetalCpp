/*
 * DTLZ5.cpp
 *
 *  Created on: 04/02/2012
 *      Author: antonio
 */

#include <DTLZ5.h>

DTLZ5::DTLZ5(string solutionType, int numberOfVariables, int numberOfObjectives) {
	numberOfVariables_   = numberOfVariables;
	numberOfObjectives_  = numberOfObjectives;
	numberOfConstraints_ = 0;
	problemName_ 				 = "DTLZ5";

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

DTLZ5::~DTLZ5() {
  delete [] lowerLimit_ ;
  delete [] upperLimit_ ;
  delete solutionType_ ;
}

/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void DTLZ5::evaluate(Solution *solution) {
	XReal * vars = new XReal(solution);
  double g = 0.0;
  double * theta = new double[numberOfObjectives_-1];

  int k = numberOfVariables_ - numberOfObjectives_ + 1;
  double alpha = 100.0;

  for (int i = 0; i < numberOfVariables_; i++)
    x_[i] = vars->getValue(i);

  for (int i = numberOfVariables_ - k; i < numberOfVariables_; i++)
    g += (x_[i] - 0.5)*(x_[i] - 0.5);

  double t = M_PI  / (4.0 * (1.0 + g));

  theta[0] = x_[0] * M_PI / 2.0;
  for (int i = 1; i < (numberOfObjectives_-1); i++)
    theta[i] = t * (1.0 + 2.0 * g * x_[i]);

  for (int i = 0; i < numberOfObjectives_; i++)
    fx_[i] = 1.0 + g;

  for (int i = 0; i < numberOfObjectives_; i++){
    for (int j = 0; j < numberOfObjectives_ - (i + 1); j++)
      fx_[i] *= cos(theta[j]);
      if (i != 0){
        int aux = numberOfObjectives_ - (i + 1);
        fx_[i] *= sin(theta[aux]);
      } // if
  } //for

  for (int i = 0; i < numberOfObjectives_; i++)
    solution->setObjective(i, fx_[i]);

	delete vars ;
	delete [] theta ;
} // evaluate
