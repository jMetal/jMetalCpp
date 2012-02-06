/**
 * @file ObjectiveComparator.h
 * @author Esteban López
 * @date 01 December 2011
**/

#ifndef __OBJECTIVE_COMPARATOR__
#define __OBJECTIVE_COMPARATOR__

#include <Comparator.h>
#include <Solution.h>

/**
 * This class implements a <code>Comparator</code> (a method for comparing
 * <code>Solution</code> objects) based on a objective values.
 */
class ObjectiveComparator : public Comparator {

private:
  int nObj;

public:
  ObjectiveComparator(int nObj);
  int compare(Solution * o1, Solution * o2);

};

#endif
