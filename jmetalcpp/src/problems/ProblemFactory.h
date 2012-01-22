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
#include <DTLZ2.h>
#include <DTLZ3.h>
#include <DTLZ4.h>
#include <Fonseca.h>
#include <ZDT1.h>
#include <ZDT2.h>
#include <ZDT3.h>
#include <ZDT4.h>
#include <ZDT5.h>
#include <ZDT6.h>

class ProblemFactory {

public:
  static Problem * getProblem(char * name);
  static Problem * getProblem(int argc, char ** argv);
  static Problem * getProblem(char * name, int argc, char ** argv);
};

#endif // __PROBLEM_FACTORY__

