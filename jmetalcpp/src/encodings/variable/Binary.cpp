//  Binary.cpp
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


#include <Binary.h>


/**
 * Default constructor.
 */
Binary::Binary() {
  bits_ = NULL ;
  numberOfBits_ = -1 ;
} //Binary


/**
 *  Constructor
 *  @param numberOfBits Length of the bit string
 */
Binary::Binary(int numberOfBits){
  numberOfBits_ = numberOfBits;

  bits_ = new vector<bool>(numberOfBits_, false) ;

  for (int i = 0; i < numberOfBits_; i++){
    if (PseudoRandom::randDouble() < 0.5) {
      (*bits_)[i] = true ;
    } else {
      (*bits_)[i] = false ;
    }
  }
} //Binary


/**
 * Copy constructor.
 * @param variable The Binary variable to copy.
 */
Binary::Binary(Binary * variable){
  numberOfBits_ = variable->getNumberOfBits();
  bits_ = new vector<bool>(numberOfBits_, false) ;
  for (int i = 0; i < numberOfBits_; i++) {
    (*bits_)[i] = (*variable->bits_)[i] ;
  }
} //Binary


/**
 * Destructor
 */
Binary::~Binary() {
  delete bits_;
} //~Binary


/**
 * This method is intended to be used in subclass of <code>Binary</code>,
 * for examples the classes, <code>BinaryReal</code> and <code>BinaryInt<codes>.
 * In this classes, the method allows to decode the
 * value encoded in the binary string. As generic variables do not encode any
 * value, this method do noting
 */
void Binary::decode() {
  //do nothing
} //decode


/**
 * Creates an exact copy of a Binary object
 * @return An exact copy of the object.
 **/
Variable * Binary::deepCopy() {
  return new Binary(this);
} //deepCopy


/**
 * Returns the length of the binary string.
 * @return The length
 */
int Binary::getNumberOfBits(){
  return numberOfBits_;
} //getNumberOfBits


/**
 * Returns the value of the ith bit.
 * @param bit The bit to retrieve
 * @return The ith bit
 */
bool Binary::getIth(int bit){
  return (*bits_)[bit];
} //getIth

/**
 * Flips the value of the ith bit.
 * @param bit The bit to flip
 */

void Binary::flip(int bit){
  (*bits_)[bit].flip();
} //blip

/**
 * Sets the value of the ith bit.
 * @param bit The bit to set
 */
void Binary::setIth(int bit, bool value){
  (*bits_)[bit] = value ;
} //getNumberOfBits


/**
* Obtain the hamming distance between two binary strings
* @param other The binary string to compare
* @return The hamming distance
*/
int Binary::hammingDistance(Binary * other) {
  int distance = 0;
  int i = 0;
  while (i < bits_->size()) {
    if ((*bits_)[i] != (*other->bits_)[i]) {
      distance++;
    }
    i++;
  }
  return distance;
} // hammingDistance


/**
 * Returns a string representing the object.
 * @return the string.
 */
string Binary::toString() {
  vector<bool>::iterator it;
  string str = "" ;
  for(it = bits_->begin(); it != bits_->end(); it++) {
    if (*it == true)
      str += "1" ;
    else
      str += "0" ;
  }
  return str ;
} // toString

/*
 * Returns the number of 1's in the binary variable
 */
int Binary::cardinality() {
  int counter = 0 ;
  vector<bool>::iterator it;
  for(it = bits_->begin(); it != bits_->end(); it++)
    if (*it == true)
      counter ++ ;
  return counter ;
}

double Binary::getValue() {
  return 0.0;
}

void Binary::setValue(double value) {
  //value_ = value;
}

double Binary::getLowerBound() {
  //  return 0.0;
  exit(-1);
}

double Binary::getUpperBound() {
//  return 0.0;
  exit(-1);
}
