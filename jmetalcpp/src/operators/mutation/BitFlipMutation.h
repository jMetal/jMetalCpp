/**
  * @file BitFlipMutation.h
  * @author Antonio J. Nebro
  * @date 13 December 2011
**/

#ifndef __BITFLIP_MUTATION__
#define __BITFLIP_MUTATION__

#include <Mutation.h>
#include <Solution.h>
#include <math.h>
#include <float.h>
#include <PseudoRandom.h>
#include <Binary.h>

/**
  * @class Mutation
  * @brief This class implements a polynomial mutation operator.
**/
class BitFlipMutation : public Mutation {

public:
	BitFlipMutation(map<string, void *> parameters);

	void * execute(void *);
private:
	double mutationProbability_;
	// TODO: VALID_TYPES;
	void * doMutation(double probability, Solution * solution);

}; // BitFlipMutation

#endif
