/*
 * DTLZ3.h
 *
 *  Created on: 09/12/2011
 *      Author: antonio
 */

#ifndef __DTLZ3_H__
#define __DTLZ3_H__

#include <Problem.h>
#include <math.h>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>

class DTLZ3 : public Problem {
public:
	DTLZ3(string solutionType, int numberOfVariables = 12, int numberOfObjectives = 3);
	void evaluate(Solution *solution);

	virtual ~DTLZ3();
};

#endif /* __DTLZ3_H__ */
