//  OneMax.h
//
//  Authors:
//       Antonio J. Nebro <antonio@lcc.uma.es>
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

#ifndef __ONEMAX_H__
#define __ONEMAX_H__

#include <JMetalInc/Problem.h>
#include <JMetalInc/BinarySolutionType.h>
#include <JMetalInc/Solution.h>

class OneMax : public Problem {
public:
	OneMax(int numberOfBits, int numberOfStrings = 1);
	~OneMax();
  void evaluate(Solution *solution);

};

#endif /* __ONEMAX_H__ */