/**
  * @file BitFlipMutation.cpp
  * @author Antonio J. Nebro
  * @date 13 December 2011
**/


#include <BitFlipMutation.h>

/**
 * Constructor
 * Creates a new instance of the polynomial mutation operator
 */
BitFlipMutation::BitFlipMutation(map<string, void *> parameters)
: Mutation(parameters) {
	mutationProbability_ = 0.0 ;
	if (parameters["probability"] != NULL)
		mutationProbability_ = *(double *) parameters["probability"];
} // BitFlipMutation


/**
 * Perform the mutation operation
 * @param probability Mutation probability
 * @param solution The solution to mutate
 */
void * BitFlipMutation::doMutation(double probability, Solution *solution) {
  Binary * variable = (Binary *)(solution->getDecisionVariables()[0]) ;

	vector<bool>::iterator it;
	string str = "" ;
  for (int i = 0; i < variable->getNumberOfBits() ; i++)
		if (PseudoRandom::randDouble() <= mutationProbability_)
      variable->flip(i) ;
} // doMutation


/**
 * Executes the operation
 * @param object An object containing a solution
 * @return An object containing the mutated solution
 * @throws JMException
 */
void * BitFlipMutation::execute(void *object) {
	Solution *solution = (Solution *)object;
	// TODO: VALID_TYPES?

	doMutation(mutationProbability_, solution)  ;

	return solution;
} // execute
