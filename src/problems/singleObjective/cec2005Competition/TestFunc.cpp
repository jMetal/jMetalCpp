//  TestFunc.cpp
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


#include <TestFunc.h>

/**
 * Constructor.
 */
TestFunc::TestFunc(int dimension, double bias) : TestFunc(dimension, bias, "undefined") {
} // TestFunc

/**
 * Constructor
 */
TestFunc::TestFunc(int dimension, double bias, string func_name) {
  m_dimension = dimension;
  m_bias = bias;
  m_func_name = func_name;
} // TestFunc

/**
 * Destructor
 */
TestFunc::~TestFunc() {
} // ~TestFunc

int TestFunc::dimension() {
  return (m_dimension);
} // dimension

double TestFunc::bias() {
  return (m_bias);
} // bias

string TestFunc::name() {
  return (m_func_name);
} // name
