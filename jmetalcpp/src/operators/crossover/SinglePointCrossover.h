/**
  * @file SinglePointCrossover.h
  * @author Antonio J. Nebro
  * @date 13 December 2011
**/

#ifndef __SPX_CROSSOVER__
#define __SPX_CROSSOVER__

#include <Crossover.h>
//#include <PseudoRandom.h>
#include <Binary.h>
#include <Solution.h>
#include <math.h>

/**
 * This class allows to apply a SBX crossover operator using two parent
 * solutions.
**/
class SinglePointCrossover : public Crossover {

public:
	SinglePointCrossover(map<string, void *> parameters);
	void *execute(void *);

private:
	double crossoverProbability_;
  Solution ** doCrossover(double probability,
  		Solution * parent1, Solution * parent2);
};

#endif
