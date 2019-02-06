//  QualityIndicator.h
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

#ifndef QUALITYINDICATOR_H_
#define QUALITYINDICATOR_H_

#include <string>
#include <JMetalInc/SolutionSet.h>
#include <JMetalInc/Problem.h>
#include <JMetalInc/MetricsUtil.h>
#include <JMetalInc/Hypervolume.h>
#include <JMetalInc/Spread.h>
#include <JMetalInc/Epsilon.h>
#include <JMetalInc/GenerationalDistance.h>
#include <JMetalInc/InvertedGenerationalDistance.h>

class QualityIndicator {

private:
	SolutionSet * trueParetoFront_;
	double trueParetoFrontHypervolume_;
	Problem * problem_;
	int dim_;
	MetricsUtil * utilities_;

public:
	QualityIndicator(Problem * problem, string paretoFrontFile);
	~QualityIndicator();
	double getHypervolume(SolutionSet * solutionSet);
	double getTrueParetoFrontHypervolume();
	double getIGD(SolutionSet * solutionSet);
	double getGD(SolutionSet * solutionSet);
	double getSpread(SolutionSet * solutionSet);
	double getEpsilon(SolutionSet * solutionSet);

};

#endif /* QUALITYINDICATOR_H_ */
