//  F12Schwefel.cpp
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


#include <F12Schwefel.h>

// Fixed (class) parameters
const string F12Schwefel::FUNCTION_NAME = "Schwefel's Problem 2.13";
// TODO: Cambiar ruta
const string F12Schwefel::DEFAULT_FILE_DATA = "../../data/cec2005CompetitionResources/supportData/schwefel_213_data.txt";


/**
 * Constructor.
 */
F12Schwefel::F12Schwefel(int dimension, double bias)
    : F12Schwefel(dimension, bias, DEFAULT_FILE_DATA) {
} // F12Schwefel


/**
 * Constructor
 */
F12Schwefel::F12Schwefel(int dimension, double bias, string file_data)
    : TestFunc(dimension, bias, FUNCTION_NAME) {

  // Note: dimension starts from 0
  m_o = new double[m_dimension];
  m_a = new double*[m_dimension];
  for (int i = 0; i < m_dimension; i++) {
    m_a[i] = new double[m_dimension];
  }
  m_b = new double*[m_dimension];
  for (int i = 0; i < m_dimension; i++) {
    m_b[i] = new double[m_dimension];
  }

  m_A = new double[m_dimension];
  m_B = new double[m_dimension];

  // Data:
  //  1. a    100x100
  //  2. b    100x100
  //  3. alpha  1x100
  double ** m_data = new double*[100+100+1];
  for (int i = 0; i < (100+100+1); i++) {
    m_data[i] = new double[m_dimension];
  }

  // Load the shifted global optimum
  Benchmark::loadMatrixFromFile(file_data, (100+100+1), m_dimension, m_data);
  for (int i = 0 ; i < m_dimension; i++) {
    for (int j = 0 ; j < m_dimension; j++) {
      m_a[i][j] = m_data[i][j];
      m_b[i][j] = m_data[100+i][j];
    }
    m_o[i] = m_data[100+100][i];
  }

  for (int i = 0; i < m_dimension; i++) {
    m_A[i] = 0.0;
    for (int j = 0; j < m_dimension; j++) {
      m_A[i] += (m_a[i][j] * sin(m_o[j]) + m_b[i][j] * cos(m_o[j]));
    }
  }

  for (int i = 0; i < (100+100+1); i++) {
    delete [] m_data[i];
  }
  delete [] m_data;

} // F12Schwefel


/**
 * Destructor
 */
F12Schwefel::~F12Schwefel() {
  delete [] m_o;
  for (int i = 0; i < m_dimension; i++) {
    delete [] m_a[i];
  }
  delete [] m_a;
  for (int i = 0; i <m_dimension; i++) {
    delete [] m_b[i];
  }
  delete [] m_b;
  delete [] m_A;
  delete [] m_B;
} // ~F12Schwefel


/**
 * Function body
 */
double F12Schwefel::f(double * x) {
  double sum = 0.0;

  for (int i = 0 ; i < m_dimension; i++) {
    m_B[i] = 0.0;
    for (int j = 0; j < m_dimension; j++) {
      m_B[i] += (m_a[i][j] * sin(x[j]) + m_b[i][j] * cos(x[j]));
    }

    double temp = m_A[i] - m_B[i];
    sum += (temp * temp);
  }

  return (sum + m_bias);
}
