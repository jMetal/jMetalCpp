/*
 * OXCrossover.cpp
 *
 *  Created on: 14 Feb 2019
 *      Author: Emad Alharbi
 */

#include "OXCrossover.h"

OXCrossover::OXCrossover (map<string, void *> parameters)
: Crossover(parameters) {
	// TODO Auto-generated constructor stub
	 crossoverProbability_ = 0.0 ;
	  //TODO: crossoverProbability_ = NULL;
	  if (parameters["probability"] != NULL)
	    crossoverProbability_ = *(double *)parameters["probability"];

}
Solution ** OXCrossover::doCrossover(double probability,Solution *parent1, Solution *parent2) {
	 Solution** offSpring = new Solution*[2];

	  offSpring[0] = new Solution(parent1);
	  offSpring[1] = new Solution(parent2);

	  if (PseudoRandom::randDouble() < probability){

	  int SubStringFrom=PseudoRandom::randInt(0,parent1->getProblem()->getNumberOfVariables());
	  int SubStringTo=PseudoRandom::randInt(0,parent1->getProblem()->getNumberOfVariables());

	  while(SubStringFrom == SubStringTo ||  SubStringTo < SubStringFrom){ // should not be same

		  SubStringFrom=PseudoRandom::randInt(0,parent1->getProblem()->getNumberOfVariables());
		  SubStringTo=PseudoRandom::randInt(0,parent1->getProblem()->getNumberOfVariables());

	  }

	int indexOfCurrentGenToChange=0;
	if(indexOfCurrentGenToChange==SubStringFrom)
		indexOfCurrentGenToChange=SubStringTo;

	for(int i=0 ; i < parent2->getProblem()->getNumberOfVariables(); ++i ){

			bool IsInTheSubStringOfParent1=false;
			for(int c=SubStringFrom ; c < SubStringTo; ++c ){
	if(parent2->getDecisionVariables()[i]->getValue() == parent1->getDecisionVariables()[c]->getValue() )
		IsInTheSubStringOfParent1=true;
			}
			if(IsInTheSubStringOfParent1==false){

				offSpring[0]->getDecisionVariables()[indexOfCurrentGenToChange]->setValue(parent2->getDecisionVariables()[i]->getValue());
				indexOfCurrentGenToChange++;
			}
			if(indexOfCurrentGenToChange==SubStringFrom)
				indexOfCurrentGenToChange=SubStringTo;
	}

	// now offSpring2

	 SubStringFrom=PseudoRandom::randInt(0,parent2->getProblem()->getNumberOfVariables());
	   SubStringTo=PseudoRandom::randInt(0,parent2->getProblem()->getNumberOfVariables());
	  while(SubStringFrom == SubStringTo ||  SubStringTo < SubStringFrom){ // should not be same
		  SubStringFrom=PseudoRandom::randInt(0,parent2->getProblem()->getNumberOfVariables());
		  SubStringTo=PseudoRandom::randInt(0,parent2->getProblem()->getNumberOfVariables());
	  }

	    indexOfCurrentGenToChange=0;
	  if(indexOfCurrentGenToChange==SubStringFrom){
	  	indexOfCurrentGenToChange=SubStringTo;
	  }
	for(int i=0 ; i < parent1->getProblem()->getNumberOfVariables(); ++i ){

			bool IsInTheSubStringOfParent2=false;
			for(int c=SubStringFrom ; c < SubStringTo; ++c ){
	if(parent1->getDecisionVariables()[i]->getValue() == parent2->getDecisionVariables()[c]->getValue() )
		IsInTheSubStringOfParent2=true;
			}
			if(IsInTheSubStringOfParent2==false){

				offSpring[1]->getDecisionVariables()[indexOfCurrentGenToChange]->setValue(parent1->getDecisionVariables()[i]->getValue());
				indexOfCurrentGenToChange++;
			}
			if(indexOfCurrentGenToChange==SubStringFrom)
			  	indexOfCurrentGenToChange=SubStringTo;

	}
	  }
	  return offSpring;
}
void * OXCrossover::execute(void *object) {
  Solution ** parents = (Solution **) object;
  // TODO: Comprobar la longitud de parents
  // TODO: Chequear el tipo de parents

  Solution ** offSpring = (Solution **)doCrossover(crossoverProbability_, parents[0], parents[1]);

  return offSpring;
}
OXCrossover::~OXCrossover() {
	// TODO Auto-generated destructor stub
}

