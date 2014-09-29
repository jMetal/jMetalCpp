//  F22RotatedHybridComposition3HighCondNumMatrix.h
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

#ifndef __F22_ROTATED_HYBRID_COMPOSITION_3_HIGH_COND_NUM_MATRIX__
#define __F22_ROTATED_HYBRID_COMPOSITION_3_HIGH_COND_NUM_MATRIX__

#include <Benchmark.h>
#include <HCJob.h>
#include <TestFunc.h>

class F22RotatedHybridComposition3HighCondNumMatrix : public TestFunc {

private:

  // Fixed (class) parameters
  static const string FUNCTION_NAME;
  static const string DEFAULT_FILE_DATA;
  static const string DEFAULT_FILE_MX_PREFIX;
  static const string DEFAULT_FILE_MX_SUFFIX;

  // Number of functions
  static const int NUM_FUNC = 10;

  // Shifted global optimum
  double ** m_o;
  double *** m_M;
  static const double m_sigma[NUM_FUNC];
  static const double m_lambda[NUM_FUNC];
  static const double m_func_biases[NUM_FUNC];
  double * m_testPoint;
  double * m_testPointM;
  double * m_fmax;

  // In order to avoid excessive memory allocation,
  // a fixed memory buffer is allocated for each function object.
  double * m_w;
  double ** m_z;
  double ** m_zM;

  class MyHCJob : public HCJob {
  public:
    MyHCJob(int numFunc);
    double basic_func(int func_no, double* x, int length);
  };

  MyHCJob * theJob;

  string getFileMxName(string prefix, int dimension, string suffix);

public:

  F22RotatedHybridComposition3HighCondNumMatrix(int dimension, double bias);
  F22RotatedHybridComposition3HighCondNumMatrix(int dimension, double bias, string file_data, string file_m);
  ~F22RotatedHybridComposition3HighCondNumMatrix();

  double f (double * x);

}; // F22RotatedHybridComposition3HighCondNumMatrix

#endif /* __F22_ROTATED_HYBRID_COMPOSITION_3_HIGH_COND_NUM_MATRIX__ */
