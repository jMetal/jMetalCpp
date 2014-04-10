//  ZDT5.h
//
//  Author:
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

#ifndef __ZDT5_H__
#define __ZDT5_H__

#include <Problem.h>
#include <math.h>
#include <cmath>
#include <BinarySolutionType.h>
#include <Solution.h>

class ZDT5 : public Problem {
private:
	double evalG(Solution *x) ;
	double evalH(double f, double g) ;
  double evalV(double) ;

	double * fx_ ;
public:
	ZDT5(string solutionType, int numberOfVariables = 11);
	void evaluate(Solution *solution);

	virtual ~ZDT5();
};

#endif /* __ZDT5_H__ */
