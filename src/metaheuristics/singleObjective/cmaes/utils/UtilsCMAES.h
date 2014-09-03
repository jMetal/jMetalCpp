//  UtilsCMAES.h
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

#ifndef __UTILS_CMAES__
#define __UTILS_CMAES__


#include <string>
#include <iostream>
#include <sstream>
#include <math.h>


using namespace std;


/**
 * Utilities methods to be used by CMA-ES
 */


class UtilsCMAES {
    
public:
  static void tred2 (int n, double ** V, double * d, double * e);
  static void tql2 (int n, double * d, double * e, double ** V);
  static int checkEigenSystem (int N, double ** C, double * diag, double ** Q);
  static double hypot (double a, double b);
  static void minFastSort (double * x, int * idx, int size);
  
};


#endif /* __UTILS_CMAES__ */
