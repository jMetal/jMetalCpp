/*
 * OCCrossover.h
 *
 *  Created on: 14 Feb 2019
 *      Author: Emad Alharbi
 */

#ifndef SRC_OPERATORS_CROSSOVER_OCCROSSOVER_H_
#define SRC_OPERATORS_CROSSOVER_OCCROSSOVER_H_
#include <Crossover.h>
#include <Solution.h>
#include <Int.h>
#include <math.h>
class OCCrossover: public Crossover {
public:
	OCCrossover(map<string, void *> parameters);
	virtual ~OCCrossover();
	void *execute(void *);
private:
	 double crossoverProbability_;
		 Solution ** doCrossover(double probability,Solution * parent1, Solution * parent2);
};

#endif /* SRC_OPERATORS_CROSSOVER_OCCROSSOVER_H_ */
