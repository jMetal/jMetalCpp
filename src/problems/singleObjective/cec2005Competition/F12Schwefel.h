//  F12Schwefel.h
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

#ifndef __F12_SCHWEFEL__
#define __F12_SCHWEFEL__

#include <Benchmark.h>
#include <TestFunc.h>

class F12Schwefel : public TestFunc {

private:

  // Fixed (class) parameters
  static const string FUNCTION_NAME;
  static const string DEFAULT_FILE_DATA;

  // Shifted global optimum
  double * m_o;
  double ** m_a;
  double ** m_b;

  // In order to avoid excessive memory allocation,
  // a fixed memory buffer is allocated for each function object.
  double * m_A;
  double * m_B;

public:

  F12Schwefel(int dimension, double bias);
  F12Schwefel(int dimension, double bias, string file_data);
  ~F12Schwefel();

  double f (double * x);

}; // F12Schwefel

#endif /* __F12_SCHWEFEL__ */
