//  MFO.h
//
//  Author:
//       Ahmad Dajani <eng.adajani@gmail.com>
//
//  Copyright (c) 2020 Ahmad Dajani
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __MFO__
#define __MFO__

#include <Algorithm.h>
#include <ObjectiveComparator.h>
#include <Problem.h>
#include <SolutionSet.h>
#include <XReal.h>
#include <PseudoRandom.h>
#include <math.h>
#include <string>

/**
 * Class implementing a single-objective MFO algorithm
 */

class MFO : public Algorithm {

private:
	const unsigned int defaultSearchAgentsCount_;
	const unsigned int defaultMaxIterations_;

	unsigned int searchAgentsCount_;
	unsigned int maxIterations_;

	Comparator *comparator;
	SolutionSet *positions_;
	SolutionSet *previousPositions_;
	SolutionSet *bestFlames_;
	SolutionSet *doublePopulation_;
	double *convergenceCurve_;

	void initPopulation();
	void initParams();
	void adjustBoundries(int agentIndex);
	void calculateFitness();
	void updatePosition(double a, int FlameNo);
public:
	MFO(Problem *problem);
	~MFO();
	SolutionSet *execute();
	const double *getConvergenceCurve();
};

#endif /* __MFO__ */
