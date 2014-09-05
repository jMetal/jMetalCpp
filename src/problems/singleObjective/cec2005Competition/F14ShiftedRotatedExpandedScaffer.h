//  F14ShiftedRotatedExpandedScaffer.h
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

#ifndef __F14_SHIFTED_ROTATED_EXPANDED_SCAFFER__
#define __F14_SHIFTED_ROTATED_EXPANDED_SCAFFER__

#include <Benchmark.h>
#include <TestFunc.h>

class F14ShiftedRotatedExpandedScaffer : public TestFunc {

private:

  // Fixed (class) parameters
  static const string FUNCTION_NAME;
  static const string DEFAULT_FILE_DATA;
  static const string DEFAULT_FILE_MX_PREFIX;
  static const string DEFAULT_FILE_MX_SUFFIX;

  // Shifted global optimum
  double * m_o;
  double ** m_matrix;

  // In order to avoid excessive memory allocation,
  // a fixed memory buffer is allocated for each function object.
  double * m_z;
  double * m_zM;

  string getFileMxName(string prefix, int dimension, string suffix);

public:

  F14ShiftedRotatedExpandedScaffer(int dimension, double bias);
  F14ShiftedRotatedExpandedScaffer(int dimension, double bias, string file_data, string file_m);
  ~F14ShiftedRotatedExpandedScaffer();

  double f (double * x);

}; // F14ShiftedRotatedExpandedScaffer

#endif /* __F14_SHIFTED_ROTATED_EXPANDED_SCAFFER__ */
