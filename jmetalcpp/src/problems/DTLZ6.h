/*
 * DTLZ6.h
 *
 *  Created on: 04/02/2012
 *      Author: antonio
 */

#ifndef __DTLZ6_H__
#define __DTLZ6_H__

#include <Problem.h>
#include <math.h>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>

class DTLZ6 : public Problem {
public:
	DTLZ6(string solutionType, int numberOfVariables = 12, int numberOfObjectives = 2);
	void evaluate(Solution *solution);

	virtual ~DTLZ6();
private:
	double * fx_ ;
  double * x_  ;
  double * theta_ ;
};

#endif /* __DTLZ6_H__ */
