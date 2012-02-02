/*
 * ZDT3.h
 *
 *  Created on: 10/12/2011
 *      Author: antonio
 */

#ifndef __ZDT3_H__
#define __ZDT3_H__

#include <Problem.h>
#include <math.h>
#include <cmath>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>


class ZDT3 : public Problem {
private:
	double evalG(XReal *x) ;
	double evalH(double f, double g) ;
	double * fx_ ;

public:
	ZDT3(string solutionType, int numberOfVariables = 30);
	void evaluate(Solution *solution);

	virtual ~ZDT3();
};

#endif /* __ZDT3_H__ */
