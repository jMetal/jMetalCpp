/*
 * paes.h
 *
 *  Created on: 25/01/2012
 *      Author: Cristian
 */

#ifndef PAES_H_
#define PAES_H_

#include <Algorithm.h>
#include <Problem.h>
#include <SolutionSet.h>
#include <DominanceComparator.h>
#include <AdaptiveGridArchive.h>

class paes : public Algorithm {

public:
	paes(Problem * problem);
	Solution * test(Solution * solution,Solution * mutatedSolution,
                      AdaptiveGridArchive * archive);
    SolutionSet * execute();
};



#endif /* PAES_H_ */
