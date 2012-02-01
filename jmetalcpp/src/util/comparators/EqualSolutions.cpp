/**
 * @file EqualSolutions.cpp
 * @author Esteban López
 * @date 13 December 2011
**/


#include <EqualSolutions.h>


/**
 * This class implements a <code>Comparator</code> (a method for comparing
 * <code>Solution</code> objects) based whether all the objective values are
 * equal or not. A dominance test is applied to decide about what solution
 * is the best.
 */


/**
 * Compares two solutions.
 * @param solution1 Object representing the first <code>Solution</code>.
 * @param solution2 Object representing the second <code>Solution</code>.
 * @return -1, or 0, or 1, or 2 if solution1 is dominates solution2, solution1
 * and solution2 are equals, or solution1 is greater than solution2,
 * respectively.
 */
int EqualSolutions::compare(Solution * solution1, Solution * solution2) {

  if (solution1==NULL)
    return 1;
  else if (solution2 == NULL)
    return -1;

  int dominate1 ; // dominate1 indicates if some objective of solution1
                  // dominates the same objective in solution2. dominate2
  int dominate2 ; // is the complementary of dominate1.

  dominate1 = 0 ;
  dominate2 = 0 ;

  int flag;
  double value1, value2;
  for (int i = 0; i < solution1->getNumberOfObjectives(); i++) {
    flag = (new ObjectiveComparator(i))->compare(solution1,solution2);
    value1 = solution1->getObjective(i);
    value2 = solution2->getObjective(i);

    if (value1 < value2) {
      flag = -1;
    } else if (value1 > value2) {
      flag = 1;
    } else {
      flag = 0;
    }

    if (flag == -1) {
      dominate1 = 1;
    }

    if (flag == 1) {
      dominate2 = 1;
    }
  }

  if (dominate1== 0 && dominate2 ==0) {
    return 0; //No one dominate the other
  }

  if (dominate1 == 1) {
    return -1; // solution1 dominate
  } else if (dominate2 == 1) {
    return 1;    // solution2 dominate
  }

  return 2;

} // compare
