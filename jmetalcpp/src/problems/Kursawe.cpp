/**
 * @file Kursawe.cpp
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 02 December 2011
 */


#include <Kursawe.h>


/**
 * @class Kursawe
 * @brief Class representing the problem Kursawe
 **/


/**
 * Constructor.
 * Creates a new instance of the Kursawe problem.
 * @param numberOfVariables Number of variables of the problem
 * @param solutionType The solution type must "Real", "BinaryReal, and "ArrayReal".
 */
Kursawe::Kursawe(string solutionType, int numberOfVariables) {
	numberOfVariables_   = numberOfVariables;
	numberOfObjectives_  = 2;
	numberOfConstraints_ = 0;
	problemName_ 				 = "Kursawe";

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
		lowerLimit_[i] = -5.0;
		upperLimit_[i] =  5.0;
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
} // Kursawe


/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void Kursawe::evaluate(Solution *solution) {

	//	cout << "Kursawe::evaluate begin..." << endl;
	XReal * vars = new XReal(solution);

	double aux, xi, xj;													 // auxiliary variables
	double * fx = new double[2];								 // function values
	//  fx = new double[numberOfObjectives_]; //(double *)malloc(sizeof(double) * numberOfObjectives_);
	//	if (fx == NULL) {
	//		cout << "Error grave: Impossible to reserve memory while evaluating the problem" << endl;
	//		exit(-1);
	//	}
	//  cout << "Number of variables: " << numberOfVariables_ << endl;
	double * x = new double[numberOfVariables_];
	for (int i = 0 ; i < numberOfVariables_; i++) {
		x[i] = vars->getValue(i) ;
		//  	cout << "  x[" << i << "] = " << x[i] << endl;
	}


	//double *fx;
	//double aux, xi, xj;
	//	int var;
	//	Variable **variables = solution->getDecisionVariables();

	fx[0] = 0.0 ;
	for (int var = 0; var < numberOfVariables_ - 1; var++) {
		xi = x[var] *  x[var];
		xj = x[var+1] * x[var+1] ;
		aux = (-0.2) * sqrt(xi + xj);
		fx[0] += (-10.0) * exp(aux);
	} // for

	fx[1] = 0.0;

	//	cout << "Valor inicial de fx[1] = " << fx[1] << endl;

	for (int var = 0; var < numberOfVariables_ ; var++) {

		//		cout << "Valor de x[" << var << "] = " << x[var] << endl;
		//		cout << "Valor de abs(x[" << var << "]) = " << fabs(x[var]) << endl;
		//		cout << "Valor de abs(x[" << var << "])^0.8 = " << pow(fabs(x[var]), 0.8) << endl;
		//		cout << "Valor de (x[" << var << "])^3 = " << pow(x[var], 3.0) << endl;
		//		cout << "Valor de sen((x[" << var << "])^3) = " << sin(pow(x[var], 3.0)) << endl;

		fx[1] += pow(fabs(x[var]), 0.8) +
				5.0 * sin(pow(x[var], 3.0));

		//		cout << "Valor acumulado de fx[1] = " << fx[1] << endl;

	} // for

	//cout << fx[0] << " " << fx[1] << endl;

	solution->setObjective(0,fx[0]);
	solution->setObjective(1,fx[1]);

	delete [] fx;
	delete [] x;
	delete vars;

	//	cout << "Kursawe::evaluate end..." << endl;

} // evaluate

