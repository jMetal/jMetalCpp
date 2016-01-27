//  MOCHC.h
//  //
//  //  Author:
//  //       Juanjo
//  //
//  //  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
//  //
//  //  This program is free software: you can redistribute it and/or modify
//  //  it under the terms of the GNU Lesser General Public License as published by
//  //  the Free Software Foundation, either version 3 of the License, or
//  //  (at your option) any later version.
//  //
//  //  This program is distributed in the hope that it will be useful,
//  //  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  //  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  //  GNU Lesser General Public License for more details.
//  //
//  //  You should have received a copy of the GNU Lesser General Public License
//  //  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <Algorithm.h>
#include <Problem.h>
#include <SolutionSet.h>
#include <Distance.h>
#include <Ranking.h>
#include <Distance.h>
#include <Binary.h>
#include <Solution.h>
#include <CrowdingComparator.h>
#include <cmath>
#include <iostream>
// Juanjo: I am following the same sintax as in the other algorithms. 
// however, I would never ever program like this in C++
// I would recommend to use something as MOCHC(Problem &)


class MOCHC : public Algorithm {

	bool equalsIndividuals(Solution &s1, Solution & s2);
	bool exist(Solution &s1, SolutionSet &set2);
	bool equals(SolutionSet& set1, SolutionSet& set2);
	int hammingDistance(Solution &sol1, Solution& sol2);
	SolutionSet *rankingAndCrowdingSelection(SolutionSet *sol,int size);

public:
	MOCHC(Problem * problem) : Algorithm(problem){};
	SolutionSet *execute();
};

