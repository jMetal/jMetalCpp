//  Problem.cpp
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
//       Juan J. Durillo <durillo@lcc.uma.es>
//       Esteban López-Camacho <esteban@lcc.uma.es>
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


#include <Problem.h>


const int Problem::DEFAULT_PRECISSION = 16;


/**
 * Constructor.
 */
Problem::Problem() {
  solutionType_ = NULL;
} // Problem


/**
 * Constructor.
 */
Problem::Problem(SolutionType * solutionType) {
  solutionType_ = solutionType ;
} // Problem


/**
 * Destructor
 */
Problem::~Problem() { } // ~Problem


//void Problem::evaluateConstraints(Solution solution) {};


/**
 * Gets the number of decision variables of the problem.
 * @return the number of decision variables.
 */
int Problem::getNumberOfVariables() {
  return numberOfVariables_;
} // getNumberOfVariables


/**
 * Sets the number of decision variables of the problem.
 */
void Problem::setNumberOfVariables(int numberOfVariables) {
  numberOfVariables_ = numberOfVariables;
} // setNumberOfVariables


/**
 * Gets the the number of objectives of the problem.
 * @return the number of objectives.
 */
int Problem::getNumberOfObjectives() {
  return numberOfObjectives_;
} // getNumberOfObjectives


/**
 * Sets the the number of objectives of the problem.
 */
void Problem::setNumberOfObjectives(int numberOfObjectives) {
  numberOfObjectives_ = numberOfObjectives;
} // setNumberOfObjectives
  

/**
 * Gets the lower bound of the ith variable of the problem.
 * @param i The index of the variable.
 * @return The lower bound.
 */
double Problem::getLowerLimit(int i) {
  if ((lowerLimit_ == NULL) || (i >= numberOfVariables_)) {
    cout << "Error: lower limits have been not initialized or accessing to a variable out of range" << endl;
    // exit(-1);
  }
  return lowerLimit_[i];
} // getLowerLimit


/**
 * Gets the upper bound of the ith variable of the problem.
 * @param i The index of the variable.
 * @return The upper bound.
 */
double Problem::getUpperLimit(int i) {
  if ((upperLimit_ == NULL) || (i >= numberOfVariables_)) {
    cout << "Error: upper limits have been not initialized or accessing to a variable out of range" << endl;
    //exit(-1);
  }
  return upperLimit_[i];
} // getUpperLimit


/**
 * Gets the number of side constraints in the problem.
 * @return the number of constraints.
 */
int Problem::getNumberOfConstraints() {
  return numberOfConstraints_ ;
} // getNumberOfConstraints


/**
 * Evaluates the overall constraint violation of a <code>Solution</code>
 * object.
 * @param solution The <code>Solution</code> to evaluate.
 */
void Problem::evaluateConstraints(Solution * solution) {
  // The default behavior is to do nothing. Only constrained problems have to
  // re-define this method
} // evaluateConstraints


/**
 * Returns the number of bits that must be used to encode binary-real
 * variables
 * @return the number of bits.
 */
int Problem::getPrecision(int var) {
  return precision_[var] ;
} // getPrecision


/**
 * Returns array containing the number of bits that must be used to encode
 * binary-real variables.
 * @return the number of bits.
 */
int * Problem::getPrecision() {
  return precision_;
} // getPrecision


/**
 * Sets the array containing the number of bits that must be used to encode
 * binary-real variables.
 * @param precision The array
 */
void Problem::setPrecision(int * precision) {
  precision_ = precision;
} // setPrecision


/**
 * Returns the length of the variable.
 * @return the variable length.
 */
int Problem::getLength(int var) {
  if (length_ == NULL) {
    return DEFAULT_PRECISSION;
  }
  return length_[var] ;
} // getLength

/**
 * Returns the number of bits of the solutions of the problem
 * @return The number of bits solutions of the problem
 */
int Problem::getNumberOfBits() {
  int result = 0;
  for (int var = 0; var < numberOfVariables_; var++) {
    result += getLength(var);
  }
  return result;
} // getNumberOfBits


///**
// * Gets the number of side constraints in the problem.
// * @return the number of constraints.
// */
//int Problem::getNumberOfConstraints() {
//  return numberOfConstraints_;
//} // getNumberOfConstraints
  

/**
 * Sets the type of the variables of the problem.
 * @param type The type of the variables
 */
void Problem::setSolutionType(SolutionType * type) {
  solutionType_ = type;
} // setSolutionType


/**
 * Returns the type of the variables of the problem.
 * @return type of the variables of the problem.
 */
SolutionType * Problem::getSolutionType() {
  return solutionType_;
} // getSolutionType


/**
 * Returns the problem name
 * @return The problem name
 */
string Problem::getName() {
  return problemName_;
} // getName
  
