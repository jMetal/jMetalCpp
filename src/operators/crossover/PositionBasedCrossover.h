/*
 * PositionBasedCrossover.h
 *
 *  Created on: 12 Feb 2019
 *      Author: Emad Alharbi
 *      University of York,UK
 */

#ifndef SRC_OPERATORS_CROSSOVER_POSITIONBASEDCROSSOVER_H_
#define SRC_OPERATORS_CROSSOVER_POSITIONBASEDCROSSOVER_H_
#include "Crossover.h"
#include "Int.h"
#include "Solution.h"
#include <math.h>
class PositionBasedCrossover: public Crossover {
public:
	PositionBasedCrossover(map<string, void *> parameters);
	virtual ~PositionBasedCrossover();
	 void *execute(void *);
private:
  double crossoverProbability_;
	 Solution ** doCrossover(double probability,Solution * parent1, Solution * parent2);
	 Solution* CreateoffSpring(Solution* P1, Solution* P2);
};

#endif /* SRC_OPERATORS_CROSSOVER_POSITIONBASEDCROSSOVER_H_ */
