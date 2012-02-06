/*
 * @file NSGAII.h
 * @author Esteban López
 * @date 24 November 2011
 */

#ifndef __NSGAII__
#define __NSGAII__

#include <Algorithm.h>
#include <Problem.h>
#include <SolutionSet.h>
#include <Distance.h>
#include <Ranking.h>
#include <CrowdingComparator.h>
//#include <QualityIndicator.h>

/**
  * @class NSGAII
  * @brief This class implements the NSGA-II algorithm
**/

class NSGAII : public Algorithm {

private:
  int populationSize_;
  int maxEvaluations_;
  //QualityIndicator *indicators_;

public:
  NSGAII(Problem * problem);
  SolutionSet * execute();

};


#endif /* __NSGAII__ */
