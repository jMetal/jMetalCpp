//  CrowdingArchive.h
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

#ifndef __CROWDINGARCHIVE__
#define __CROWDINGARCHIVE__

#include <Archive.h>
#include <Comparator.h>
#include <CrowdingDistanceComparator.h>
#include <Distance.h>
#include <DominanceComparator.h>
#include <EqualSolutions.h>
#include <Solution.h>

/**
 * This class implements a bounded archive based on crowding distances (as
 * defined in NSGA-II).
 */
class CrowdingArchive : public Archive {

private:
  int maxSize_;
  int objectives_;
  Comparator * dominance_;
  Comparator * equals_;
  Comparator * crowdingDistance_;
  Distance * distance_;

public:
  CrowdingArchive(int maxSize, int numberOfObjectives);
  ~CrowdingArchive();
  bool add(Solution * solution);

};


#endif
