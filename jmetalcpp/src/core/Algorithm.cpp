//  Algorithm.cpp
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


#include <Algorithm.h>


/**
 * Constructor
 * @param problem
**/
Algorithm::Algorithm(Problem *problem) {
  problem_ = problem;
}


/**
 * Destructor
 */
Algorithm::~Algorithm() {
  delete problem_;
} // ~Algorithm


/**
 * Offers facilities for add new operators for the algorithm. To use an
 * operator, an algorithm has to obtain it through the
 * <code>getOperator</code> method.
 * @param name The operator name
 * @param operator The operator
**/
void Algorithm::addOperator(string name, Operator * operator_) {
  operators_[name] = operator_;
}


/**
 * Gets an operator through his name. If the operator doesn't exist or the
 * name is wrong this method returns null. The client of this method have to
 * check the result of the method.
 * @param name The operator name
 * @return The operator if exists, null in another case.
**/
Operator * Algorithm::getOperator(string name) {
  return operators_[name];
}


/**
 * Sets an input parameter to an algorithm. Typically,
 * the method is invoked by a Main object before running an algorithm.
 * The parameters have to been inserted using their name to access them
 * through the <code>getInputParameter</code> method.
 * @param name The parameter name
 * @param object Object that represent a parameter for the
 * algorithm.
**/
void Algorithm::setInputParameter(string name, void *value) {
  inputParameters_[name] = value;
}


/**
 * Gets an input parameter through its name. Typically,
 * the method is invoked by an object representing an algorithm
 * @param name The parameter name
 * @return Object representing the parameter or null if the parameter doesn't
 * exist or the name is wrong
**/
void * Algorithm::getInputParameter(string name) {
  return inputParameters_[name];
}


/**
 * Sets an output parameter that can be obtained by invoking
 * <code>getOutputParame</code>. Typically this algorithm is invoked by an
 * algorithm at the end of the <code>execute</code> to retrieve output
 * information
 * @param name The output parameter name
 * @param object Object representing the output parameter
**/
void Algorithm::setOutputParameter(string name, void *value) {
  outputParameters_[name] = value;
}


/**
 * Gets an output parameter through its name. Typically,
 * the method is invoked by a Main object after the execution of an algorithm.
 * @param name The output parameter name
 * @return Object representing the output parameter, or null if the parameter
 * doesn't exist or the name is wrong.
**/
void * Algorithm::getOutputParameter(string name) {
  return outputParameters_[name];
}


/**
 * Returns the problem to solve
 * @return Problem The problem to solve
**/
Problem * Algorithm::getProblem() {
  return problem_;
}
