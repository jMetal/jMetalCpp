/*
 * ZDT4.h
 *
 *  Created on: 10/12/2011
 *      Author: antonio
 */

#ifndef __ZDT4_H__
#define __ZDT4_H__

#include <Problem.h>
#include <math.h>
#include <cmath>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>


class ZDT4 : public Problem {
private:
	double evalG(XReal *x) ;
	double evalH(double f, double g) ;

public:
	ZDT4(string solutionType, int numberOfVariables = 10);
	void evaluate(Solution *solution);

	virtual ~ZDT4();
private:
	double * fx_ ;
  double * x_  ;
};

#endif /* __ZDT4_H__ */
