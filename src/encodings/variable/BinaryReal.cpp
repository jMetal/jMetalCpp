//  BinaryReal.cpp
//
//  Author:
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


#include <BinaryReal.h>


/**
 * Defines the default number of bits used for binary coded variables.
 */
const int BinaryReal::DEFAULT_PRECISION = 30;


/**
 * Constructor.
 */
BinaryReal::BinaryReal() : Binary() { }


/**
 * Constructor
 * @param numberOfBits Length of the binary string.
 * @param lowerBound The lower limit for the variable
 * @param upperBound The upper limit for the variable.
 */
BinaryReal::BinaryReal(int numberOfBits, double lowerBound, double upperBound)
: Binary(numberOfBits) {
  lowerBound_ = lowerBound;
  upperBound_ = upperBound;
  this->decode();
} //BinaryReal


/**
 * Copy constructor
 * @param variable The variable to copy
 */
BinaryReal::BinaryReal(BinaryReal * variable) : Binary (variable) {
  lowerBound_   = variable->lowerBound_;
  upperBound_   = variable->upperBound_;
  value_ = variable->value_;
} //BinaryReal


/**
 * Destructor
 */
BinaryReal::~BinaryReal() { /* do nothing */ }


/**
 * Decodes the real value encoded in the binary string represented
 * by the <code>BinaryReal</code> object. The decoded value is stores in the
 * <code>value_</code> field and can be accessed by the method
 * <code>getValue</code>.
 */
void BinaryReal::decode(){
  double value = 0.0;
  for (int i = 0; i < numberOfBits_; i++) {
    if ((*bits_)[i] == true) {
      value += pow(2.0,i);
    }
  }
  value_ = value * (upperBound_ - lowerBound_) /
      (pow(2.0,numberOfBits_)-1.0);
  value_ += lowerBound_;
} //decode


/**
 * Returns the double value of the variable.
 * @return the double value.
 */
double BinaryReal::getValue() {
  return value_;
} //getValue


void BinaryReal::setValue(double value) {
  value_ = value;
}


/**
 * Creates an exact copy of a <code>BinaryReal</code> object.
 * @return The copy of the object
 */
Variable * BinaryReal::deepCopy() {
  return new BinaryReal(this);
} //deepCopy


/**
 * Returns the lower bound of the variable.
 * @return the lower bound.
 */
double BinaryReal::getLowerBound() {
  return lowerBound_;
} // getLowerBound


/**
 * Returns the upper bound of the variable.
 * @return the upper bound.
 */
double BinaryReal::getUpperBound() {
  return upperBound_;
} // getUpperBound


/**
 * Sets the lower bound of the variable.
 * @param lowerBound the lower bound.
 */
void BinaryReal::setLowerBound(double lowerBound) {
  lowerBound_ = lowerBound;
} // setLowerBound


/**
 * Sets the upper bound of the variable.
 * @param upperBound the upper bound.
 */
void BinaryReal::setUpperBound(double upperBound) {
  upperBound_ = upperBound;
} // setUpperBound


/**
 * Returns a string representing the object.
 * @return the string.
 */
string BinaryReal::toString() {
  std::ostringstream ss;
   ss << value_;
  return ss.str();
} // toString
