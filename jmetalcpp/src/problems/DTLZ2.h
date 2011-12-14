/*
 * DTLZ2.h
 *
 *  Created on: 09/12/2011
 *      Author: antonio
 */

#ifndef __DTLZ2_H__
#define __DTLZ2_H__

#include <Problem.h>
#include <math.h>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>

class DTLZ2 : public Problem {
public:
	DTLZ2(string solutionType, int numberOfVariables = 12, int numberOfObjectives = 3);
	void evaluate(Solution *solution);

	virtual ~DTLZ2();
private:
	double * fx_ ;
  double * x_  ;
};

#endif /* __DTLZ2_H__ */
