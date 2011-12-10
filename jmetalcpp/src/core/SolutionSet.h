/**
 * @file SolutionSet.h
 * @author Juan J. Durillo
 * @author Antonio J. Nebro
 * @author Esteban López
 * @date 28 November 2011
**/

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
//#include <list>
//#include <stdlib.h>
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
  //~SolutionSet();
   
  bool add(Solution * solution);
  Solution *get(int index);
  int getMaxSize();
  void sort(Comparator * comparator);
  int indexBest(Comparator * comparator);
  Solution * best(Comparator * comparator);
  int indexWorst(Comparator * comparator);
  Solution * worst(Comparator * comparator);
  int size();
  void printObjectivesToFile(string path);
  void printVariablesToFile(string file);
  void clear();
  void remove(int i);
  // Iterator iterator();
  SolutionSet * join(SolutionSet * another);
  void replace(int position, Solution * solution);
  //double **writeObjectivesToMatrix();

  //void reset() ;
  //string toString();
};


#endif
