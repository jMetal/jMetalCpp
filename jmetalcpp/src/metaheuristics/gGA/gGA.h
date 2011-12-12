/*
 * gGA.h
 *
 *  Created on: 12/12/2011
 *      Author: antonio
 */

#ifndef __GGA_H__
#define __GGA_H__

#include <Algorithm.h>
#include <Problem.h>
#include <SolutionSet.h>

class gGA : public Algorithm {
private:
  int populationSize_;
  int maxEvaluations_;
  Problem *problem_;
public:
  gGA(Problem * problem);
  SolutionSet * execute();
};

#endif /* GGA_H_ */
