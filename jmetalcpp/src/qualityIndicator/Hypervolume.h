/*
  * @file Hypervolume.h
  * @author Esteban López
  * @date 24 November 2011
 */

#ifndef __HYPERVOLUME__
#define __HYPERVOLUME__


/**
  * @class Hypervolume
  * @brief This class implements the hypervolume indicator
**/

class NSGAII : public Algorithm {
private:
  int populationSize_;
  int maxEvaluations_;
  QualityIndicator *indicators_;
  Problem *problem_;
public:
  NSGAII(Problem * problem);
  SolutionSet * execute();
};


#endif /* HYPERVOLUME__ */
