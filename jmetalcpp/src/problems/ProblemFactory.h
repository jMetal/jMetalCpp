/**
 * @file ProblemFactory.h
 * @author Esteban López
 * @version 1.0
 * @date 18 January 2012
 */

#ifndef __PROBLEM_FACTORY__
#define __PROBLEM_FACTORY__

#include <Problem.h>
#include <stdio.h>
#include <string.h>

#include <DTLZ1.h>
#include <Fonseca.h>
#include <ZDT1.h>


class ProblemFactory {

public:
  static Problem * getProblem(char * name);
  static Problem * getProblem(int argc, char ** argv);
  static Problem * getProblem(char * name, int argc, char ** argv);
};

#endif // __PROBLEM_FACTORY__

