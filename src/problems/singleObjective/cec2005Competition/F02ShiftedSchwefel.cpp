//  F02ShiftedSchwefel.cpp
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


#include <F02ShiftedSchwefel.h>

// Fixed (class) parameters
const string F02ShiftedSchwefel::FUNCTION_NAME = "Shifted Schwefel's Problem 1.2";
// TODO: Cambiar ruta
const string F02ShiftedSchwefel::DEFAULT_FILE_DATA = "../../data/cec2005CompetitionResources/supportData/schwefel_102_data.txt";


/**
 * Constructor.
 */
F02ShiftedSchwefel::F02ShiftedSchwefel(int dimension, double bias)
    : F02ShiftedSchwefel(dimension, bias, DEFAULT_FILE_DATA) {
} // F02ShiftedSchwefel


/**
 * Constructor
 */
F02ShiftedSchwefel::F02ShiftedSchwefel(int dimension, double bias, string file_data)
    : TestFunc(dimension, bias, FUNCTION_NAME) {

  // Note: dimension starts from 0
  m_o = new double[m_dimension];
  m_z = new double[m_dimension];

  // Load the shifted global optimum
  Benchmark::loadRowVectorFromFile(file_data, m_dimension, m_o);

} // F02ShiftedSchwefel


/**
 * Destructor
 */
F02ShiftedSchwefel::~F02ShiftedSchwefel() {
  delete [] m_o;
  delete [] m_z;
} // ~F02ShiftedSchwefel


/**
 * Function body
 */
double F02ShiftedSchwefel::f(double * x) {
  double result = 0.0;

  Benchmark::shift(m_z, x, m_o, m_dimension);

  result = Benchmark::schwefel_102(m_z, m_dimension);

  result += m_bias;

  return result;
}
