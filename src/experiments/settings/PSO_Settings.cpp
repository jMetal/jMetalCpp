//  PSO_Settings.cpp
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//
//  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
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


#include <PSO_Settings.h>


/**
 * Default constructor
 */
PSO_Settings::PSO_Settings () : Settings() {
} // PSO_Settings


/**
 * Destructor
 */
PSO_Settings::~PSO_Settings () {
  delete algorithm ;
  delete mutation  ; // Mutation operator
} // ~PSO_Settings


/**
 * Constructor
 */
PSO_Settings::PSO_Settings(string problemName) {

	problemName_ = problemName ;

  problem_ = ProblemFactory::getProblem((char *) problemName_.c_str());

  // Default settings
  swarmSize_                 = 50 ;
  maxIterations_             = 5000 ;
  mutationDistributionIndex_ = 20.0 ;
  mutationProbability_       = 1.0/problem_->getNumberOfVariables() ;

} // PSO_Settings


/**
 * Configure method
 */
Algorithm * PSO_Settings::configure() {

	algorithm = new PSO(problem_);
  algorithm->setInputParameter("swarmSize", &swarmSize_);
  algorithm->setInputParameter("maxIterations", &maxIterations_);

	map<string, void *> parameters;

  // Mutation operator
  double mutationProbability = mutationProbability_;
  double mutationDistributionIndex = mutationDistributionIndex_;
  parameters["probability"] = &mutationProbability;
  parameters["distributionIndex"] = &mutationDistributionIndex;
  mutation = new PolynomialMutation(parameters);

	// Add the operators to the algorithm
	algorithm->addOperator("mutation",mutation);

	cout << "PSO algorithm initialized." << endl;

	return algorithm ;

} // configure

