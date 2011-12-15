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

	cout << "bitflipmutation -> prob: " << mutationProbability_ << endl ;
} // BitFlipMutation


/**
 * Perform the mutation operation
 * @param probability Mutation probability
 * @param solution The solution to mutate
 */
void * BitFlipMutation::doMutation(double probability, Solution *solution) {
  int numberOfVariables = solution->getNumberOfVariables() ;

  for (int i = 0 ; i < numberOfVariables ; i++) {
  	Binary * variable = (Binary *)(solution->getDecisionVariables()[i]) ;
    for (int j = 0; j < variable->getNumberOfBits() ; j++)
		  if (PseudoRandom::randDouble() <= mutationProbability_)
        variable->flip(j) ;
  }
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
