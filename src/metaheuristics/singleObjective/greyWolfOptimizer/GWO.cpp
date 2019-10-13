//  GWO.cpp
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

#include <GWO.h>


/**
 * Class implementing a single-objective GWO algorithm
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
GWO::GWO(Problem *problem) : Algorithm(problem), 
                             defaultSearchAgentsCount_(30),
                             defaultMaxIterations_(500) {
	//Init. algorithm parameters
	initParams();

	//Init. member varaibles
	alphaScore_ = std::numeric_limits<double>::max();
	betaScore_ = std::numeric_limits<double>::max();
	deltaScore_ = std::numeric_limits<double>::max();

	alphaPosition_ = NULL;
	betaPosition_ = NULL;
	deltaPosition_ = NULL;
	convergenceCurve_ = new double[maxIterations_];

	//Init. population
	initPopulation();
} // GWO


/**
 * Initialize all parameter of the algorithm
 */
void GWO::initParams() {
	searchAgentsCount_ = *(unsigned int *) getInputParameter("searchAgentsCount", (void *)&defaultSearchAgentsCount_);
	maxIterations_ = *(unsigned int *) getInputParameter("maxIterations", (void *)&defaultMaxIterations_);
} // initParams


/**
 * Create the initial solutionSet
 */
void GWO::initPopulation() {
	positions_ = new SolutionSet(searchAgentsCount_);

	for(int agentIndex=0; agentIndex<searchAgentsCount_; agentIndex++) {
		Solution *solution = new Solution(problem_);
		XReal *solutionVariables = new XReal(solution);
		for(int variable=0; variable<solutionVariables->size(); variable++) {
			double value = problem_->getLowerLimit(variable) + 
			               (problem_->getUpperLimit(variable) - problem_->getLowerLimit(variable)) *
			               PseudoRandom::randDouble(0.0, 1.0);
			solutionVariables->setValue(variable, value);
		}
		positions_->add(solution);
		delete solutionVariables;
	} //for
} // initPopulation


/**
 * Adjust wolf (solution) boundries
 */
void GWO::adjustBoundries(int agentIndex) {
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
void GWO::calculateFitness() {
	for(int agentIndex=0; agentIndex<searchAgentsCount_; agentIndex++) {
		adjustBoundries(agentIndex);

		Solution *fitness = new Solution(positions_->get(agentIndex));
		problem_->evaluate(fitness);
		double fitnessValue = fitness->getObjective(0);

		if( fitnessValue < alphaScore_ ) {
			alphaScore_ = fitnessValue; // Update alpha
			alphaPosition_ = positions_->get(agentIndex);
		}

		if( (fitnessValue > alphaScore_) && (fitnessValue < betaScore_) ) {
			betaScore_ = fitnessValue;  // Update beta
			betaPosition_ = positions_->get(agentIndex);
		}

		if( (fitnessValue > alphaScore_) && (fitnessValue > betaScore_) && (fitnessValue < deltaScore_) ) {
			deltaScore_ = fitnessValue; //Update delta
			deltaPosition_ = positions_->get(agentIndex);
		}
		delete fitness;
	}
} //calculateFitness


/**
 * Update the Position of search agents including omegas
 */
void GWO::updateWolves(double a) {
	XReal *alphaVariables = new XReal(alphaPosition_);
	XReal *betaVariables = new XReal(betaPosition_);
	XReal *deltaVariables = new XReal(deltaPosition_);

	for(int agentIndex=0; agentIndex<searchAgentsCount_; agentIndex++) {
		XReal *solutionVariables = new XReal(positions_->get(agentIndex));
		for(int variable=0; variable<solutionVariables->size(); variable++) {
			double r1 = PseudoRandom::randDouble(0.0, 1.0);
			double r2 = PseudoRandom::randDouble(0.0, 1.0);

			double A1 = 2.0 * a * r1 - a; //Equation (3.3)
			double C1 = 2.0 * r2;         //Equation (3.4)
			double D_alpha = fabs(C1 * alphaVariables->getValue(variable) - 
			                           solutionVariables->getValue(variable)); //Equation (3.5)-part 1
			double X1 = alphaVariables->getValue(variable) - A1 * D_alpha;     //Equation (3.6)-part 1

			r1 = PseudoRandom::randDouble(0.0, 1.0);
			r2 = PseudoRandom::randDouble(0.0, 1.0);

			double A2 = 2.0 * a * r1 - a; //Equation (3.3)
			double C2 = 2.0 * r2;         //Equation (3.4)
			double D_beta = fabs(C2 * betaVariables->getValue(variable) - 
			                          solutionVariables->getValue(variable)); //Equation (3.5)-part 2
			double X2 = betaVariables->getValue(variable) - A2 * D_beta;      //Equation (3.6)-part 2

			r1 = PseudoRandom::randDouble(0.0, 1.0);
			r2 = PseudoRandom::randDouble(0.0, 1.0);

			double A3 = 2.0 * a * r1 - a; //Equation (3.3)
			double C3 = 2.0 * r2;         //Equation (3.4)
			double D_delta = fabs(C3 * deltaVariables->getValue(variable) - 
			                           solutionVariables->getValue(variable)); //Equation (3.5)-part 3
			double X3 = deltaVariables->getValue(variable) - A3 * D_delta;     //Equation (3.5)-part 3

			solutionVariables->setValue(variable, (X1+X2+X3) / 3.0 );          //Equation (3.7)
		}
		delete solutionVariables;
	} //for

	delete alphaVariables;
	delete betaVariables;
	delete deltaVariables;
} //updateWolves


/**
 * delete all objects in the algorithm
 */
GWO::~GWO() {
	delete []convergenceCurve_;
	delete positions_;
} // deleteParams


/**
 * Get convergence curve
 */
const double * GWO::getConvergenceCurve() {
	return convergenceCurve_;
}


/**
 * Runs of the GWO algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet * GWO::execute() {
	for(int l=0; l<maxIterations_; l++) {
		calculateFitness();
		double a = 2.0 - (double)l * (2.0/maxIterations_);
		updateWolves(a);
		convergenceCurve_[l] = alphaScore_;
	}

	Solution *fitness = new Solution(alphaPosition_);
	problem_->evaluate(fitness);

	// Return alpha vector
	SolutionSet *resultPopulation = new SolutionSet(1);
	resultPopulation->add(fitness);

	return resultPopulation;
} // execute
