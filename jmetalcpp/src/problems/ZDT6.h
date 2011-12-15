/*
 * ZDT6.h
 *
 *  Created on: 10/12/2011
 *      Author: antonio
 */

#ifndef __ZDT6_H__
#define __ZDT6_H__

#include <Problem.h>
#include <math.h>
#include <cmath>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>

class ZDT6 : public Problem {
private:
	double evalG(XReal *x) ;
	double evalH(double f, double g) ;
	double * fx_ ;

public:
	ZDT6(string solutionType, int numberOfVariables = 10);
	void evaluate(Solution *solution);

	virtual ~ZDT6();
};

#endif /* __ZDT6_H__ */
