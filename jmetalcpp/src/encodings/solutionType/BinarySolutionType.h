/**
 * @file BinarySolutionType.h
 * @author Esteban López
 * @version 1.0
 * @date 30 November 2011
 */

#ifndef __BINARY_SOLUTION_TYPE__
#define __BINARY_SOLUTION_TYPE__

#include <SolutionType.h>
#include <BinaryReal.h>
//#include <Global.h>

/**
 * This class is aimed at defining a Type encoding a Real solution
**/
class BinarySolutionType : public SolutionType {

public:
	BinarySolutionType(Problem *problem);
   Variable **createVariables();
	
};

#endif
