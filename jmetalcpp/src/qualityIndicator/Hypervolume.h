//  Hypervolume.h
//
//  Author:
//       Esteban López <esteban@lcc.uma.es>
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

#ifndef __HYPERVOLUME__
#define __HYPERVOLUME__

#include <MetricsUtil.h>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

/**
 * This class implements the hypervolume indicator. The code is a C++ version
 * of the original metric implementation by Eckart Zitzler.
 * Reference: E. Zitzler and L. Thiele
 *           Multiobjective Evolutionary Algorithms: A Comparative Case Study
 *           and the Strength Pareto Approach,
 *           IEEE Transactions on Evolutionary Computation, vol. 3, no. 4,
 *           pp. 257-271, 1999.
 */

class Hypervolume {

private:

  bool dominates(vector<double> point1, vector<double> point2, int noObjectives);
  void swap(vector< vector<double> > * front, int i, int j);
  int filterNondominatedSet(vector< vector<double> > * front, int noPoints,
      int noObjectives);
  double surfaceUnchangedTo(vector< vector<double> > front, int noPoints,
      int objective);
  int reduceNondominatedSet(vector< vector<double> > * front, int noPoints,
      int objective, double threshold);
  vector< vector<double> > mergeFronts(vector< vector<double> > front1,
      vector< vector<double> > front2);

public:

  MetricsUtil * utils_;

  Hypervolume();
  ~Hypervolume();

  double calculateHypervolume(vector< vector<double> > * front, int noPoints,
      int noObjectives);
  double hypervolume(vector< vector<double> > paretoFront,
      vector< vector<double> > paretoTrueFront, int numberOfObjectives);

};

#endif /* __HYPERVOLUME__ */
