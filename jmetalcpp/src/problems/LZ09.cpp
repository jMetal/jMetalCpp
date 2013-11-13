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
void LZ09::alphaFunction(double *alpha, vector<double> * x, int dim, int type) {
	if (dim == 2) {
		if (type == 21) {
			alpha[0] = x->at(0);
			alpha[1] = 1 - sqrt(x->at(0));
		}

		if (type == 22) {
			alpha[0] = x->at(0);
			alpha[1] = 1 - x->at(0) * x->at(0);
		}

		if (type == 23) {
			alpha[0] = x->at(0);
			alpha[1] = 1 - sqrt(alpha[0]) - alpha[0]
			           * sin(10 * alpha[0] * alpha[0] * 3.141596);
		}

		if (type == 24) {
			alpha[0] = x->at(0);
			alpha[1] = 1 - x->at(0) - 0.05 * sin(4 * 3.141596 * x->at(0));
		}
	} else {
		if (type == 31) {
			alpha[0] = cos(x->at(0) * 3.141596 / 2) * cos(x->at(1) * 3.141596 / 2);
			alpha[1] = cos(x->at(0) * 3.141596 / 2) * sin(x->at(1) * 3.141596 / 2);
			alpha[2] = sin(x->at(0) * 3.141596 / 2);
		}

		if (type == 32) {
			alpha[0] = 1 - cos(x->at(0) * 3.141596 / 2)
			* cos(x->at(1) * 3.141596 / 2);
			alpha[1] = 1 - cos(x->at(0) * 3.141596 / 2)
			* sin(x->at(1) * 3.141596 / 2);
			alpha[2] = 1 - sin(x->at(0) * 3.141596 / 2);
		}

		if (type == 33) {
			alpha[0] = x->at(0);
			alpha[1] = x->at(1);
			alpha[2] = 3
			- (sin(3 * 3.141596 * x->at(0)) + sin(3 * 3.141596 * x->at(1))) - 2
			* (x->at(0) + x->at(1));
		}

		if (type == 34) {
			alpha[0] = x->at(0) * x->at(1);
			alpha[1] = x->at(0) * (1 - x->at(1));
			alpha[2] = (1 - x->at(0));
		}
	}
}

/**
 * Beta function
 */


double LZ09::betaFunction(vector<double> * x, int type) {

	double beta;
	beta = 0;

	int dim = x->size() ;

	if (dim == 0)
		beta = 0;

	if (type == 1) {
		beta = 0;
		for (int i = 0; i < dim; i++) {
			beta += x->at(i) * x->at(i);
		}
		beta = 2.0 * beta / dim;
	}

	if (type == 2) {
		beta = 0;
		for (int i = 0; i < dim; i++) {
			beta += sqrt(i + 1) * x->at(i) * x->at(i);
		}
		beta = 2.0 * beta / dim;
	}

	if (type == 3) {
		double sum = 0, xx;
		for (int i = 0; i < dim; i++) {
			xx = 2 * x->at(i);
			sum += (xx * xx - cos(4 * 3.141596 * xx) + 1);
		}
		beta = 2.0 * sum / dim;
	}

	if (type == 4) {
		double sum = 0, prod = 1, xx;
		for (int i = 0; i < dim; i++) {
			xx = 2 * x->at(i);
			sum += xx * xx;
			prod *= cos(10 * 3.141596 * xx / sqrt(i + 1));
		}
		beta = 2.0 * (sum - 2 * prod + 2) / dim;
	}
	return beta;
}

double LZ09::psfunc2(double x, double t1, int dim, int type, int css) {
	double beta;
	beta = 0.0;

	dim++;

	if(type==21){
		double xy   = 2*(x - 0.5);
		beta = xy - pow(t1, 0.5*(nvar_ + 3*dim - 8)/(nvar_ - 2));
	}

	if(type==22){
		double theta = 6*3.141596*t1 + dim*3.141596/nvar_;
		double xy    = 2*(x - 0.5);
		beta = xy - sin(theta);
	}

	if(type==23){
		double theta = 6*3.141596*t1 + dim*3.141596/nvar_;
		double ra    = 0.8*t1;
		double xy    = 2*(x - 0.5);
		if(css==1)
			beta = xy - ra*cos(theta);
		else{
			beta = xy - ra*sin(theta);
		}
	}

	if(type==24){
		double theta = 6*3.141596*t1 + dim*3.141596/nvar_;
		double xy    = 2*(x - 0.5);
		double ra    = 0.8*t1;
		if(css==1)
			beta = xy - ra*cos(theta/3);
		else{
			beta = xy - ra*sin(theta);
		}
	}

	if(type==25){
		double rho   = 0.8;
		double phi   = 3.141596*t1;
		double theta = 6*3.141596*t1 + dim*3.141596/nvar_;
		double xy    = 2*(x - 0.5);
		if(css==1)
			beta = xy - rho*sin(phi)*sin(theta);
		else if(css==2)
			beta = xy - rho*sin(phi)*cos(theta);
		else
			beta = xy - rho*cos(phi);
	}

	if(type==26){
		double theta = 6*3.141596*t1 + dim*3.141596/nvar_;
		double ra    = 0.3*t1*(t1*cos(4*theta) + 2);
		double xy    = 2*(x - 0.5);
		if(css==1)
			beta = xy - ra*cos(theta);
		else{
			beta = xy - ra*sin(theta);
		}
	}

	return beta;
}

