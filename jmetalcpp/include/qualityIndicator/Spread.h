//  Spread.h
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

#ifndef __SPREAD__
#define __SPREAD__

#include <MetricsUtil.h>
#include <LexicoGraphicalComparator.h>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * This class implements the spread quality indicator.
 * It can be used also as command line program just by typing:
 *  "java jmetal.qualityIndicator.Spread <solutionFrontFile> <trueFrontFile>".
 * This metric is only applicable to two bi-objective problems.
 * Reference: Deb, K., Pratap, A., Agarwal, S., Meyarivan, T.: A fast and
 *            elitist multiobjective genetic algorithm: NSGA-II. IEEE Trans.
 *            on Evol. Computation 6 (2002) 182-197
 */

class Spread {

private:
  static bool compareFront(vector<double> pointOne, vector<double> pointTwo);

public:

  MetricsUtil * utils_;

  Spread();
  ~Spread();
  double spread (vector< vector<double> > front,
      vector< vector<double> > trueParetoFront, int numberOfObjectives);

}; // Spread

#endif /* __SPREAD__ */
