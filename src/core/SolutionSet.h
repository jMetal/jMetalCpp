//  SolutionSet.h
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//       Antonio J. Nebro <antonio@lcc.uma.es>
//       Juan J. Durillo <durillo@lcc.uma.es>
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

#ifndef __SOLUTION_SET__
#define __SOLUTION_SET__

#include <string>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stddef.h>
#include <Solution.h>
#include <Comparator.h>

using namespace std;

//class Solution ;
class Comparator;

/**
 * @class SolutionSet
 * @brief This class is aimed at representing a solution set
**/
class SolutionSet {

protected:
  vector<Solution*> solutionsList_;
  int capacity_;

public:

  SolutionSet();
  SolutionSet(int maximumSize);
  ~SolutionSet();

  bool add(Solution * solution);
  bool add(int index, Solution * solution);
  Solution *get(int index);
  int getMaxSize();
  void sort(Comparator * comparator);
  int indexBest(Comparator * comparator);
  Solution * best(Comparator * comparator);
  int indexWorst(Comparator * comparator);
  Solution * worst(Comparator * comparator);
  int size();
  void printObjectivesToFile(string path);
  void printObjectivesToFile(string path, bool append);
  void printVariablesToFile(string file);
  void printVariablesToFile(string file, bool append);
  void clear();
  void clear(bool del);
  void remove(int i);
  void remove(int i, bool del);
  SolutionSet * join(SolutionSet * another);
  void replace(int position, Solution * solution);
  void replace(int position, Solution * solution, bool del);
  vector <vector<double> > writeObjectivesToMatrix();
  void printObjectives();

  //void reset() ;
  //string toString();
};


#endif
