/*
 * InsertionMutation.h
 *
 *  Created on: 9 Feb 2019
 *      Author: Emad Alharbi
 *      University of York,UK
 */

#ifndef __INT_NONE_REPEATED_SOLUTION_TYPE__
#define __INT_NONE_REPEATED_SOLUTION_TYPE__


#include "SolutionType.h"
#include "Int.h"
#include <string>

/**
 * This class is aimed at defining a Type encoding a Int solution
**/
class IntNoneRepeatedSolutionType : public SolutionType {

public:
	IntNoneRepeatedSolutionType(Problem *problem);
    Variable **createVariables();

};

#endif
