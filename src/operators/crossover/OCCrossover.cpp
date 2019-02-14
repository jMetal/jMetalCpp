/*
 * OCCrossover.cpp
 *
 *  Created on: 14 Feb 2019
 *      Author: Emad Alharbi
 */

#include "OCCrossover.h"

OCCrossover::OCCrossover (map<string, void *> parameters)
: Crossover(parameters) {
	// TODO Auto-generated constructor stub
	 crossoverProbability_ = 0.0 ;
	  //TODO: crossoverProbability_ = NULL;
	  if (parameters["probability"] != NULL)
	    crossoverProbability_ = *(double *)parameters["probability"];

}

OCCrossover::~OCCrossover() {
	// TODO Auto-generated destructor stub
}

