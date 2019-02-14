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
#include <algorithm>

/**
 * Class representing an adaptive random neighborhood
 */
class AdaptiveRandomNeighborhood
{
protected:
    SolutionSet * solutionSet_ = nullptr;
	MatrixOfInteger list_;
    int numberOfRandomNeighbours_;
public:
    AdaptiveRandomNeighborhood(SolutionSet * solutionSet, int numberOfRandomNeighbours);
    VectorOfInteger getNeighbors(int i);
    int getNumberOfRandomNeighbours();
    SolutionSet * getBestFitnessSolutionInNeighborhood(Comparator * comparator);
    MatrixOfInteger getNeighborhood();
    void recompute();
}; // AdaptiveRandomNeighborhood

#endif /* __ADAPTIVE_RANDOM_NEIGHBORHOOD__ */
