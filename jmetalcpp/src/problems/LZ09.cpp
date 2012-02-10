//  LZ09.cpp
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

#include <LZ09.h>

/**
 * Constructor
 */
LZ09::LZ09(int nvar, int nobj, int ptype, int dtype, int ltype) {
	nvar_ = nvar ;
	nobj_ = nobj ;
	ltype_ = ltype ;
	dtype_ = dtype ;
  ptype_ = ptype ;
} // LZ09::LZ09

/**
 * Alpha function
 */
void LZ09::alphaFunction(double *alpha, double* x, int dim, int type) {
	if (dim == 2) {
		if (type == 21) {
			alpha[0] = x[0];
			alpha[1] = 1 - sqrt(x[0]);
		}

		if (type == 22) {
			alpha[0] = x[0];
			alpha[1] = 1 - x[0] * x[0];
		}

		if (type == 23) {
			alpha[0] = x[0];
			alpha[1] = 1 - sqrt(alpha[0]) - alpha[0]
			           * sin(10 * alpha[0] * alpha[0] * M_PI);
		}

		if (type == 24) {
			alpha[0] = x[0];
			alpha[1] = 1 - x[0] - 0.05 * sin(4 * M_PI * x[0]);
		}
	} else {
		if (type == 31) {
			alpha[0] = cos(x[0] * M_PI / 2) * cos(x[1] * M_PI / 2);
			alpha[1] = cos(x[0] * M_PI / 2) * sin(x[1] * M_PI / 2);
			alpha[2] = sin(x[0] * M_PI / 2);
		}

		if (type == 32) {
			alpha[0] = 1 - cos(x[0] * M_PI / 2)
			* cos(x[1] * M_PI / 2);
			alpha[1] = 1 - cos(x[0] * M_PI / 2)
			* sin(x[1] * M_PI / 2);
			alpha[2] = 1 - sin(x[0] * M_PI / 2);
		}

		if (type == 33) {
			alpha[0] = x[0];
			alpha[1] = x[1];
			alpha[2] = 3
			- (sin(3 * M_PI * x[0]) + sin(3 * M_PI * x[1])) - 2
			* (x[0] + x[1]);
		}

		if (type == 34) {
			alpha[0] = x[0] * x[1];
			alpha[1] = x[0] * (1 - x[1]);
			alpha[2] = (1 - x[0]);
		}
	}
}

/**
 * Beta function
 */
double LZ09::betaFunction(vector<double> x, int type) {

	double beta;
	beta = 0;
	/*
	int dim = x.size();

	if (dim == 0)
		beta = 0;

	if (type == 1) {
		beta = 0;
		for (int i = 0; i < dim; i++) {
			beta += x.elementAt(i) * x.elementAt(i);
		}
		beta = 2.0 * beta / dim;
	}

	if (type == 2) {
		beta = 0;
		for (int i = 0; i < dim; i++) {
			beta += Math.sqrt(i + 1) * x.elementAt(i) * x.elementAt(i);
		}
		beta = 2.0 * beta / dim;
	}

	if (type == 3) {
		double sum = 0, xx;
		for (int i = 0; i < dim; i++) {
			xx = 2 * x.elementAt(i);
			sum += (xx * xx - Math.cos(4 * Math.PI * xx) + 1);
		}
		beta = 2.0 * sum / dim;
	}

	if (type == 4) {
		double sum = 0, prod = 1, xx;
		for (int i = 0; i < dim; i++) {
			xx = 2 * x.elementAt(i);
			sum += xx * xx;
			prod *= Math.cos(10 * Math.PI * xx / Math.sqrt(i + 1));
		}
		beta = 2.0 * (sum - 2 * prod + 2) / dim;
	}
*/
	return beta;
}


