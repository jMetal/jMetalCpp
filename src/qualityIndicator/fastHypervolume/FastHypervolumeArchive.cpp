//  FastHypervolumeArchive.cpp
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


#include <FastHypervolumeArchive.h>


/**
 * This class implements a bounded archive based on the hypervolume quality indicator
 */


/**
 * Constructor.
 * @param maxSize The maximum size of the archive.
 * @param numberOfObjectives The number of objectives.
 */
FastHypervolumeArchive::FastHypervolumeArchive(int maxSize, int numberOfObjectives)
: Archive(maxSize) {
  this->maxSize         = maxSize;
  this->objectives      = numberOfObjectives;
  this->dominance       = new DominanceComparator();
  this->equals          = new EqualSolutions();
  this->referencePoint  = new Solution(objectives) ;
  for (int i = 0; i < objectives; i++) {
    referencePoint->setObjective(i, std::numeric_limits<double>::max());
  }
  crowdingDistance_ = new CrowdingComparator();
} // FastHypervolumeArchive


/**
 * Destructor.
 */
FastHypervolumeArchive::~FastHypervolumeArchive() {
  cout << "DELETING FASTHYPERVOLUMEARCHIVE" << endl;
  delete dominance;
  delete equals;
  delete referencePoint;
  delete crowdingDistance_;
} // ~FastHypervolumeArchive


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
bool FastHypervolumeArchive::add(Solution *solution){
  int flag = 0;
  int i = 0;
  Solution *aux; //Store an solution temporally

  while (i < solutionsList_.size()){
    aux = solutionsList_[i];

    flag = dominance->compare(solution,aux);
    if (flag == 1) {               // The solution to add is dominated
      return false;                // Discard the new solution
    } else if (flag == -1) {       // A solution in the archive is dominated
      // Remove it from the population
      delete aux;
      solutionsList_.erase(solutionsList_.begin() + i);
    } else {
      if (equals->compare(aux,solution)==0) {
        // There is an equal solution in the population
        return false; // Discard the new solution
      }  // if
      i++;
    }
  }
  // Insert the solution into the archive
  bool res = true;
  solutionsList_.push_back(solution);
  if (size() > maxSize) { // The archive is full
    computeHVContribution();
    int indexWorst_ = indexWorst(crowdingDistance_);
    if (solution == solutionsList_[indexWorst_]) {
      res = false;
    } else {
      delete solutionsList_[indexWorst_];
    }
    remove(indexWorst_);
  }
  return res;
} // add


/**
 * This method forces to compute the contribution of each solution
 */
void FastHypervolumeArchive::computeHVContribution() {
  if (size() > 2) { // The contribution can be updated
    FastHypervolume *fastHV = new FastHypervolume();
    fastHV->computeHVContributions(this);
    delete fastHV;
  }
} // computeHVContribution
