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
Solution ** OCCrossover::doCrossover(double probability,Solution *parent1, Solution *parent2) {

}
void * OCCrossover::execute(void *object) {
  Solution ** parents = (Solution **) object;
  // TODO: Comprobar la longitud de parents
  // TODO: Chequear el tipo de parents

  Solution ** offSpring = (Solution **)doCrossover(crossoverProbability_, parents[0], parents[1]);

  return offSpring;
}
OCCrossover::~OCCrossover() {
	// TODO Auto-generated destructor stub
}

