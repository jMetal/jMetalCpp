//  Real.cpp
//
//  Author:
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


#include <Real.h>


/** 
  * Empty constructor. 
  * It will only initialize all the variables.
 **/
Real::Real() {
  value_ = 0.0;
} // Real


/**
 * Lower and Upper bounds based constructor.
 * It will initialize the upper and lower bounds of the 
 * variable and it will initialize its value to a random
 * value between those upper and lower bound values.
 **/
Real::Real(double lowerBound, double upperBound) {
  value_ = PseudoRandom::randDouble(lowerBound, upperBound);
  lowerBound_ = lowerBound;
  upperBound_ = upperBound;
} // Real


/**
 * Constructor
 */
Real::Real(Variable * variable) {
  lowerBound_ = variable->getLowerBound();
  upperBound_ = variable->getUpperBound();
  value_      = variable->getValue();
} // Real


/**
 * Destructor
 */
Real::~Real() { /* do nothing */ }


/**
 * Gets the value of the <code>Real</code> variable.
 * @return the value.
 */
double Real::getValue() {
  return value_;
} // getValue


/**
 * Sets the value of the variable.
 * @param value The value.
 */
void Real::setValue(double value) {
  value_ = value;
} // setValue


/**
 * Returns a exact copy of the <code>Real</code> variable
 * @return the copy
 */
Variable *Real::deepCopy() {
  return new Real(this);
} // deepCopy


/**
 * Gets the lower bound of the variable.
 * @return the lower bound.
 */
double Real::getLowerBound() {
  return lowerBound_;
} // getLowerBound


/**
 * Gets the upper bound of the variable.
 * @return the upper bound.
 */
double Real::getUpperBound() {
  return upperBound_;
} // getUpperBound


/**
 * Sets the lower bound of the variable.
 * @param lowerBound The lower bound.
 */
void Real::setLowerBound(double bound) {
  lowerBound_ = bound;
} // setLowerBound


/**
 * Sets the upper bound of the variable.
 * @param upperBound The upper bound.
 */
void Real::setUpperBound(double bound) {
  upperBound_ = bound;
} // setUpperBound


/**
 * Returns a string representing the object
 * @return The string
 */
string Real::toString(){
  std::ostringstream stringStream;
  stringStream << value_ ;
  string aux = stringStream.str() + " ";

  return aux ;
} // toString
