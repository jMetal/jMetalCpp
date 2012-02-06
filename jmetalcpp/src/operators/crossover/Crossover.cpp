/**
  * @file Crossover.h
  * @author Juan J. Durillo
  * @author Antonio J. Nebro
  * @author Esteban López
  * @date 30 November 2011
**/

#include <Crossover.h>

Crossover::Crossover(map<string , void*> parameters)
: Operator(parameters) {}

Crossover::~Crossover() { /* do nothing */ }
