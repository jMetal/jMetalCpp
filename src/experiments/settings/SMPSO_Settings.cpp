//  SMPSO_Settings.cpp
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


#include <SMPSO_Settings.h>


/**
 * Default constructor
 */
SMPSO_Settings::SMPSO_Settings () : Settings() {
} // SMPSO_Settings


/**
 * Destructor
 */
SMPSO_Settings::~SMPSO_Settings () {
  delete algorithm ;
  delete mutation  ; // Mutation operator
} // ~SMPSO_Settings


/**
 * Constructor
 */
SMPSO_Settings::SMPSO_Settings(string problemName) {

	problemName_ = problemName ;

  problem_ = ProblemFactory::getProblem((char *) problemName_.c_str());

  // Default settings
  swarmSize_                 = 100 ;
  maxIterations_             = 250 ;
  archiveSize_               = 100 ;
  mutationDistributionIndex_ = 20.0 ;
  mutationProbability_       = 1.0/problem_->getNumberOfVariables() ;

} // SMPSO_Settings


/**
 * Configure method
 */
Algorithm * SMPSO_Settings::configure() {

	algorithm = new SMPSO(problem_);
  algorithm->setInputParameter("swarmSize", &swarmSize_);
  algorithm->setInputParameter("maxIterations", &maxIterations_);
  algorithm->setInputParameter("archiveSize", &archiveSize_);

	map<string, void *> parameters;

  double mutationProbability = mutationProbability_;
  double mutationDistributionIndex = mutationDistributionIndex_;
  parameters["probability"] = &mutationProbability;
  parameters["distributionIndex"] = &mutationDistributionIndex;
  mutation = new PolynomialMutation(parameters);

	// Add the operators to the algorithm
	algorithm->addOperator("mutation",mutation);

	cout << "SMPSO algorithm initialized." << endl;

	return algorithm ;

} // configure

