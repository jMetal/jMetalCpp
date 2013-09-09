//  Real.h
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

#ifndef Real_h
#define Real_h

#include <Variable.h>
#include <PseudoRandom.h>
#include <sstream>

/**
 * This class implements a Real value decision variable
 */
class Real : public Variable {

public:

  Real();
  Real(double lowerBound, double upperBound);
  Real(Variable * variable);
  ~Real();

  double getValue();
  void setValue(double value);
  Variable * deepCopy();
  double getLowerBound();
  double getUpperBound();
  void setLowerBound(double bound);
  void setUpperBound(double bound);
  string toString() ;

private:
  double value_;
  double lowerBound_ ;
  double upperBound_ ;
};

#endif
