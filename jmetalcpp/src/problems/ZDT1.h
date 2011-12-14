/*
 * ZDT1.h
 *
 *  Created on: 09/12/2011
 *      Author: antonio
 */

#ifndef __ZDT1_H__
#define __ZDT1_H__

#include <Problem.h>
#include <math.h>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>

class ZDT1 : public Problem {
private:
	double evalG(XReal *x) ;
	double evalH(double f, double g) ;

public:
	ZDT1(string solutionType, int numberOfVariables = 30);
	void evaluate(Solution *solution);

	~ZDT1();
private:
	double * fx_ ;
  double * x_  ;
};

#endif /* ZDT1_H_ */
