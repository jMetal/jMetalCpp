//  AdaptiveRandomNeighborhood.h
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//       Antonio J. Nebro <antonio@lcc.uma.es>
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

#ifndef __ADAPTIVE_RANDOM_NEIGHBORHOOD__
#define __ADAPTIVE_RANDOM_NEIGHBORHOOD__

#include <Solution.h>
#include <SolutionSet.h>
#include <PseudoRandom.h>

#include <vector>
#include <algorithm>
//#include <list>



/**
 * Class representing an adaptive random neighborhood
 */
class AdaptiveRandomNeighborhood
{

private:

    SolutionSet * solutionSet_;
    std::vector<std::vector<int>> list_;
    int numberOfRandomNeighbours_;

public:

    AdaptiveRandomNeighborhood(SolutionSet * solutionSet, int numberOfRandomNeighbours);
    std::vector<int> getNeighbors(int i);
    int getNumberOfRandomNeighbours();
    SolutionSet * getBestFitnessSolutionInNeighborhood(Comparator * comparator);
    std::vector<std::vector<int>> getNeighborhood();
    void recompute();
    //std::string toString();

}; // AdaptiveRandomNeighborhood

#endif /* __ADAPTIVE_RANDOM_NEIGHBORHOOD__ */
