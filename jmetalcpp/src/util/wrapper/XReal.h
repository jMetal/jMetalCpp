/**
  * @file XReal.h
  * @author Esteban López
  * @date 30 November 2011
**/

#ifndef XREAL_H_
#define XREAL_H_

#include <Solution.h>
#include <BinarySolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <ArrayReal.h>


/**
 * This class allows to apply a SBX crossover operator using two parent
 * solutions.
**/
class XReal {

public:
	XReal();
	XReal(Solution * solution);
	double getValue(int index);
	void setValue(int index, double value);
	double getLowerBound(int index);
	double getUpperBound(int index);
	int getNumberOfDecisionVariables();
	int size();

private:
	Solution * solution_;
	SolutionType * type_;
	//TODO: Intentar hacer esto de otra manera:
	RealSolutionType * realSolutionType;
	BinarySolutionType * binarySolutionType;
	ArrayRealSolutionType * arrayRealSolutionType;

};

#endif /* XREAL_H_ */
