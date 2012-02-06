/*
 * DTLZ7.h
 *
 *  Created on: 04/02/2012
 *      Author: antonio
 */

#ifndef __DTLZ7_H__
#define __DTLZ7_H__

#include <Problem.h>
#include <math.h>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>

class DTLZ7 : public Problem {
public:
	DTLZ7(string solutionType, int numberOfVariables = 12, int numberOfObjectives = 3);
	void evaluate(Solution *solution);

	virtual ~DTLZ7();
private:
	double * fx_ ;
  double * x_  ;
};

#endif /* __DTLZ7_H__ */
