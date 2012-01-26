/**
 * @file Algorithm.h
 * @author Juan J. Durillo
 * @author Antonio J. Nebro
 * @author Esteban López
 * @date 23 November 2011
**/

#ifndef __ALGORITHM__
#define __ALGORITHM__

#include <string>
#include <SolutionSet.h>
#include <Operator.h>
#include <Problem.h>

/**
 *  This class implements a generic template for the algorithms developed in
 *  jMetal. Every algorithm must have a mapping between the parameters and
 *  and their names, and another mapping between the operators and their names.
 *  The class declares an abstract method called <code>execute</code>, which
 *  defines the behavior of the algorithm.
**/
class Algorithm {

public:
	Algorithm(Problem *problem);
	~Algorithm();
	virtual SolutionSet * execute() = 0; // this launch the execution
																			 //	of an algorithm
	void addOperator(string name, Operator *operator_);
	Operator * getOperator(string name);
	void setInputParameter(string name, void *value);
	void * getInputParameter(string name);
	void setOutputParameter(string name, void *value);
	void * getOutputParameter(string name);
	Problem * getProblem();

protected:
   Problem *problem_;
   map<string, Operator *> operators_;
   map<string, void *> inputParameters_;
   map<string, void *> outputParameters_;

}; // Algorithm

#endif
