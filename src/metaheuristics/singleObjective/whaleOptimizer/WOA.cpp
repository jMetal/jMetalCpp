//  WOA.cpp
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

#include <WOA.h>
#define _USE_MATH_DEFINES
#include <math.h>

/**
 * Class implementing a single-objective WOA algorithm
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
WOA::WOA(Problem *problem) : Algorithm(problem), 
                             defaultSearchAgentsCount_(40),
                             defaultMaxIterations_(500) {
	// Init. algorithm parameters
	initParams();

	// Init. member variables
	leaderPos_ = NULL;
	leaderScore_ = std::numeric_limits<double>::max();
	convergenceCurve_ = new double[maxIterations_];

	// Init. population
	initPopulation();
} // WOA


/**
 * delete all objects in the algorithm
 */
WOA::~WOA() {
	delete []convergenceCurve_;
	delete positions_;
} // deleteParams


/**
 * Initialize all parameter of the algorithm
 */
void WOA::initParams() {
	searchAgentsCount_ = *(unsigned int *) getInputParameter("searchAgentsCount", (void *)&defaultSearchAgentsCount_);
	maxIterations_ = *(unsigned int *) getInputParameter("maxIterations", (void *)&defaultMaxIterations_);
} // initParams


/**
 * Create the initial solutionSet
 */
void WOA::initPopulation() {
	positions_ = new SolutionSet(searchAgentsCount_);

	for(int agentIndex=0; agentIndex<searchAgentsCount_; agentIndex++) {
		Solution *solution = new Solution(problem_);
		XReal *solutionVariables = new XReal(solution);
		for(int variable=0; variable<solutionVariables->size(); variable++) {
			double value = problem_->getLowerLimit(variable) + 
			               (problem_->getUpperLimit(variable) - 
			               problem_->getLowerLimit(variable)) *
			               PseudoRandom::randDouble(0.0, 1.0);
			solutionVariables->setValue(variable, value);
		} //for variable
		positions_->add(solution);
		delete solutionVariables;
	} //for agentIndex
} // initPopulation


/**
 * Get convergence curve
 */
const double * WOA::getConvergenceCurve() {
	return convergenceCurve_;
} // getConvergenceCurve


/**
 * Get leader score
 */
const double WOA::getLeaderScore() {
	return leaderScore_;
} // getLeaderScore


/**
 * Adjust position boundries
 */
void WOA::adjustBoundries(int agentIndex) {
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
void WOA::calculateFitness() {
	for(int agentIndex=0; agentIndex<searchAgentsCount_; agentIndex++) {
		// Return back the search agents that go beyond the boundaries of the search space
		adjustBoundries(agentIndex);

		//Calculate objective function for each search agent
		Solution *fitness = new Solution(positions_->get(agentIndex));
		problem_->evaluate(fitness);
		double fitnessValue = fitness->getObjective(0);

		// Update the leader
		// Note: < for minimization problem
		//       > for maximization problem
		if(fitnessValue < leaderScore_) {
			// Update alpha
			leaderScore_ = fitnessValue;
			leaderPos_ = positions_->get(agentIndex);
		}
		delete fitness;
	}
} //calculateFitness


/**
 * Update the Position of search agents 
 */
void WOA::updatePosition(double a, double a2) {
	for(int agentIndex=0; agentIndex<searchAgentsCount_; agentIndex++) {
		double r1 = PseudoRandom::randDouble(0.0, 1.0);
		double r2 = PseudoRandom::randDouble(0.0, 1.0);
		double A = 2.0 * a * r1 - a;                          // Eq. (2.3) in the paper
		double C = 2.0 * r2;                                  // Eq. (2.4) in the paper
		double b = 1.0;                                       // parameters in Eq. (2.5)
		double l = (a2 - 1.0) * 
		           PseudoRandom::randDouble(0.0, 1.0) + 1.0;  // parameters in Eq. (2.5)
		double p = PseudoRandom::randDouble(0.0, 1.0);        // p in Eq. (2.6)

		XReal *solutionVariables = new XReal(positions_->get(agentIndex));
		for(int variable=0; variable<solutionVariables->size(); variable++) {
			if(p < 0.5) {
				if(fabs(A) >= 1.0) {
					int randomLeaderIndex = PseudoRandom::randInt(0, searchAgentsCount_ - 1);
					XReal *randomPosition = new XReal(positions_->get(randomLeaderIndex));
					double D_X_rand = fabs(C * randomPosition->getValue(variable) - 
					                       solutionVariables->getValue(variable) );             // Eq. (2.7)   
					solutionVariables->setValue(variable, randomPosition->getValue(variable) -
					                                      A * D_X_rand);                        //% Eq. (2.8)
					delete randomPosition;
				} else { // fabs(A) < 1
					XReal *leaderPosition = new XReal(leaderPos_);
					double D_Leader = fabs(C * leaderPosition->getValue(variable) - 
					                       solutionVariables->getValue(variable));              // Eq. (2.1)
					solutionVariables->setValue(variable, leaderPosition->getValue(variable) -
					                                      A * D_Leader);                        // Eq. (2.2)
					delete leaderPosition;
				}
			} else { // p >= 0.5
				XReal *leaderPosition = new XReal(leaderPos_);
				double distanceToLeader = fabs(leaderPosition->getValue(variable) - 
					                           solutionVariables->getValue(variable));
				solutionVariables->setValue(variable, distanceToLeader * 
				                                      exp(b * l) *
				                                      cos(l * 2.0 * M_PI) +
				                                      leaderPosition->getValue(variable)
				                           ); // Eq. (2.5)
				delete leaderPosition;
			}
		}
		delete solutionVariables;
	}
} // updatePosition


/**
 * Runs of the WOA algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet * WOA::execute() {
	for(int iteration=0; iteration<maxIterations_; iteration++) {
		calculateFitness();

		// a decreases linearly fron 2 to 0 in Eq. (2.3)
		double a = 2.0 - (double)iteration * ( 2.0 / maxIterations_);

		// a2 linearly dicreases from -1 to -2 to calculate t in Eq. (3.12)
		double a2 = -1.0 + (double)iteration * ( -1.0 / maxIterations_);

		updatePosition(a, a2);

		convergenceCurve_[iteration] = leaderScore_;
	}

	Solution *fitness = new Solution(leaderPos_);
	problem_->evaluate(fitness);
	leaderScore_ = fitness->getObjective(0);

	// Return leader vector
	SolutionSet *resultPopulation = new SolutionSet(1);
	resultPopulation->add(fitness);

	return resultPopulation;
} // execute
