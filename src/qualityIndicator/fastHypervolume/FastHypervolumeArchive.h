//  FastHypervolumeArchive.h
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

#ifndef __FAST_HYPERVOLUME_ARCHIVE__
#define __FAST_HYPERVOLUME_ARCHIVE__

#include <FastHypervolumeArchive.h>

#include <Archive.h>
#include <CrowdingComparator.h>
#include <DominanceComparator.h>
#include <EqualSolutions.h>
#include <FastHypervolume.h>

/**
 * This class implements a bounded archive based on the hypervolume quality indicator
 */
class FastHypervolumeArchive : public Archive {

private:

  /**
   * Stores the maximum size of the archive.
   */
  int maxSize;

  /**
   * stores the number of the objectives.
   */
  int objectives;

  /**
   * Stores a <code>Comparator</code> for dominance checking.
   */
  Comparator *dominance;

  /**
   * Stores a <code>Comparator</code> for equality checking (in the objective
   * space).
   */
  Comparator *equals;

  Comparator *crowdingDistance_;

  Solution *referencePoint;

public:

  /**
   * Constructor.
   * @param maxSize The maximum size of the archive.
   * @param numberOfObjectives The number of objectives.
   */
  FastHypervolumeArchive(int maxSize, int numberOfObjectives);

  /**
   * Destructor.
   */
  ~FastHypervolumeArchive();

  /**
   * Adds a <code>Solution</code> to the archive. If the <code>Solution</code>
   * is dominated by any member of the archive, then it is discarded. If the
   * <code>Solution</code> dominates some members of the archive, these are
   * removed. If the archive is full and the <code>Solution</code> has to be
   * inserted, the solution contributing the least to the HV of the solution set
   * is discarded.
   * @param solution The <code>Solution</code>
   * @return true if the <code>Solution</code> has been inserted, false
   * otherwise.
   */
  bool add(Solution *solution);

  /**
   * This method forces to compute the contribution of each solution
   */
  void computeHVContribution();

};

#endif /* __FAST_HYPERVOLUME_ARCHIVE__ */
