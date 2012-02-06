/**
  * @file PermutationUtility.cpp
  * @author Esteban López
  * @date 01 December 2011
**/

#include <PermutationUtility.h>

int * PermutationUtility::intPermutation(int length) {

  int * aux    = new int[length];
  int * result = new int[length];

  // First, create an array from 0 to length - 1.
  // Also is needed to create an random array of size length
  for (int i = 0; i < length; i++) {
    result[i] = i;
    aux[i] = PseudoRandom::randInt(0,length-1);
  } // for

  // Sort the random array with effect in result, and then we obtain a
  // permutation array between 0 and length - 1
  for (int i = 0; i < length; i++) {
    for (int j = i + 1; j < length; j++) {
      if (aux[i] > aux[j]) {
        int tmp;
        tmp = aux[i];
        aux[i] = aux[j];
        aux[j] = tmp;
        tmp = result[i];
        result[i] = result[j];
        result[j] = tmp;
      } // if
    } // for
  } // for
  delete[] aux;

  return result;

}
