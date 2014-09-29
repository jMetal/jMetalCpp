//  F03ShiftedRotatedHighCondElliptic.cpp
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


#include <F03ShiftedRotatedHighCondElliptic.h>

// Fixed (class) parameters
const string F03ShiftedRotatedHighCondElliptic::FUNCTION_NAME = "Shifted Rotated High Conditioned Elliptic Function";
// TODO: Cambiar ruta
const string F03ShiftedRotatedHighCondElliptic::DEFAULT_FILE_DATA = "../../data/cec2005CompetitionResources/supportData/high_cond_elliptic_rot_data.txt";
const string F03ShiftedRotatedHighCondElliptic::DEFAULT_FILE_MX_PREFIX = "../../data/cec2005CompetitionResources/supportData/Elliptic_M_D";
const string F03ShiftedRotatedHighCondElliptic::DEFAULT_FILE_MX_SUFFIX = ".txt";


/**
 * Constructor.
 */
F03ShiftedRotatedHighCondElliptic::F03ShiftedRotatedHighCondElliptic(int dimension, double bias)
    : F03ShiftedRotatedHighCondElliptic(dimension, bias, DEFAULT_FILE_DATA, getFileMxName(DEFAULT_FILE_MX_PREFIX, dimension, DEFAULT_FILE_MX_SUFFIX)) {
} // F03ShiftedRotatedHighCondElliptic


/**
 * Constructor
 */
F03ShiftedRotatedHighCondElliptic::F03ShiftedRotatedHighCondElliptic(int dimension, double bias, string file_data, string file_m)
    : TestFunc(dimension, bias, FUNCTION_NAME) {

  // Note: dimension starts from 0
  m_o = new double[m_dimension];
  m_matrix = new double*[m_dimension];
  for (int i=0; i<m_dimension; i++) {
    m_matrix[i] = new double[m_dimension];
  }
  m_z = new double[m_dimension];
  m_zM = new double[m_dimension];

  // Load the shifted global optimum
  Benchmark::loadRowVectorFromFile(file_data, m_dimension, m_o);
  // Load the matrix
  Benchmark::loadMatrixFromFile(file_m, m_dimension, m_dimension, m_matrix);

  constant = pow(1.0e6, 1.0/(m_dimension-1.0));

} // F03ShiftedRotatedHighCondElliptic


/**
 * Destructor
 */
F03ShiftedRotatedHighCondElliptic::~F03ShiftedRotatedHighCondElliptic() {
  delete [] m_o;
  for (int i=0; i<m_dimension; i++) {
    delete [] m_matrix[i];
  }
  delete [] m_matrix;
  delete [] m_z;
  delete [] m_zM;
} // ~F03ShiftedRotatedHighCondElliptic


/**
 * Function body
 */
double F03ShiftedRotatedHighCondElliptic::f(double * x) {
  double result = 0.0;

  Benchmark::shift(m_z, x, m_o, m_dimension);
  Benchmark::rotate(m_zM, m_z, m_matrix, m_dimension);

  double sum = 0.0;

  for (int i = 0 ; i < m_dimension ; i ++) {
    sum += pow(constant, i) * m_zM[i] * m_zM[i];
  }

  result = sum + m_bias;

  return result;
}


string F03ShiftedRotatedHighCondElliptic::getFileMxName(string prefix, int dimension, string suffix) {
  std::stringstream sstm;
  sstm << prefix << dimension << suffix;
  return sstm.str();
}
