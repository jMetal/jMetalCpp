/*
 * DTLZ4.h
 *
 *  Created on: 09/12/2011
 *      Author: antonio
 */

#ifndef __DTLZ4_H__
#define __DTLZ4_H__

#include <Problem.h>
#include <math.h>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>

class DTLZ4 : public Problem {
public:
	DTLZ4(string solutionType, int numberOfVariables = 12, int numberOfObjectives = 3);
	void evaluate(Solution *solution);

	virtual ~DTLZ4();
};

#endif /* __DTLZ4_H__ */
