//  AdaptiveGridArchive.h
//
//  Author:
//       Cristian Zambrano <cristian_uteq@hotmail.com>
//
//  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef ADAPTIVEGRIDARCHIVE_H_
#define ADAPTIVEGRIDARCHIVE_H_

#include <DominanceComparator.h>
#include <Comparator.h>
#include <AdaptiveGrid.h>
#include <Archive.h>
#include <iostream>

/**
 * This class implements an archive based on an adaptive grid used in PAES
 */

class AdaptiveGridArchive : public Archive {

private:
	/**
		 * Stores the adaptive grid
		 */
	AdaptiveGrid * grid_;

	/**
	 * Stores the maximum size of the archive
	 */
	int maxSize_;

	/**
	 * Stores a <code>Comparator</code> for dominance checking
	 */
	Comparator * dominance_;

public:
	AdaptiveGridArchive(int maxSize,int bisections, int objectives);
	bool add(Solution * solution, int eval);
	AdaptiveGrid * getGrid();
};

#endif /* ADAPTIVEGRIDARCHIVE_H_ */
