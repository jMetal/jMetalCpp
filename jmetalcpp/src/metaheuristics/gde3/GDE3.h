/*
 * @file GDE3.h
 * @author Esteban López
 * @date 16 January 2012
 */

#ifndef __GDE3__
#define __GDE3__

#include <Algorithm.h>
#include <Problem.h>
#include <SolutionSet.h>
#include <Distance.h>
#include <Ranking.h>
#include <CrowdingComparator.h>

/**
  * @class GDE3
  * @brief This class implements the GDE3 algorithm.
**/

class GDE3 : public Algorithm {
private:
  int populationSize_;
  int maxEvaluations_;
  //QualityIndicator *indicators_;
  // Problem *problem_; // MODIFIED BY AJNEBRO
public:
  GDE3(Problem * problem);
  SolutionSet * execute();
};


#endif /* __GDE3__ */
