/*
 * ZDT2.h
 *
 *  Created on: 10/12/2011
 *      Author: antonio
 */

#ifndef __ZDT2_H__
#define __ZDT2_H__

#include <Problem.h>
#include <math.h>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>


class ZDT2 : public Problem{
private:
	double evalG(XReal *x) ;
	double evalH(double f, double g) ;
	double * fx_ ;

public:
	ZDT2(string solutionType, int numberOfVariables = 30);
	void evaluate(Solution *solution);

	virtual ~ZDT2();
};

#endif /* __ZDT2_H__ */
