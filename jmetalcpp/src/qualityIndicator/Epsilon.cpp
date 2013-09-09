//  Epsilon.cpp
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//
//  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
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


#include <Epsilon.h>


/**
 * Constructor
 * Creates a new instance of a Epsilon object
 */
Epsilon::Epsilon() {
  utils_ = new MetricsUtil();
} // Epsilon


/**
 * Destructor
 */
Epsilon::~Epsilon() {
  delete utils_;
} // ~Epsilon


/**
 * Returns the epsilon indicator.
 * @param b. True Pareto front
 * @param a. Solution front
 * @return the value of the epsilon indicator
 */
double Epsilon::epsilon(vector <vector<double> > b, vector <vector<double> > a,
    int dim) {

  int  i, j, k;
  double  eps, eps_j = 0.0, eps_k=0.0, eps_temp;

  dim_ = dim;
  set_params() ;

  if (method_ == 0)
    eps = -std::numeric_limits<double>::max();
  else
    eps= 0;

  for (i = 0; i < a.size(); i++) {
    for (j = 0; j < b.size(); j++) {
      for (k = 0; k < dim_; k++) {
        switch (method_) {
          case 0:
            if (obj_[k] == 0)
              eps_temp = b[j][k] - a[i][k];
              //eps_temp = b[j * dim_ + k] - a[i * dim_ + k];
            else
              eps_temp = a[i][k] - b[j][k];
              //eps_temp = a[i * dim_ + k] - b[j * dim_ + k];
            break;
          default:
            if ( (a[i][k] < 0 && b[j][k] > 0) ||
                 (a[i][k] > 0 && b[j][k] < 0) ||
                 (a[i][k] == 0 || b[j][k] == 0)) {
            //if ( (a[i * dim_ + k] < 0 && b[j * dim_ + k] > 0) ||
            //     (a[i * dim_ + k] > 0 && b[j * dim_ + k] < 0) ||
            //     (a[i * dim_ + k] == 0 || b[j * dim_ + k] == 0)) {
              cout << "error in data file" << endl;
              exit(-1);
            }
            if (obj_[k] == 0)
              eps_temp = b[j][k] / a[i][k];
              //eps_temp = b[j * dim_ + k] / a[i * dim_ + k];
            else
              eps_temp = a[i][k] / b[j][k];
              //eps_temp = a[i * dim_ + k] / b[j * dim_ + k];
          break;
        }
        if (k == 0)
          eps_k = eps_temp;
        else if (eps_k < eps_temp)
          eps_k = eps_temp;
      }
      if (j == 0)
        eps_j = eps_k;
      else if (eps_j > eps_k)
        eps_j = eps_k;
    }
    if (i == 0)
      eps = eps_j;
    else if (eps < eps_j)
      eps = eps_j;
  }
  free_params();
  return eps;
} // epsilon


/**
 * Established the params by default
 */
void Epsilon::set_params() {
  int  i;
  obj_ = new int[dim_];
  for (i = 0; i < dim_; i++) {
    obj_[i] = 0;
  }
  method_ = 0;
} // set_params


/**
 * Free the reserved memory for the params
 */
void Epsilon::free_params() {
  delete [] obj_;
} // set_params
