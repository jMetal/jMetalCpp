//  AdaptiveGrid.h
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

#ifndef __ADAPTIVEGRID__
#define __ADAPTIVEGRID__

#include <SolutionSet.h>
#include <Solution.h>
#include <float.h>
#include <ObjectiveComparator.h>
#include <math.h>
#include <limits.h>
#include <PseudoRandom.h>

/**
 * This class implements some utilities for calculating distances
 */
class AdaptiveGrid {

private:

	 /**
	   * Number of bi-divisions of the objective space
	   */
	int bisections_;

	/**
	 * Objectives of the problem
	 */
	int objectives_;

	/**
	 * Number of solutions into a specific hypercube in the adaptative grid
	 */
	int * hypercubes_;

	int sizehypercubes_;
	/**
	 *
	 * Grid lower bounds
	 */
	double * lowerLimits_;

	/**
	 * Grid upper bounds
	 */
	double * upperLimits_;

	/**
	 * Size of hypercube for each dimension
	 */
	double * divisionSize_;

	/**
	 * Hypercube with maximum number of solutions
	 */
	int mostPopulated_;

	/**
	 * Indicates when an hypercube has solutions
	 */
	int * occupied_;

	int occupiedsize_;

	void updateLimits(SolutionSet * solutionSet);

public:
	AdaptiveGrid(int bisections, int objetives);

	void addSolutionSet(SolutionSet * solutionSet);
	void updateGrid(SolutionSet * solutionSet);
	void updateGrid(Solution * solution, SolutionSet * solutionSet, int eval);
	int location(Solution * solution);
	int getMostPopulated();
	int getLocationDensity(int location);
	void removeSolution(int location);
	void addSolution(int location);
	int getBisections();
	string toString();
	int rouletteWheel();
	int calculateOccupied();
	int occupiedHypercubes();
	int randomOccupiedHypercube();
};


#endif

