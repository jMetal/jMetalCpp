/**
  * @file SBXCrossover.h
  * @author Juan J. Durillo
  * @author Antonio J. Nebro
  * @author Esteban López
  * @date 30 November 2011
**/

#ifndef __SBX_CROSSOVER__
#define __SBX_CROSSOVER__

#include <Crossover.h>
#include <XReal.h>
#include <Solution.h>
#include <math.h>

/**
 * This class allows to apply a SBX crossover operator using two parent
 * solutions.
**/
class SBXCrossover : public Crossover {

public:
  SBXCrossover(map<string, void *> parameters);
  ~SBXCrossover();
  void *execute(void *);

protected:
  static const double ETA_C_DEFAULT_;
  static const double EPS;

private:
  double crossoverProbability_;
  double distributionIndex_;
  //TODO: Añadir VALID_TYPES;
  Solution ** doCrossover(double probability,
      Solution * parent1, Solution * parent2);
};

#endif
