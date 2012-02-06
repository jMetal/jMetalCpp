/**
  * @file BinaryTournament2.h
  * @author Juan J. Durillo
  * @author Antonio J. Nebro
  * @author Esteban López
  * @date 01 December 2011
**/

#ifndef __BINARY_TOURNAMENT_2__
#define __BINARY_TOURNAMENT_2__

#include <SolutionSet.h>
#include <Selection.h>
#include <Comparator.h>
#include <PermutationUtility.h>
#include <DominanceComparator.h>

/**
 * This class implements an operator for binary selections using the same code
 * in Deb's NSGA-II implementation
 */
class BinaryTournament2 : public Selection {

private:
  Comparator * dominance_;
  int * a_;
  int index_;

public:
  BinaryTournament2(map<string, void *> parameters);
  ~BinaryTournament2();
  void *execute(void *);

};

#endif
