/*
 * InsertionMutation.cpp
 *
 *  Created on: 9 Feb 2019
 *      Author: Emad Alharbi
 *      University of York,UK
 */
#include "InsertionMutation.h"

InsertionMutation::InsertionMutation(map<string, void *> parameters)

	: Mutation(parameters) {
	  mutationProbability_ = 0.0 ;
	  if (parameters["probability"] != NULL)
	    mutationProbability_ = *(double *) parameters["probability"];
}

InsertionMutation::~InsertionMutation() {
	// TODO Auto-generated destructor stub
}

void * InsertionMutation::doMutation(double probability, Solution *solution) {

   for (int c=0; c<solution->getNumberOfVariables() ; ++c )
   if (PseudoRandom::randDouble() < probability) {

  int numberOfVariables = solution->getNumberOfVariables() ;
  Solution** temp = new Solution*[2];
  temp[0] = new Solution(solution);
  temp[1] = new Solution(solution);
  int RandomGen=PseudoRandom::randInt(0,solution->getProblem()->getNumberOfVariables()-1);
  int RandomPos=PseudoRandom::randInt(0,solution->getProblem()->getNumberOfVariables()-1);
while(RandomGen==RandomPos){
	 RandomGen=PseudoRandom::randInt(0,solution->getProblem()->getNumberOfVariables()-1);
	 RandomPos=PseudoRandom::randInt(0,solution->getProblem()->getNumberOfVariables()-1);
}

// shift the gens one position left
for(int i=RandomGen ; i < temp[0]->getProblem()->getNumberOfVariables(); ++i ){

if(i+1<temp[0]->getProblem()->getNumberOfVariables())
	temp[1]->getDecisionVariables()[i]->setValue(temp[0]->getDecisionVariables()[i+1]->getValue());




}
// replace the gen to the random position
solution->getDecisionVariables()[RandomPos]->setValue(temp[0]->getDecisionVariables()[RandomGen]->getValue());

// copy the gens from the shifted solution, when index less than random position, copy the values as it and once the index became larger than the random position, copy the gen at index i-1 from the shifted solution
for(int i=0 ; i < temp[0]->getProblem()->getNumberOfVariables(); ++i ){
	if(i<RandomPos)
	solution->getDecisionVariables()[i]->setValue(temp[1]->getDecisionVariables()[i]->getValue());
	if(i>RandomPos)
	solution->getDecisionVariables()[i]->setValue(temp[1]->getDecisionVariables()[i-1]->getValue());
}


	}
} // doMutation


/**
 * Executes the operation
 * @param object An object containing a solution
 * @return An object containing the mutated solution
 * @throws JMException
 */
void * InsertionMutation::execute(void *object) {
  Solution *solution = (Solution *)object;
  // TODO: VALID_TYPES?

  doMutation(mutationProbability_, solution)  ;

  return solution;
} // exe
