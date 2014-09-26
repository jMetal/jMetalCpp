//  CEC2005Problem.cpp
//
//  Authors:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//       Antonio J. Nebro <antonio@lcc.uma.es>
//
//  Copyright (c) 2014 Antonio J. Nebro
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


#include <CEC2005Problem.h>

const double CEC2005Problem::PI = 3.141592653589793;

/**
 * Constructor.
 * Creates a new instance of a CEC2005 problem.
 * @param solutionType The solution type must "Real", "BinaryReal, and "ArrayReal".
 * @param problemId CEC2005 problem id
 * @param numberOfVariables Number of variables of the problem
 */
CEC2005Problem::CEC2005Problem(string solutionType, int problemID, int numberOfVariables) {
  numberOfVariables_   = numberOfVariables ;
  numberOfObjectives_  = 1;
  numberOfConstraints_ = 0;

  Benchmark * cec2005ProblemFactory = new Benchmark() ;
  testFunction_ = cec2005ProblemFactory->testFunctionFactory(problemID, numberOfVariables) ;
  delete cec2005ProblemFactory;

  problemName_ = "CEC2005: " + testFunction_->name();


  upperLimit_ = new double[numberOfVariables_];
  lowerLimit_ = new double[numberOfVariables_];

  double ulimit = 0 ;
  double llimit = 0 ;

  switch (problemID) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 14:
      ulimit = 100;
      llimit = -100 ;
      break ;
    case 7:
    case 25:
      ulimit = std::numeric_limits<double>::max();
      llimit = -std::numeric_limits<double>::max();
      break ;
    case 8:
      ulimit = 32; llimit = -32 ;
      break ;
    case 9:
    case 10:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
      ulimit = 5; llimit = -5 ;
      break ;
    case 11:
      ulimit = 0.5; llimit = -0.5 ;
      break ;
    case 12:
      ulimit = PI; llimit = -PI ;
      break ;
    case 13:
      ulimit = 3; llimit = 1 ;
      break ;
  }

  for (int var = 0; var < numberOfVariables_; var++){
    lowerLimit_[var] = llimit ;
    upperLimit_[var] = ulimit ;
  } // for

  if (solutionType.compare("BinaryReal") == 0)
    solutionType_ = new BinaryRealSolutionType(this) ;
  else if (solutionType.compare("Real") == 0)
    solutionType_ = new RealSolutionType(this) ;
  else {
    cout << "Error: solution type " << solutionType << " invalid" << endl;
    exit(-1) ;
  } // if

} // CEC2005Problem


/**
 * Destructor
 */
CEC2005Problem::~CEC2005Problem() {
  delete [] lowerLimit_ ;
  delete [] upperLimit_ ;
  delete solutionType_ ;
  delete testFunction_;
} // ~CEC2005Problem


/**
 * Evaluates a solution
 * @param solution The solution to evaluate
 */
void CEC2005Problem::evaluate(Solution *solution) {
  Variable ** decisionVariables  = solution->getDecisionVariables();
  double * x = new double[numberOfVariables_] ;

  for (int i = 0 ; i < numberOfVariables_; i++) {
    x[i] = decisionVariables[i]->getValue() ;
  }

  double result ;
  result = testFunction_->f(x) ;

  delete [] x;

  solution->setObjective(0, result);

} // evaluate
