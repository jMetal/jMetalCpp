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
  problemName_         = "Kursawe";

  lowerLimit_ = new double[numberOfVariables_];
  if (lowerLimit_ == NULL) {
    cout << "Impossible to reserve memory for storing the variable lower limits" << endl;
    exit(-1);
  }

  upperLimit_ = new double[numberOfVariables_];
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

  XReal * vars = new XReal(solution);

  double aux, xi, xj;                          // auxiliary variables
  double * fx = new double[2];                 // function values
  if (fx == NULL) {
    cout << "Error grave: Impossible to reserve memory while evaluating the problem" << endl;
    exit(-1);
  }

  double * x = new double[numberOfVariables_];
  for (int i = 0 ; i < numberOfVariables_; i++) {
    x[i] = vars->getValue(i) ;
  }

  fx[0] = 0.0 ;
  for (int var = 0; var < numberOfVariables_ - 1; var++) {
    xi = x[var] *  x[var];
    xj = x[var+1] * x[var+1] ;
    aux = (-0.2) * sqrt(xi + xj);
    fx[0] += (-10.0) * exp(aux);
  } // for

  fx[1] = 0.0;

  for (int var = 0; var < numberOfVariables_ ; var++) {
    fx[1] += pow(fabs(x[var]), 0.8) +
        5.0 * sin(pow(x[var], 3.0));
  } // for

  solution->setObjective(0,fx[0]);
  solution->setObjective(1,fx[1]);

  delete [] fx;
  delete [] x;
  delete vars;

} // evaluate