double LZ09::psfunc3(double x, double t1, double t2, int dim, int type){
	// type:  the type of curve
	// css:   the class of index
	double beta;
	beta = 0.0 ;

	dim++;

	if(type==31){
		double xy  = 4*(x - 0.5);
		double rate = 1.0*dim/nvar_;
		beta = xy - 4*(t1*t1*rate + t2*(1.0-rate)) + 2;
	}

	if(type==32){
		double theta = 2*3.141596*t1 + dim*3.141596/nvar_;
		double xy    = 4*(x - 0.5);
		beta = xy - 2*t2*sin(theta);
	}

	return beta;
}

void LZ09::objective(vector<double> *x_var, vector <double> *y_obj) {
	// 2-objective case
	if(nobj_==2)
	{
		if(ltype_==21||ltype_==22||ltype_==23||ltype_==24||ltype_==26)
		{
			double g = 0, h = 0, a, b;
			vector <double> aa  ; // *aa = new vector();
			vector <double> bb ; // *bb = new vector();
			for(int n=1;n<nvar_;n++)
			{

				if(n%2==0){
					a = psfunc2(x_var->at(n),x_var->at(0),n,ltype_,1);  // linkage
					aa.push_back(a);
				}
				else
				{
					b = psfunc2(x_var->at(n),x_var->at(0),n,ltype_,2);
					bb.push_back(b);
				}

			}

			g = betaFunction(&aa, dtype_);
			h = betaFunction(&bb, dtype_);

			double alpha[2] ;
			alphaFunction(alpha,x_var,2,ptype_);  // shape function
			y_obj->at(0) = alpha[0] + h;
			y_obj->at(1) = alpha[1] + g;
			aa.clear();
			bb.clear();
		}

		if(ltype_==25)
		{
			double g = 0, h = 0, a, b;
			double e = 0, c;
			vector <double> aa ; //= new Vector() ;
			vector <double> bb ; //= new Vector() ;
			for(int n=1;n<nvar_;n++){
				if(n%3==0){
					a = psfunc2(x_var->at(n),x_var->at(0),n,ltype_,1);
					aa.push_back(a);
				}
				else if(n%3==1)
				{
					b = psfunc2(x_var->at(n),x_var->at(0),n,ltype_,2);
					bb.push_back(b);
				}
				else{
					c = psfunc2(x_var->at(n),x_var->at(0),n,ltype_,3);
					if(n%2==0)    aa.push_back(c);
					else          bb.push_back(c);
				}
			}
			g = betaFunction(&aa,dtype_);          // distance function
			h = betaFunction(&bb,dtype_);

			//double * alpha = new double[2];
			double alpha[2] ;
			alphaFunction(alpha,x_var,2,ptype_);  // shape function
			y_obj->at(0) = alpha[0] + h;
			y_obj->at(1) = alpha[1] + g;
			aa.clear();
			bb.clear();
		}
	}


	// 3-objective case
	if(nobj_==3)
	{
		if(ltype_==31||ltype_==32)
		{
			double g = 0, h = 0, e = 0, a;
			vector <double> aa ;
			vector <double> bb ;
			vector <double> cc ;
			for(int n=2;n<nvar_;n++)
			{
				a = psfunc3(x_var->at(n),x_var->at(0),x_var->at(1),n,ltype_);
				if(n%3==0)	    aa.push_back(a);
				else if(n%3==1)	bb.push_back(a);
				else            cc.push_back(a);
			}

			g = betaFunction(&aa,dtype_);
			h = betaFunction(&bb,dtype_);
			e = betaFunction(&cc,dtype_);

			//double * alpha = new double[3];
			double alpha[3] ;
			alphaFunction(alpha,x_var,3,ptype_);  // shape function
			y_obj->at(0) = alpha[0] + h;
			y_obj->at(1) = alpha[1] + g;
			y_obj->at(2) = alpha[2] + e;
			aa.clear();
			bb.clear();
			cc.clear();
		}
	}
}


