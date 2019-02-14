//  BarrosF1F2.h
//
//  Authors:
//       Sérgio Vieira <sergiosvieira@gmail.com>
//       
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

#ifndef __BARROS_F1_F5__
#define __BARROS_F1_F5__

#include <Problem.h>
#include <math.h>
#include <ArrayRealSolutionType.h>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <Solution.h>

/**
  * @class Barros F1 F5
  * @brief Class representing problem Barros
  **/
class BarrosF1F5 : public Problem
{
protected:
	const double PI = 3.141592653589793;
public:
    BarrosF1F5(std::string solutionType);
    ~BarrosF1F5();
    void evaluate(Solution *solution);
};

#endif /** __BARROS_F1_F2__ **/
