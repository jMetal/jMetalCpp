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

