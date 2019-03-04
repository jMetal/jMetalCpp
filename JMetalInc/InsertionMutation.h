/*
 * InsertionMutation.h
 *
 *  Created on: 9 Feb 2019
 *      Author: Emad Alharbi
 */

#ifndef SRC_OPERATORS_MUTATION_INSERTIONMUTATION_H_
#define SRC_OPERATORS_MUTATION_INSERTIONMUTATION_H_

#include <JMetalInc/Mutation.h>
#include <JMetalInc/Solution.h>
#include <math.h>
#include <float.h>
#include <JMetalInc/PseudoRandom.h>
#include <JMetalInc/Int.h>
class InsertionMutation  : public Mutation{
public:
	InsertionMutation(map<string, void *> parameters);
	virtual ~InsertionMutation();
	 void * execute(void *);

private:
  double mutationProbability_;
  // TODO: VALID_TYPES;
  void * doMutation(double probability, Solution * solution);
};

#endif /* SRC_OPERATORS_MUTATION_INSERTIONMUTATION_H_ */
