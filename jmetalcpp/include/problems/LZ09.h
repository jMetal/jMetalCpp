//  LZ09.h
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
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

#ifndef __LZ09_H__
#define __LZ09_H__

#include <math.h>
#include <cstdlib>
#include <vector>

using namespace std;

class LZ09 {
private:
	int nvar_  ;
	int nobj_  ;
	int ltype_ ;
  int dtype_ ;
  int ptype_ ;

public:
  LZ09 (int nvar, int nobj, int ptype, int dtype, int ltype) ;
	void alphaFunction(double *alpha, vector<double> *x, int dim, int type) ;
	double betaFunction(vector<double> * x, int type) ;
	double psfunc2(double x, double t1, int dim, int type, int css) ;
	double psfunc3(double x, double t1, double t2, int dim, int type) ;
	void objective(vector<double> * x_var, vector <double> * y_obj) ;

};

#endif /* __LZ09_H__ */
