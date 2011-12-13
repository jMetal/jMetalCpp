/**
  * @file PolynomialMutation.h
  * @author Juan J. Durillo
  * @author Antonio J. Nebro
  * @author Esteban López
  * @date 01 December 2011
**/

#ifndef __POLYNOMIAL_MUTATION__
#define __POLYNOMIAL_MUTATION__

#include <Mutation.h>
#include <Solution.h>
#include <math.h>
#include <float.h>
#include <PseudoRandom.h>
#include <XReal.h>

/**
  * @class Mutation
  * @brief This class implements a polynomial mutation operator.
**/
class PolynomialMutation : public Mutation {

public:

	static const double ETA_M_DEFAULT_;
	static const double eta_m_;

	PolynomialMutation(map<string, void *> parameters);

	void * execute(void *);

private:
	double mutationProbability_;
	double distributionIndex_;

	void * doMutation(double probability, Solution * solution);
	// TODO: VALID_TYPES;

}; // PolynomialMutation

#endif
