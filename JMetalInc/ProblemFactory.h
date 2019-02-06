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

#include <JMetalInc/Problem.h>
#include <stdio.h>
#include <string.h>

#include <JMetalInc/CEC2005Problem.h>
#include <JMetalInc/DTLZ1.h>
#include <JMetalInc/DTLZ2.h>
#include <JMetalInc/DTLZ3.h>
#include <JMetalInc/DTLZ4.h>
#include <JMetalInc/DTLZ5.h>
#include <JMetalInc/DTLZ6.h>
#include <JMetalInc/DTLZ7.h>
#include <JMetalInc/Fonseca.h>
#include <JMetalInc/Griewank.h>
#include <JMetalInc/Kursawe.h>
#include <JMetalInc/LZ09_F1.h>
#include <JMetalInc/LZ09_F2.h>
#include <JMetalInc/LZ09_F3.h>
#include <JMetalInc/LZ09_F4.h>
#include <JMetalInc/LZ09_F5.h>
#include <JMetalInc/LZ09_F6.h>
#include <JMetalInc/LZ09_F7.h>
#include <JMetalInc/LZ09_F8.h>
#include <JMetalInc/LZ09_F9.h>
#include <JMetalInc/OneMax.h>
#include <JMetalInc/Rastrigin.h>
#include <JMetalInc/Rosenbrock.h>
#include <JMetalInc/Schaffer.h>
#include <JMetalInc/Sphere.h>
#include <JMetalInc/Srinivas.h>
#include <JMetalInc/Tanaka.h>
#include <JMetalInc/ZDT1.h>
#include <JMetalInc/ZDT2.h>
#include <JMetalInc/ZDT3.h>
#include <JMetalInc/ZDT4.h>
#include <JMetalInc/ZDT5.h>
#include <JMetalInc/ZDT6.h>

class ProblemFactory {

public:
  static Problem * getProblem(char * name);
  static Problem * getProblem(int argc, char ** argv);
  static Problem * getProblem(char * name, int argc, char ** argv);
};

#endif // __PROBLEM_FACTORY__

