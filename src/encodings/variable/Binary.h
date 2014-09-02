//  Binary.h
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


#ifndef Binary_h
#define Binary_h

#include <Variable.h>
#include <bitset>
#include <vector>
#include <PseudoRandom.h>
#include <stdlib.h>

/**
 * This class implements a generic binary string variable.It can be used as
 * a base class other binary string based classes (e.g., binary coded integer
 * or real variables).
 */
class Binary : public Variable {

public:

  Binary();
  Binary(int numberOfBits);
  Binary(Binary * variable);
  ~Binary();

  void decode();
  Variable * deepCopy();
  int getNumberOfBits();
  bool getIth(int bit);
  void setIth(int bit, bool value);
  void flip(int bit) ;
  int hammingDistance(Binary * other);
  string toString();
  int cardinality() ;

  double getValue();
  void setValue(double value);
  double getLowerBound();
  double getUpperBound();

protected:
  vector<bool> * bits_;
  int numberOfBits_;
};

#endif
