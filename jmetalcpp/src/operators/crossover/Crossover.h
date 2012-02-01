/**
  * @file Crossover.h
  * @author Juan J. Durillo
  * @author Antonio J. Nebro
  * @author Esteban López
  * @date 30 November 2011
**/

#ifndef __CROSSOVER__
#define __CROSSOVER__

#include <Operator.h>

/**
  * @class Crossover
  * @brief This class is aimed at representing a Crossover operator
**/
class Crossover : public Operator {

public:
	Crossover(map<string, void *> parameters);

};

#endif
