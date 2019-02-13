/*
 * InversionMutation.cpp
 *
 *  Created on: 9 Feb 2019
 *      Author: Emad Alharbi
 *      University of York,UK
 */

#include "InversionMutation.h"

InversionMutation::InversionMutation(map<string, void *> parameters)
	: Mutation(parameters){
	  mutationProbability_ = 0.0 ;
	  if (parameters["probability"] != NULL)
	    mutationProbability_ = *(double *) parameters["probability"];

}

InversionMutation::~InversionMutation() {
	// TODO Auto-generated destructor stub
}
void * InversionMutation::doMutation(double probability, Solution *solution) {


  int numberOfVariables = solution->getNumberOfVariables() ;
  Solution** temp = new Solution*[1];
  temp[0] = new Solution(solution);

  int SubstringStartFrom=PseudoRandom::randInt(0,solution->getProblem()->getNumberOfVariables()-1); // select start point of sublist
  int SubstringTo=PseudoRandom::randInt(0,solution->getProblem()->getNumberOfVariables()-1);// select end point of sublist

while(SubstringStartFrom==SubstringTo || SubstringTo < SubstringStartFrom){
	SubstringStartFrom=PseudoRandom::randInt(0,solution->getProblem()->getNumberOfVariables()-1);
	SubstringTo=PseudoRandom::randInt(0,solution->getProblem()->getNumberOfVariables()-1);
}

if (PseudoRandom::randDouble() < probability) {
for(int i=SubstringStartFrom ; i < solution->getProblem()->getNumberOfVariables(); ++i ){ // do the inversion
	solution->getDecisionVariables()[i]->setValue(temp[0]->getDecisionVariables()[SubstringTo]->getValue());
	SubstringTo--;
	if(SubstringTo < SubstringStartFrom)
		break;
}
}
} // doMutation

void * InversionMutation::execute(void *object) {
  Solution *solution = (Solution *)object;
  // TODO: VALID_TYPES?

  doMutation(mutationProbability_, solution)  ;

  return solution;
}
