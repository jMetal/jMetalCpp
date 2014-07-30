//  FastHypervolume.h
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//
//  Copyright (c) 2014 Antonio J. Nebro
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

#ifndef __FAST_HYPERVOLUME__
#define __FAST_HYPERVOLUME__

#include <MetricsUtil.h>
#include <ObjectiveComparator.h>
//#include <iostream>
//#include <cstdlib>
#include <math.h>

using namespace std;

class FastHypervolume {

private:

  Solution * referencePoint_;
  int numberOfObjectives_;
  double offset_ = 20.0;

  void updateReferencePoint(SolutionSet * solutionSet);
  double get2DHV(SolutionSet * solutionSet);
  double computeHypervolume(SolutionSet * solutionSet);

  // double computeSolutionHVContribution(SolutionSet * solutionSet,
  //     int solutionIndex, double solutionSetHV);

public:

  FastHypervolume();
  FastHypervolume(double offset);
  ~FastHypervolume();


  void computeHVContributions(SolutionSet * solutionSet);

};

#endif /* __HYPERVOLUME__ */
