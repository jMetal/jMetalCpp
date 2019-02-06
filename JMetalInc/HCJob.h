//  HCJob.h
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

#ifndef __H_C_JOB__
#define __H_C_JOB__

class HCJob {

public:

  // Number of basic functions
  int num_func;
  // Number of dimensions
  int num_dim;

  // Predefined constant
  double C;
  // Coverage range for each basic function
  double* sigma;
  // Biases for each basic function
  double* biases;
  // Stretch / compress each basic function
  double* lambda;
  // Estimated fmax
  double* fmax;
  // Shift global optimum for each basic function
  double** o;
  // Linear transformation matrix for each basic function
  double*** M;

  // Working areas to avoid memory allocation operations
  double* w;
  double** z;
  double** zM;
  HCJob(int numFunc);
  virtual ~HCJob();
  virtual double basic_func(int func_no, double* x, int length) = 0;

}; // HCJob

#endif /* __H_C_JOB__ */
