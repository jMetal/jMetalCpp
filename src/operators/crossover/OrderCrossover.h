/*
 * OrderCrossover.h
 *
 *  Created on: 9 Feb 2019
 *      Author: Emad Alharbi
 */

#ifndef SRC_OPERATORS_CROSSOVER_ORDERCROSSOVER_H_
#define SRC_OPERATORS_CROSSOVER_ORDERCROSSOVER_H_
#include <Crossover.h>
#include <Int.h>
#include <Solution.h>
#include <math.h>
class OrderCrossover : public Crossover {
public:
	OrderCrossover(map<string, void *> parameters);
	 void *execute(void *);

private:
	 double crossoverProbability_;
	 Solution ** doCrossover(double probability,Solution * parent1, Solution * parent2);
	virtual ~OrderCrossover();
};

#endif /* SRC_OPERATORS_CROSSOVER_ORDERCROSSOVER_H_ */
