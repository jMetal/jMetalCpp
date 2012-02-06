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
#include <SolutionType.h>
#include <Solution.h>
#include <stddef.h>

using namespace std;

class SolutionType;
class Solution;

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
  Problem();
  Problem(SolutionType * solutionType);
  ~Problem();
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

}; // Problem

#endif
