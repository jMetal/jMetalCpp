//  paes.h
//
//  Author:
//       Cristian Zambrano <cristian_uteq@hotmail.com>
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

#ifndef PAES_H_
#define PAES_H_

#include <Algorithm.h>
#include <Problem.h>
#include <SolutionSet.h>
#include <DominanceComparator.h>
#include <AdaptiveGridArchive.h>

class paes : public Algorithm {

public:
	paes(Problem * problem);
	Solution * test(Solution * solution,Solution * mutatedSolution,
                      AdaptiveGridArchive * archive);
    SolutionSet * execute();
};



#endif /* PAES_H_ */
