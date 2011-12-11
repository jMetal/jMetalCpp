/*
 * DTLZ1.h
 *
 *  Created on: 09/12/2011
 *      Author: antonio
 */

#ifndef __DTLZ1_H__
#define __DTLZ1_H__

#include <Problem.h>
#include <math.h>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>

class DTLZ1 : public Problem {
public:
	DTLZ1(string solutionType, int numberOfVariables = 7, int numberOfObjectives = 2);
	void evaluate(Solution *solution);

	~DTLZ1();
};

#endif /* __DTLZ1_H__ */
