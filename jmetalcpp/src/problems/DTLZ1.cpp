/*
 * ZDT1.cpp
 *
 *  Created on: 09/12/2011
 *      Author: antonio
 */

#include <DTLZ1.h>

DTLZ1::DTLZ1(string solutionType, int numberOfVariables, int numberOfObjectives) {
	numberOfVariables_   = numberOfVariables;
	numberOfObjectives_  = numberOfObjectives;
	numberOfConstraints_ = 0;
	problemName_ 				 = "DTLZ1";

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

DTLZ1::~DTLZ1() {
  delete [] lowerLimit_ ;
  delete [] upperLimit_ ;
  delete solutionType_ ;
}

/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void DTLZ1::evaluate(Solution *solution) {
	XReal * vars = new XReal(solution);

	double * fx = new double[numberOfObjectives_] ;
  double * x = new double[numberOfVariables_];
  int k = numberOfVariables_ - numberOfObjectives_ + 1;

  for (int i = 0; i < numberOfVariables_; i++)
    x[i] = vars->getValue(i);

  double g = 0.0 ;

  for (int i = numberOfVariables_ - k; i < numberOfVariables_; i++)
    g += (x[i] - 0.5)*(x[i] - 0.5) - cos(20.0 * M_PI * (x[i] - 0.5));

  g = 100 * (k + g);
  for (int i = 0; i < numberOfObjectives_; i++)
    fx[i] = (1.0 + g) * 0.5;

  for (int i = 0; i < numberOfObjectives_; i++){
    for (int j = 0; j < numberOfObjectives_ - (i + 1); j++)
      fx[i] *= x[j];
      if (i != 0){
        int aux = numberOfObjectives_ - (i + 1);
        fx[i] *= 1 - x[aux];
      } //if
  }//for

  for (int i = 0; i < numberOfObjectives_; i++)
    solution->setObjective(i, fx[i]);

	delete [] fx ;
	delete [] x ;
	delete vars ;
} // evaluate
