//  Variable.h
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

#ifndef __VARIABLE__
#define __VARIABLE__

#include <typeinfo>
#include <string>
#include <iostream>

using namespace std ;

/**
 * This is an abstract class for storing the variables composing a solution.  
 * Some examples of variables can be Real, Binary, etc. There is no guarantee
 * that those variables are implemented on the current version of this project
 */
class Variable {

public:
  virtual ~Variable() = 0;
  virtual Variable * deepCopy() = 0;
  virtual double getValue() = 0;
  virtual void setValue(double value) = 0;
  virtual double getLowerBound() = 0;
  virtual double getUpperBound() = 0;
  void setLowerBound(double bound);
  void setUpperBound(double bound);
  //void setVariableType(VariableType_ variableType);
  string getVariableType();
  virtual string toString() = 0;

}; // Variable

#endif
