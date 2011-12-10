/**
 * @file Problem.h
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 23 November 2011
**/

#ifndef __PROBLEM__
#define __PROBLEM__

#include <string>
#include <iostream>
//#include <Global.h>
#include <SolutionType.h>
#include <Solution.h>
#include <stddef.h>
//#include <stdlib.h>

using namespace std;

class SolutionType ;
class Solution ;

/**
 * Abstract class representing a multiobjective optimization problem
 */
class Problem {

private:
	static const int DEFAULT_PRECISSION;

protected:
  int numberOfVariables_;
  int numberOfObjectives_;
  int numberOfConstraints_;
  string problemName_;
  SolutionType *solutionType_;
  double *lowerLimit_;
  double *upperLimit_;
  int *precision_;
  int *length_;
   
public:

  //VariableType *variableType_;
  /**
   * Receives as parameter a solution to be evaluated. 
   * Evaluates this solution according to the objective
   * functions that will be stored in the solution itself.
   * After the execution of this method the objective values
   * can be retrieved using solution->getObjective(int)
   */

  Problem();
  Problem(SolutionType * solutionType);
  int getNumberOfVariables();
  void setNumberOfVariables(int numberOfVariables);
  int getNumberOfObjectives();
  void setNumberOfObjectives(int numberOfObjectives);
  double getLowerLimit(int i);
  double getUpperLimit(int i);
  virtual void evaluate(Solution * solution) = 0;
  int getNumberOfConstraints();
  void evaluateConstraints(Solution * solution);
  int getPrecision(int var);
  int * getPrecision();
  void setPrecision(int * precision);
  int getLength(int var);
  void setSolutionType(SolutionType * type);
  SolutionType * getSolutionType();
  string getName();
  int getNumberOfBits();

//  virtual void evaluateConstraints(Solution solution);
//  virtual int getNumberOfVariables();
//  virtual void setNumberOfVariables(int value);
//  int getNumberOfObjectives();
//  virtual void setNumberOfObjectives(int value);
//  virtual double getLowerLimit(int index);
//  virtual double getUpperLimit(int index);
//  virtual int getNumberOfConstraints();
//  virtual void setSolutionType(SolutionType *type);
//  virtual SolutionType *getSolutionType();
//  virtual std::string getName();

}; // Problem

#endif
