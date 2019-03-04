/*
 * PositionBasedCrossover.cpp
 *
 *  Created on: 12 Feb 2019
 *      Author: Emad Alharbi
 *      University of York,UK
 */

#include "PositionBasedCrossover.h"
#include <vector>
#include <algorithm>
PositionBasedCrossover::PositionBasedCrossover(map<string, void *> parameters)
: Crossover(parameters) {
  crossoverProbability_ = 0.0 ;
  //TODO: crossoverProbability_ = NULL;
  if (parameters["probability"] != NULL)
    crossoverProbability_ = *(double *)parameters["probability"];
	// TODO Auto-generated constructor stub

}
Solution ** PositionBasedCrossover::doCrossover(double probability,Solution *parent1, Solution *parent2) {

  Solution** offSpring = new Solution*[2];

  offSpring[0] = new Solution(parent1);
  offSpring[1] = new Solution(parent2);
  if (PseudoRandom::randDouble() < probability){
  offSpring[0] = CreateoffSpring(parent1,parent2);
  offSpring[1] = CreateoffSpring(parent2,parent1);
  }
  return offSpring;

}
Solution* PositionBasedCrossover::CreateoffSpring(Solution* P1, Solution* P2){

	Solution** offSpring = new Solution*[1];
	offSpring[0] = new Solution(P1);

	 std::vector<int> RandomPositionFromP1;

	  int NumberOfRandomGenes=PseudoRandom::randInt(0,P1->getProblem()->getNumberOfVariables());

	  for(int i=0 ; i< NumberOfRandomGenes ; ++i){

		  int RandomPosition=PseudoRandom::randInt(0,P1->getProblem()->getNumberOfVariables()-1);
		  while(std::find(RandomPositionFromP1.begin(), RandomPositionFromP1.end(), RandomPosition) != RandomPositionFromP1.end() ){
			  RandomPosition=PseudoRandom::randInt(0,P1->getProblem()->getNumberOfVariables()-1);
		  }
		  RandomPositionFromP1.push_back(RandomPosition);

	  }

	  std::vector<int> EmptyPositionInOff1;
	  for(int i=0 ; i < P2->getProblem()->getNumberOfVariables(); ++i ){
		  if(!(std::find(RandomPositionFromP1.begin(), RandomPositionFromP1.end(), i) != RandomPositionFromP1.end())){
			  EmptyPositionInOff1.push_back(i);


		  }
	  }

	  int IndexOfEmptyPositionInOff1=0;
	  for(int i=0 ; i < P2->getProblem()->getNumberOfVariables(); ++i ){
	bool Found=false;
		  for(int v=0; v < RandomPositionFromP1.size(); ++v){
			  if(P2->getDecisionVariables()[i]->getValue()==P1->getDecisionVariables()[RandomPositionFromP1[v]]->getValue()){
				  Found=true;

				  break;
			  }
		  }
		  if(Found==false){
			  offSpring[0]->getDecisionVariables()[EmptyPositionInOff1[IndexOfEmptyPositionInOff1]]->setValue(P2->getDecisionVariables()[i]->getValue());
			  IndexOfEmptyPositionInOff1++;
		  }
	  }
	  return offSpring[0];
}
PositionBasedCrossover::~PositionBasedCrossover() {
	// TODO Auto-generated destructor stub
}
void * PositionBasedCrossover::execute(void *object) {
  Solution ** parents = (Solution **) object;
  // TODO: Comprobar la longitud de parents
  // TODO: Chequear el tipo de parents

  Solution ** offSpring = (Solution **)doCrossover(crossoverProbability_, parents[0], parents[1]);

  return offSpring;
} //
