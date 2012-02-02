/*
 * AdaptiveGridArchive.h
 *
 *  Created on: 24/01/2012
 *      Author: Cristian
 */

#ifndef ADAPTIVEGRIDARCHIVE_H_
#define ADAPTIVEGRIDARCHIVE_H_

#include <DominanceComparator.h>
#include <Comparator.h>
#include <AdaptiveGrid.h>
#include <Archive.h>
#include <iostream.h>


/**
 * This class implements an archive based on an adaptive grid used in PAES
 */

class AdaptiveGridArchive : public Archive {

private:
	AdaptiveGrid * grid_;
	int maxSize_;
	Comparator * dominance_;

public:
	AdaptiveGridArchive(int maxSize,int bisections, int objectives);
	bool add(Solution * solution, int eval);
	AdaptiveGrid * getGrid();
};


#endif /* ADAPTIVEGRIDARCHIVE_H_ */
