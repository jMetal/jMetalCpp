//  F01ShiftedSphere.cpp
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


#include <F01ShiftedSphere.h>

// Fixed (class) parameters
const string F01ShiftedSphere::FUNCTION_NAME = "Shifted Sphere Function";
// TODO: Cambiar ruta
const string F01ShiftedSphere::DEFAULT_FILE_DATA = "../../data/cec2005CompetitionResources/supportData/sphere_func_data.txt";


/**
 * Constructor.
 */
F01ShiftedSphere::F01ShiftedSphere(int dimension, double bias)
    : F01ShiftedSphere(dimension, bias, DEFAULT_FILE_DATA) {
} // F01ShiftedSphere


/**
 * Constructor
 */
F01ShiftedSphere::F01ShiftedSphere(int dimension, double bias, string file_data)
    : TestFunc(dimension, bias, FUNCTION_NAME) {

  // Note: dimension starts from 0
  m_o = new double[m_dimension];
  m_z = new double[m_dimension];

  // Load the shifted global optimum
  Benchmark::loadRowVectorFromFile(file_data, m_dimension, m_o);

} // F01ShiftedSphere


/**
 * Destructor
 */
F01ShiftedSphere::~F01ShiftedSphere() {
  delete [] m_o;
  delete [] m_z;
} // ~F01ShiftedSphere


/**
 * Function body
 */
double F01ShiftedSphere::f(double * x) {
  double result = 0.0;

  Benchmark::shift(m_z, x, m_o, m_dimension);

  result = Benchmark::sphere(m_z, m_dimension);

  result += m_bias;

  return result;
}
