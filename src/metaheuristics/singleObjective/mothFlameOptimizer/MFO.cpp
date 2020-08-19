//  MFO.cpp
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

#include <MFO.h>
#define _USE_MATH_DEFINES
#include <math.h>

/**
 * Class implementing a single-objective MFO algorithm
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
MFO::MFO(Problem *problem) : Algorithm(problem), 
                             defaultSearchAgentsCount_(30),
                             defaultMaxIterations_(1000) {
	// Init. algorithm parameters
	initParams();

	// Init. member variables
	comparator = new ObjectiveComparator(0);
	convergenceCurve_ = new double[maxIterations_];
	positions_ = new SolutionSet(searchAgentsCount_);
	previousPositions_ = new SolutionSet(searchAgentsCount_);
	bestFlames_ = new SolutionSet(searchAgentsCount_);

	// Init. population
	initPopulation();
} // MFO


/**
 * delete all objects in the algorithm
 */
MFO::~MFO() {
	delete []convergenceCurve_;
	delete previousPositions_;
	delete positions_;
	delete bestFlames_;
	delete comparator;
} // deleteParams


/**
 * Initialize all parameter of the algorithm
 */
void MFO::initParams() {
	searchAgentsCount_ = *(unsigned int *) getInputParameter("searchAgentsCount", (void *)&defaultSearchAgentsCount_);
	maxIterations_ = *(unsigned int *) getInputParameter("maxIterations", (void *)&defaultMaxIterations_);
} // initParams


/**
 * Create the initial solutionSet
 */
void MFO::initPopulation() {
	for(int agentIndex=0; agentIndex<searchAgentsCount_; agentIndex++) {
		Solution *solution = new Solution(problem_);
		XReal *solutionVariables = new XReal(solution);
		for(int variable=0; variable<solutionVariables->size(); variable++) {
			double value = PseudoRandom::randDouble(problem_->getLowerLimit(variable),
			                                        problem_->getUpperLimit(variable));
			solutionVariables->setValue(variable, value);
		} //for variable
		positions_->add(solution);
		previousPositions_->add(new Solution(problem_));
		delete solutionVariables;
	} //for agentIndex
} // initPopulation


/**
 * Get convergence curve
 */
const double * MFO::getConvergenceCurve() {
	return convergenceCurve_;
} // getConvergenceCurve


/**
 * Adjust position boundries
 */
void MFO::adjustBoundries(int agentIndex) {
	XReal *agentWrapper = new XReal(positions_->get(agentIndex));
	for(int variable=0; variable<agentWrapper->size(); variable++) {
		double value = agentWrapper->getValue(variable);
		if(value < problem_->getLowerLimit(variable)) {
			agentWrapper->setValue(variable, problem_->getLowerLimit(variable));
		} else if(value > problem_->getUpperLimit(variable)) {
			agentWrapper->setValue(variable, problem_->getUpperLimit(variable));
		}
	}
	delete agentWrapper;
} //adjustBoundries


/**
 * Calculate fitness for each solution
 */
void MFO::calculateFitness() {
	double fitnessValue;
	for(int agentIndex=0; agentIndex<searchAgentsCount_; agentIndex++) {
		// Return back the search agents that go beyond the boundaries of the search space
		adjustBoundries(agentIndex);

		// Calculate the fitness of each moth
		Solution *fitness = new Solution(positions_->get(agentIndex));
		problem_->evaluate(fitness);
		fitnessValue = fitness->getObjective(0);
		positions_->get(agentIndex)->setObjective(0, fitnessValue);
		delete fitness;
	}
} //calculateFitness


void MFO::updatePosition(double a, int FlameNo) {
	const double b = 1.0;
	double distanceToFlame;
	double t;
	XReal *bestFlamesVariables;

	for(int agentIndex=0; agentIndex<searchAgentsCount_; agentIndex++) {
		XReal *positionVariables = new XReal(positions_->get(agentIndex));

		if(agentIndex <= FlameNo) {
			// Update the position of the moth with respect to its corresponsing flame
			bestFlamesVariables = new XReal(bestFlames_->get(agentIndex));
		} else {
			// Update the position of the moth with respect to its corresponsing flame
			bestFlamesVariables = new XReal(bestFlames_->get(FlameNo));
		}

		for(int variable=0; variable<positionVariables->size(); variable++) {
			// D in Eq. (3.13)
			distanceToFlame = fabs(bestFlamesVariables->getValue(variable) - 
								   positionVariables->getValue(variable));
			t =(a - 1.0) * PseudoRandom::randDouble(0.0, 1.0) + 1.0;

			positionVariables->setValue(variable, distanceToFlame * 
												  exp(b * t) * 
												  cos(t * 2.0 * M_PI) + 
												  bestFlamesVariables->getValue(variable));
		}

		delete positionVariables;
		delete bestFlamesVariables;
	}
}

/**
 * Runs of the MFO algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet * MFO::execute() {
	int FlameNo;
	double a;

	for(int iteration=0; iteration<maxIterations_; iteration++) {
		calculateFitness();

		if(iteration == 0) {
			for(int agentIndex=0; agentIndex<searchAgentsCount_; agentIndex++) {
				bestFlames_->add(new Solution(positions_->get(agentIndex)));
			}

			// Sort the first population of moths
			bestFlames_->sort(comparator);
		} else {
			// Sort the moths
			doublePopulation_ = previousPositions_->join(bestFlames_);
			doublePopulation_->sort(comparator);

			// Update the flames
			for(int agentIndex=0; agentIndex<searchAgentsCount_; agentIndex++) {
				bestFlames_->replace(agentIndex, new Solution(doublePopulation_->get(agentIndex)));
			}

			delete doublePopulation_;
		}

		// Update the position of best flame obtained so far
		for(int agentIndex=0; agentIndex<searchAgentsCount_; agentIndex++) {
			previousPositions_->replace(agentIndex, new Solution(positions_->get(agentIndex)));
		}

		// a linearly dicreases from -1 to -2 to calculate t in Eq. (3.12)
		a = -1.0 + (double)(iteration + 1) * (-1.0 / (double)maxIterations_);

		FlameNo = round((searchAgentsCount_ - 1) - (iteration + 1) *
						( (double)(searchAgentsCount_ - 1) / (double)maxIterations_));

		updatePosition(a, FlameNo);

		convergenceCurve_[iteration] = bestFlames_->get(0)->getObjective(0);
	}

	// Return best flame
	Solution *fitness = new Solution(bestFlames_->get(0));
	problem_->evaluate(fitness);

	SolutionSet *resultPopulation = new SolutionSet(1);
	resultPopulation->add(fitness);

	return resultPopulation;
} // execute
