#ifndef __SIGA_RULE_METAL_H__
#define __SIGA_RULE_METAL_H__

#include <Problem.h>
#include <math.h>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>
#include <functional>

class SIGARuleMetal : public Problem
{
public:
	SIGARuleMetal(std::function<void(Solution*)> callback, string solutionType, int numberOfVariables, int numberOfObjectives);
	void evaluate(Solution *solution);

	virtual ~SIGARuleMetal();
private:
	std::function<void(Solution*)> callback_;
};

#endif /* __DTLZ1_H__ */
