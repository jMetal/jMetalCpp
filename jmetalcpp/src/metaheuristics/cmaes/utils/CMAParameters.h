//  CMAParameters.h
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

#ifndef __CMA_PARAMETERS__
#define __CMA_PARAMETERS__

#include <math.h>

class CMAParameters {
  
private:
  
	int supplemented; // after supplementation it is undecidable whether a parameter was 
	                  // explicitly set from outside, therefore another supplementation is not advisable
	int locked; // lock when lambda is used to new data structures
	int lambda;          /* -> mu, <- N */
	int mu;              /* -> weights, (lambda) */
	double mucov;        /* -> ccov */
	double mueff;        /* <- weights */
	double * weights;    /* <- mu, -> mueff, mucov, ccov */
	double damps;        /* <- cs, maxeval, lambda */
	double cs;           /* -> damp, <- N */
	double cc;           /* <- N */
	double ccov;         /* <- mucov, <- N, <- diagonalcov */
	double ccovsep;      /* <- ccov */

	double chiN;
  
  void setDefaults(int N, int lambda);
  void setWeights(int mu);
  void setWeights(double * w, int weightsLength);
    
public:
  
  CMAParameters(int N, int lambda);
  int getMu();
  double * getWeights();
  double getMucov();
  double getCcov(bool flgdiag);
  double getCcov();
  double getMueff();
  double getDamps();
  double getCc();
  double getCs();
  
  double getChiN(); 
  
};

#endif /* __CMA_PARAMETERS__ */
