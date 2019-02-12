/*
 * OrderCrossover.h
 *
 *  Created on: 9 Feb 2019
 *      Author: Emad Alharbi
 */

#ifndef SRC_OPERATORS_CROSSOVER_ORDERCROSSOVER_H_
#define SRC_OPERATORS_CROSSOVER_ORDERCROSSOVER_H_
#include <JMetalInc/Crossover.h>
#include <JMetalInc/Int.h>
#include <JMetalInc/Solution.h>
#include <math.h>
class OrderCrossover : public Crossover {
public:
	OrderCrossover(map<string, void *> parameters);
	 void *execute(void *);

private:
	 Solution ** doCrossover(double probability,Solution * parent1, Solution * parent2);
	virtual ~OrderCrossover();
};

#endif /* SRC_OPERATORS_CROSSOVER_ORDERCROSSOVER_H_ */
