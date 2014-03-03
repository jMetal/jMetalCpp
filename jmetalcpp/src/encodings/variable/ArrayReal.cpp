//  ArrayReal.cpp
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


#include <ArrayReal.h>


/**
 * Constructor
 */
ArrayReal::ArrayReal() {
  problem_ = NULL;
  size_   = 0;
  array_ = NULL;
} // Constructor


/**
 * Constructor
 * @param size Size of the array
 */
ArrayReal::ArrayReal(int size, Problem * problem) {
  problem_ = problem;
  size_   = size;
  array_ = new double[size_];

  for (int i = 0; i < size_ ; i++) {
    array_[i] = PseudoRandom::randDouble()*(problem_->getUpperLimit(i)-
                                           problem_->getLowerLimit(i))+
                                           problem_->getLowerLimit(i);
  } // for
} // Constructor


/**
 * Copy Constructor
 * @param arrayReal The arrayDouble to copy
 */
ArrayReal::ArrayReal(ArrayReal * arrayReal) {
  problem_ = arrayReal->problem_ ;
  size_  = arrayReal->size_;
  array_ = new double[size_];

  for (int i = 0; i < size_; i++) {
    array_[i] = arrayReal->array_[i];
  } // for
} // Copy Constructor


/**
 * Destructor
 */
ArrayReal::~ArrayReal() {
  delete [] array_;
} // ~ArrayReal


/**
 * Creates an exact copy of a <code>BinaryReal</code> object.
 * @return The copy of the object
 */
Variable * ArrayReal::deepCopy() {
  return new ArrayReal(this);
} // deepCopy


/**
 * Returns the length of the arrayReal.
 * @return The length
 */
int ArrayReal::getLength(){
  return size_;
} // getLength


/**
 * getValue
 * @param index Index of value to be returned
 * @return the value in position index
 */
double ArrayReal::getValue(int index) {
  if ((index >= 0) && (index < size_))
    return array_[index] ;
  else {
    cerr << "ArrayReal.getValue: index value (" << index << ") invalid" << endl;
    exit(-1);
  } // if
} // getValue

double ArrayReal::getValue() {
  cerr << "ERROR: ArrayReal::getValue() without index" << endl;
  exit(-1);
} // getValue


/**
 * setValue
 * @param index Index of value to be returned
 * @param value The value to be set in position index
 */
void ArrayReal::setValue(int index, double value) {
  if ((index >= 0) && (index < size_))
    array_[index] = value;
  else {
    cout << "ArrayReal.getValue: index value (" << index << ") invalid" << endl;
  } // if
} // setValue

void ArrayReal::setValue(double value) {
  cout << "ERROR: ArrayReal::setValue(value) without index" << endl;
} // setValue


/**
 * Get the lower bound of a value
 * @param index The index of the value
 * @return the lower bound
 */
double ArrayReal::getLowerBound(int index) {
  if ((index >= 0) && (index < size_))
    return problem_->getLowerLimit(index) ;
  else {
    cerr << "ArrayReal.getValue: index value (" << index << ") invalid" << endl;
    exit(-1);
  } // if
} // getLowerBound

double ArrayReal::getLowerBound() {
  cerr << "ERROR: ArrayReal::getLowerBound() without index" << endl;
  exit(-1);
} // getLowerBound


/**
 * Get the upper bound of a value
 * @param index The index of the value
 * @return the upper bound
 */
double ArrayReal::getUpperBound(int index) {
  if ((index >= 0) && (index < size_))
    return problem_->getUpperLimit(index);
  else {
    cerr << "ArrayReal.getValue: index value (" << index << ") invalid" << endl;
    exit(-1);
  } // if
} // getLowerBound

double ArrayReal::getUpperBound() {
  cerr << "ERROR: ArrayReal::getUpperBound() without index" << endl;
  exit(-1);
} // getUpperBound


/**
 * Returns a string representing the object
 * @return The string
 */
string ArrayReal::toString(){
  std::ostringstream ss;
  for (int i = 0; i < (size_ - 1); i ++) {
    ss << array_[i] << " ";
  }
  ss << array_[size_ -1];
  return ss.str();
} // toString
