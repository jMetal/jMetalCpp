//  WorstSolutionSelection.h
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

#ifndef __WORST_SOLUTION_SELECTION__
#define __WORST_SOLUTION_SELECTION__

#include <SolutionSet.h>
#include <Selection.h>
#include <Comparator.h>

/**
 * This class implements a selection operator used for selecting the worst
 * solution in a SolutionSet according to a given comparator
 */
class WorstSolutionSelection : public Selection {

private:
  Comparator * comparator_;

public:
  WorstSolutionSelection(map<string, void *> parameters);
  void *execute(void *);

};

#endif // __WORST_SOLUTION_SELECTION__
