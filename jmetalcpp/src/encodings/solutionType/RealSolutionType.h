/**
 * @file RealSolutionType.h
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 30 November 2011
 */

#ifndef __REAL_SOLUTION_TYPE__
#define __REAL_SOLUTION_TYPE__

#include <SolutionType.h>
#include <Real.h>
#include <string>

/**
 * This class is aimed at defining a Type encoding a Real solution
**/
class RealSolutionType : public SolutionType {

public:
   RealSolutionType(Problem *problem);
   Variable **createVariables();
	
};

#endif
