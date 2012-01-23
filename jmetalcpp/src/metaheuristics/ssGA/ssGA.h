/*
 * @file ssGA.h
 * @author Esteban López
 * @date 20 January 2012
 */

#ifndef __SSGA_H__
#define __SSGA_H__

#include <Algorithm.h>
#include <Problem.h>
#include <SolutionSet.h>
#include <ObjectiveComparator.h>
#include <WorstSolutionSelection.h>

/**
 * Class implementing a steady-state genetic algorithm
 */
class ssGA : public Algorithm {

public:
  ssGA(Problem * problem);
  SolutionSet * execute();

};

#endif /* __SSGA_H__ */
