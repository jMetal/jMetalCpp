/**
	* @file ObjectiveComparator.h
	* @author Juan J. Durillo
	* @author Antonio J. Nebro
	* @author Esteban López
	* @date 28 November 2011
**/

#ifndef __COMPARATOR__
#define __COMPARATOR__

#include <Solution.h>

/**
 * @class DominanceComparator
 * @brief This class is aimed at representing a Solution
**/
class Comparator {

public:
  virtual int compare(Solution * one, Solution * two) = 0;

};

#endif
