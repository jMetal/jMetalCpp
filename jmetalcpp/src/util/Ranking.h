/**
 * @file Ranking.cpp
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 01 December 2011
 */

#ifndef __RANKING__
#define __RANKING__

#include <SolutionSet.h>
#include <Solution.h>
#include <DominanceComparator.h>
#include <OverallConstraintViolationComparator.h>
#include <vector>

/**
 * This class implements some facilities for ranking solutions.
 * Given a <code>SolutionSet</code> object, their solutions are ranked
 * according to scheme proposed in NSGA-II; as a result, a set of subsets
 * are obtained. The subsets are numbered starting from 0 (in NSGA-II, the
 * numbering starts from 1); thus, subset 0 contains the non-dominated
 * solutions, subset 1 contains the non-dominated solutions after removing those
 * belonging to subset 0, and so on.
 */
class Ranking {

private:
	SolutionSet * solutionSet_;
  SolutionSet ** ranking_;
  int numberOfSubfronts_;
  DominanceComparator * dominance_;
  OverallConstraintViolationComparator * constraint_;

public:
  Ranking (SolutionSet * solutionSet);
  ~Ranking();
  SolutionSet * getSubfront(int rank);
  int getNumberOfSubfronts();

};

#endif
