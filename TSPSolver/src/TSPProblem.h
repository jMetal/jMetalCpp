/*
 * TSPProblem.h
 *
 *  Created on: 26 Jan 2019
 *      Author: Emad Alharbi
 */

#ifndef TSPPROBLEM_H_
#define TSPPROBLEM_H_
#include <JMetalInc/Problem.h>
#include <JMetalInc/BinarySolutionType.h>
#include <JMetalInc/RealSolutionType.h>
#include <JMetalInc/IntSolutionType.h>
#include <JMetalInc/Solution.h>
#include <JMetalInc/BinaryRealSolutionType.h>
#include <JMetalInc/IntNoneRepeatedSolutionType.h>
struct CCdatagroup {   // for holding city coordinates
	//double x[1904712]; // one element larger because the city tour start from 1 so element 0 is ignored
	//double y[1904712]; // one element larger because the city tour start from 1 so element 0 is ignored

	double x[30]; // one element larger because the city tour start from 1 so element 0 is ignored
	double y[30]; // one element larger because the city tour start from 1 so element 0 is ignored

	//double x[5]; // one element larger because the city tour start from 1 so element 0 is ignored
	//double y[5]; // one element larger because the city tour start from 1 so element 0 is ignored
};
class TSPProblem : public Problem {
public:
	CCdatagroup *TSPDATA = new CCdatagroup();
	TSPProblem();
	virtual ~TSPProblem();
	void evaluate(Solution *solution);
};

#endif /* TSPPROBLEM_H_ */
