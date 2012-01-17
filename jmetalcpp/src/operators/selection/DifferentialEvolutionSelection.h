/**
  * @file DifferentialEvolutionSelection.h
  * @author Esteban López
  * @date 16 January 2012
**/

#ifndef __DIFFERENTIAL_EVOLUTION_SELECTION__
#define __DIFFERENTIAL_EVOLUTION_SELECTION__

#include <Selection.h>
#include <Solution.h>
#include <SolutionSet.h>
#include <PseudoRandom.h>

/**
 * Class implementing the selection operator used in DE: three different solutions
 * are returned from a population.
 */
class DifferentialEvolutionSelection : public Selection {

public:
  DifferentialEvolutionSelection(map<string, void *> parameters);
  void *execute(void *);

};

#endif // __DIFFERENTIAL_EVOLUTION_SELECTION__
