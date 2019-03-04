/*
 * InversionMutation.h
 *
 *  Created on: 9 Feb 2019
 *      Author: Emad Alharbi
 */

#ifndef SRC_OPERATORS_MUTATION_INVERSIONMUTATION_H_
#define SRC_OPERATORS_MUTATION_INVERSIONMUTATION_H_
#include <JMetalInc/Mutation.h>
#include <JMetalInc/Solution.h>
#include <math.h>
#include <float.h>
#include <JMetalInc/PseudoRandom.h>
#include <JMetalInc/Int.h>
class InversionMutation : public Mutation{
public:
	InversionMutation();
	virtual ~InversionMutation();

	InversionMutation(map<string, void *> parameters);

	  void * execute(void *);
private:
  double mutationProbability_;
  // TODO: VALID_TYPES;
  void * doMutation(double probability, Solution * solution);
};

#endif /* SRC_OPERATORS_MUTATION_INVERSIONMUTATION_H_ */
