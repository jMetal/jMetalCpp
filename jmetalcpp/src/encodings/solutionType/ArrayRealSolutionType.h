/**
 * @file ArrayRealSolutionType.h
 * @author Esteban López
 * @version 1.0
 * @date 30 November 2011
 */

#ifndef __ARRAY_REAL_SOLUTION_TYPE__
#define __ARRAY_REAL_SOLUTION_TYPE__

#include <SolutionType.h>
#include <ArrayReal.h>

/**
  * Class representing the solution type of solutions composed of an ArrayReal
  * variable
  */
class ArrayRealSolutionType : public SolutionType {

public:
  ArrayRealSolutionType(Problem *problem);
  Variable **createVariables();
  Variable **copyVariables(Variable ** vars);
	
};

#endif
