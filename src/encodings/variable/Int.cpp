//  Int.cpp
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


#include <Int.h>


/** 
  * Empty constructor. 
  * It will only initialize all the variables.
 **/
Int::Int() {
  value_ = 0.0;
} // Int


/**
 * Lower and Upper bounds based constructor.
 * It will initialize the upper and lower bounds of the 
 * variable and it will initialize its value to a random
 * value between those upper and lower bound values.
 **/
Int::Int(double lowerBound, double upperBound) {

  value_ = PseudoRandom::randInt(lowerBound, upperBound);

  lowerBound_ = lowerBound;
  upperBound_ = upperBound;
} // Int


/**
 * Constructor
 */
Int::Int(Variable * variable) {
  lowerBound_ = variable->getLowerBound();
  upperBound_ = variable->getUpperBound();
  value_      = variable->getValue();
} // Int


/**
 * Destructor
 */
Int::~Int() { /* do nothing */ }


/**
 * Gets the value of the <code>Int</code> variable.
 * @return the value.
 */
double Int::getValue() {
  return value_;
} // getValue


/**
 * Sets the value of the variable.
 * @param value The value.
 */
void Int::setValue(double value) {
  value_ = value;
} // setValue


/**
 * Returns a exact copy of the <code>Int</code> variable
 * @return the copy
 */
Variable *Int::deepCopy() {
  return new Int(this);
} // deepCopy


/**
 * Gets the lower bound of the variable.
 * @return the lower bound.
 */
double Int::getLowerBound() {
  return lowerBound_;
} // getLowerBound


/**
 * Gets the upper bound of the variable.
 * @return the upper bound.
 */
double Int::getUpperBound() {
  return upperBound_;
} // getUpperBound


/**
 * Sets the lower bound of the variable.
 * @param lowerBound The lower bound.
 */
void Int::setLowerBound(double bound) {
  lowerBound_ = bound;
} // setLowerBound


/**
 * Sets the upper bound of the variable.
 * @param upperBound The upper bound.
 */
void Int::setUpperBound(double bound) {
  upperBound_ = bound;
} // setUpperBound


/**
 * Returns a string representing the object
 * @return The string
 */
string Int::toString(){
  std::ostringstream stringStream;
  stringStream << value_ ;
  string aux = stringStream.str() + " ";

  return aux ;
} // toString
