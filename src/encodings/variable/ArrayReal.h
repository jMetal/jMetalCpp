//  ArrayReal.h
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

#ifndef Array_Real_h
#define Array_Real_h

#include <Variable.h>
#include <Problem.h>
#include <PseudoRandom.h>
#include <sstream>

/**
 * Class implementing a decision variable representing an array of real values.
 * The real values of the array have their own bounds.
 */
class ArrayReal : public Variable {

public:

  double * array_;
  Problem * problem_;
  int size_;

  ArrayReal();
  ArrayReal(int size, Problem * problem);
  ArrayReal(ArrayReal * arrayReal);
  ~ArrayReal();

  Variable * deepCopy();
  int getLength();
  double getValue(int index);
  void setValue(int index, double value);
  double getLowerBound(int index);
  double getUpperBound(int index);
  string toString();

  void setValue(double value);
  double getValue();
  double getLowerBound();
  double getUpperBound();
};

#endif
