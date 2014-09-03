//  TestFunc.h
//
//  Authors:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//       Antonio J. Nebro <antonio@lcc.uma.es>
//
//  Copyright (c) 2014 Antonio J. Nebro
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

#ifndef __TEST_FUNC__
#define __TEST_FUNC__

#include <string>

using namespace std;

class TestFunc {

protected:
  int m_dimension;
  double m_bias;
  string m_func_name;

public:
  TestFunc(int dimension, double bias);
  TestFunc(int dimension, double bias, string func_name);
  virtual ~TestFunc();
  virtual double f(double * x) = 0;
  int dimension();
  double bias();
  string name();

}; // TestFunc

#endif /* __TEST_FUNC__ */
