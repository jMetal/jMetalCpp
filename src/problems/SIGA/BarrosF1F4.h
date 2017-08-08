#ifndef __BARROS_F1_F4_H__
#define __BARROS_F1_F4_H__

#include <Problem.h>
#include <math.h>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>
#include <functional>

class BarrosF1F4 : public Problem
{
public:
	BarrosF1F4(string solutionType, int numberOfVariables = 2, int numberOfObjectives = 2);
	void evaluate(Solution *solution);
	virtual ~BarrosF1F4();
};

#endif /* __BARROS_F1_F4_H__ */
