/**
 * @file SolutionType.h
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 23 November 2011
**/

#ifndef __SOLUTION_TYPE__
#define __SOLUTION_TYPE__

#include <Problem.h>
#include <Variable.h>
#include <stddef.h>
//#include <stdlib.h>
#include <string>

class Problem;

/**
 * This class is aimed at defining a Type for every solution.
 * The type of a solution (a.k.a SolutionType) will define the type
 * of the variables composing that solution.
 * Advantages: Flexibility for defining different types of solutions
 * (mixing variable types, etc)
**/
class SolutionType {

protected:
	Problem *problem_;

public:
	SolutionType(Problem *problem);
	virtual Variable **createVariables() = 0;
	Variable **copyVariables(Variable **vars);

}; // SolutionType

#endif
