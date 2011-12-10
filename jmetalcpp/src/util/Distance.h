/**
 * @file Distance.cpp
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 01 December 2011
 */

#ifndef __DISTANCE__
#define __DISTANCE__

#include <SolutionSet.h>
#include <Solution.h>
#include <float.h>
#include <ObjectiveComparator.h>
#include <math.h>

using namespace std;


/**
 * This class implements some utilities for calculating distances
 */
class Distance {

public:
	Distance();
	double ** distanceMatrix(SolutionSet * solutionSet);
	double distanceToSolutionSetInObjectiveSpace(Solution * solution,
      																				 SolutionSet * solutionSet);
	double distanceToSolutionSetInSolutionSpace(Solution * solution,
	 		                                  			SolutionSet * solutionSet);
	double distanceBetweenSolutions(Solution * solutionI, Solution * solutionJ);
	double distanceBetweenObjectives(Solution * solutionI, Solution * solutionJ);
	void crowdingDistanceAssignment(SolutionSet * solutionSet, int nObjs);

};


#endif
