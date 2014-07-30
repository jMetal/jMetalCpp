//  NonDominatedSolutionList.cpp
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


#include <NonDominatedSolutionList.h>


/**
 * Constructor.
 * The objects of this class are lists of non-dominated solutions according to
 * a Pareto dominance comparator.
 */
NonDominatedSolutionList::NonDominatedSolutionList()
: SolutionSet() {

  dominance = new DominanceComparator();
  equal = new SolutionComparator();

} // NonDominatedList


/**
 * Constructor.
 * This constructor creates a list of non-dominated individuals using a
 * comparator object.
 * @param dominance The comparator for dominance checking.
 */
NonDominatedSolutionList::NonDominatedSolutionList(Comparator *dominance)
: SolutionSet() {

  this->dominance = dominance;
  this->equal     = new SolutionComparator();

} // NonDominatedList


/**
 * Destructor.
 */
NonDominatedSolutionList::~NonDominatedSolutionList() {

  delete dominance;
  delete equal;

} // ~NonDominatedSolutionList


/** Inserts a solution in the list
 * @param solution The solution to be inserted.
 * @return true if the operation success, and false if the solution is
 * dominated or if an identical individual exists.
 * The decision variables can be null if the solution is read from a file; in
 * that case, the domination tests are omitted
 */
bool NonDominatedSolutionList::add(Solution *solution) {

  int i = 0;
  Solution * aux; //Store an solution temporally

  if (solution->getDecisionVariables() != NULL) {
    while (i < solutionsList_.size()) {
      aux = solutionsList_[i];
      int flag = dominance->compare(solution,aux);

      if (flag == -1) {  // A solution in the list is dominated by the new one
        delete aux;
        solutionsList_.erase(solutionsList_.begin()+i);
      } else if (flag == 0) { // Non-dominated solutions
       flag = equal->compare(solution,aux);
       if (flag == 0) {
         return false;   // The new solution is in the list
       }
       i++;
      } else if (flag == 1) { // The new solution is dominated
        return false;
      }
    } // while
  } // if

  //At this point, the solution is inserted into the list
  solutionsList_.push_back(solution);

  return true;
} // add
