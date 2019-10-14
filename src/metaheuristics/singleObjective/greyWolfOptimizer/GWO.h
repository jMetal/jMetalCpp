//  GWO.h
//
//  Author:
//       Ahmad Dajani <eng.adajani@gmail.com>
//
//  Copyright (c) 2019 Ahmad Dajani
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

#ifndef __GWO__
#define __GWO__

#include <Algorithm.h>
#include <BestSolutionSelection.h>
#include <ObjectiveComparator.h>
#include <Problem.h>
#include <SolutionSet.h>
#include <XReal.h>
#include <PseudoRandom.h>
#include <math.h>
#include <string>

/**
 * Class implementing a single-objective GWO algorithm
 */

class GWO : public Algorithm {

private:
	const unsigned int defaultSearchAgentsCount_;
	const unsigned int defaultMaxIterations_;
	
	unsigned int searchAgentsCount_;
	unsigned int maxIterations_;

	Solution *alphaPosition_;
	double alphaScore_;

	Solution *betaPosition_;
	double betaScore_;

	Solution *deltaPosition_;
	double deltaScore_;

	double *convergenceCurve_;
  
	SolutionSet *positions_;

	void initPopulation();
	void calculateFitness();
	void adjustBoundries(int agentIndex);
	void updateWolves(double a);
	void initParams();

public:
	GWO(Problem *problem);
	~GWO();
	SolutionSet *execute();
	const double *getConvergenceCurve();
};

#endif /* __GWO__ */
