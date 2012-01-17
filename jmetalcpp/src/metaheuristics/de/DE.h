/*
 * @file DE.h
 * @author Esteban López
 * @date 16 January 2012
 */

#ifndef __DE__
#define __DE__

#include <Algorithm.h>
#include <Problem.h>
#include <SolutionSet.h>
#include <ObjectiveComparator.h>

/**
 * This class implements a differential evolution algorithm.
 */

class DE : public Algorithm {

public:
  DE(Problem * problem);
  SolutionSet * execute();
};


#endif /* __DE__ */
