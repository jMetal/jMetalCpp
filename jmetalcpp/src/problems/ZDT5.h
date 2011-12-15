/*
 * ZDT5.h
 *
 *  Created on: 15/12/2011
 *      Author: antonio
 */

#ifndef __ZDT15_H__
#define __ZDT5_H__

#include <Problem.h>
#include <math.h>
#include <cmath>
#include <BinarySolutionType.h>
#include <Solution.h>

class ZDT5 : public Problem {
private:
	double evalG(Solution *x) ;
	double evalH(double f, double g) ;
  double evalV(double) ;

	double * fx_ ;
public:
	ZDT5(string solutionType, int numberOfVariables = 11);
	void evaluate(Solution *solution);

	virtual ~ZDT5();
};

#endif /* __ZDT5_H__ */
