//  DE_Settings.cpp
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

#include <DE_Settings.h>

/**
 * Default constructor
 */
DE_Settings::DE_Settings () : Settings() {
} // DE_Settings

/**
 * Destructor
 */
DE_Settings::~DE_Settings () {
  delete algorithm ;
  delete crossover ; // Crossover operator
  delete selection ; // Selection operator
} // ~DE_Settings

/**
 * Constructor
 */
DE_Settings::DE_Settings(string problemName) {
	problemName_ = problemName ;

  problem_ = ProblemFactory::getProblem((char *) problemName_.c_str());

  // Algorithm parameters
  populationSize_    = 100;
  maxEvaluations_    = 25000;
  crParameter_        = 0.5;
  fParameter_         = 0.5;
  deVariantParameter_ = "rand/1/bin";

} // DE_Settings

/**
 * Configure method
 */
Algorithm * DE_Settings::configure() {

	algorithm = new DE(problem_);
  algorithm->setInputParameter("populationSize",&populationSize_);
  algorithm->setInputParameter("maxEvaluations",&maxEvaluations_);

	map<string, void *> parameters;

	// Crossover operator
  double crParameter = crParameter_;
  double fParameter  = fParameter_;
  parameters["CR"] =  &crParameter;
  parameters["F"] = &fParameter;
  string deVariantParameter = deVariantParameter_;
  parameters["DE_VARIANT"] = &deVariantParameter;
  crossover = new DifferentialEvolutionCrossover(parameters);

  // Selection operator
  parameters.clear();
  selection = new DifferentialEvolutionSelection(parameters) ;

	// Add the operators to the algorithm
	algorithm->addOperator("crossover",crossover);
	algorithm->addOperator("selection",selection);

	cout << "DE algorithm initialized." << endl;

	return algorithm ;
} // configure

