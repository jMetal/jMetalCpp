/**
  * @file Mutation.h
  * @author Juan J. Durillo
  * @author Antonio J. Nebro
  * @author Esteban López
  * @date 01 December 2011
**/

#ifndef __MUTATION__
#define __MUTATION__

#include <Operator.h>

/**
 * @class Mutation
 * @brief This class is aimed at representing a Mutation operator
**/
class Mutation : public Operator{

public:
  Mutation(map<string, void *> parameters);
  virtual ~Mutation() = 0;

};

#endif
