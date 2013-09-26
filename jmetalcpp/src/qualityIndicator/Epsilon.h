//  Epsilon.h
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

#ifndef __EPSILON__
#define __EPSILON__

#include <MetricsUtil.h>
#include <vector>

/**
 * This class implements the unary epsilon additive indicator as proposed in
 * E. Zitzler, E. Thiele, L. Laummanns, M., Fonseca, C., and Grunert da Fonseca.
 * V (2003): Performance Assesment of Multiobjective Optimizers: An Analysis and
 * Review. The code is the a Java version of the orginal metric implementation
 * by Eckart Zitzler.
 * It can be used also as a command line program just by typing
 * $java jmetal.qualityIndicator.Epsilon <solutionFrontFile> <trueFrontFile> <numberOfOjbectives>
 */

class Epsilon {

private:

  int dim_; // stores the number of objectives
  int * obj_; // obj_[i]=0 means objective i is to be minimized. This code always supposes
              //the minimization of all the objectives
  int method_; // method_ = 0 means apply additive epsilon and method_ = 1 means multiplicative
               // epsilon. This code always apply additive epsilon

  void set_params();
  void free_params();

public:

  MetricsUtil * utils_; // stores a reference to  qualityIndicatorUtils

  Epsilon();
  ~Epsilon();
  double epsilon(vector <vector<double> > b, vector< vector<double> > a, int dim);

}; // Epsilon

#endif /* EPSILON_H_ */
