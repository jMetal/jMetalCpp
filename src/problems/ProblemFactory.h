//  ProblemFactory.h
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//
//  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __PROBLEM_FACTORY__
#define __PROBLEM_FACTORY__

#include <Problem.h>
#include <stdio.h>
#include <string.h>

#include <CEC2005Problem.h>
#include <DTLZ1.h>
#include <DTLZ2.h>
#include <DTLZ3.h>
#include <DTLZ4.h>
#include <DTLZ5.h>
#include <DTLZ6.h>
#include <DTLZ7.h>
#include <Fonseca.h>
#include <Griewank.h>
#include <Kursawe.h>
#include <LZ09_F1.h>
#include <LZ09_F2.h>
#include <LZ09_F3.h>
#include <LZ09_F4.h>
#include <LZ09_F5.h>
#include <LZ09_F6.h>
#include <LZ09_F7.h>
#include <LZ09_F8.h>
#include <LZ09_F9.h>
#include <OneMax.h>
#include <Rastrigin.h>
#include <Rosenbrock.h>
#include <Schaffer.h>
#include <Sphere.h>
#include <Srinivas.h>
#include <Tanaka.h>
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

