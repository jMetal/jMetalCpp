/**
 * @file BinaryRealSolutionType.h
 * @author Esteban López
 * @version 1.0
 * @date 02 December 2011
 */

#ifndef __BINARY_REAL_SOLUTION_TYPE__
#define __BINARY_REAL_SOLUTION_TYPE__

#include <SolutionType.h>
#include <BinaryReal.h>

/**
 * This class is aimed at defining a Type encoding a Real solution
**/
class BinaryRealSolutionType : public SolutionType {

public:
   BinaryRealSolutionType(Problem * problem);
   Variable ** createVariables();
	
};

#endif
