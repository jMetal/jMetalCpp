//  F05SchwefelGlobalOptBound.cpp
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


#include <F05SchwefelGlobalOptBound.h>

// Fixed (class) parameters
const string F05SchwefelGlobalOptBound::FUNCTION_NAME = "Schwefel's Problem 2.6 with Global Optimum on Bounds";
// TODO: Cambiar ruta
const string F05SchwefelGlobalOptBound::DEFAULT_FILE_DATA = "../../data/cec2005CompetitionResources/supportData/schwefel_206_data.txt";


/**
 * Constructor.
 */
F05SchwefelGlobalOptBound::F05SchwefelGlobalOptBound(int dimension, double bias)
    : F05SchwefelGlobalOptBound(dimension, bias, DEFAULT_FILE_DATA) {
} // F05SchwefelGlobalOptBound


/**
 * Constructor
 */
F05SchwefelGlobalOptBound::F05SchwefelGlobalOptBound(int dimension, double bias, string file_data)
    : TestFunc(dimension, bias, FUNCTION_NAME) {

  // Note: dimension starts from 0
  m_o = new double[m_dimension];
  m_A = new double*[m_dimension];
  for (int i=0; i<m_dimension; i++) {
    m_A[i] = new double[m_dimension];
  }
  m_B = new double[m_dimension];
  m_z = new double[m_dimension];

  double ** m_data = new double*[m_dimension+1];
  for (int i=0; i<m_dimension+1; i++) {
    m_data[i] = new double[m_dimension];
  }

  // Load the shifted global optimum
  Benchmark::loadMatrixFromFile(file_data, m_dimension + 1, m_dimension, m_data);
  for (int i = 0 ; i < m_dimension ; i ++) {
    if ((i+1) <= ceil(m_dimension / 4.0)) {
      m_o[i] = -100.0;
    } else if ((i+1) >= floor((3.0 * m_dimension) / 4.0)) {
      m_o[i] = 100.0;
    } else {
      m_o[i] = m_data[0][i];
    }
  }
  for (int i = 0 ; i < m_dimension ; i ++) {
    for (int j = 0 ; j < m_dimension ; j ++) {
      m_A[i][j] = m_data[i+1][j];
    }
  }
  Benchmark::Ax(m_B, m_A, m_o, m_dimension);

  for (int i=0; i<m_dimension+1; i++) {
    delete [] m_data[i];
  }
  delete [] m_data;

} // F05SchwefelGlobalOptBound


/**
 * Destructor
 */
F05SchwefelGlobalOptBound::~F05SchwefelGlobalOptBound() {
  delete [] m_o;
  for (int i=0; i<m_dimension; i++) {
    delete [] m_A[i];
  }
  delete [] m_A;
  delete [] m_B;
  delete [] m_z;
} // ~F05SchwefelGlobalOptBound


/**
 * Function body
 */
double F05SchwefelGlobalOptBound::f(double * x) {
  double max = -numeric_limits<double>::max();

  Benchmark::Ax(m_z, m_A, x, m_dimension);

  for (int i = 0 ; i < m_dimension ; i ++) {
    double temp = fabs(m_z[i] - m_B[i]);
    if (max < temp) {
      max = temp;
    }
  }

  return (max + m_bias);
}
