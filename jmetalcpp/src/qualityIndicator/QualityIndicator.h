/*
 * @file QualityIndicator.h
 * @author Esteban López
 * @date 01 December 2011
 */

#ifndef QUALITYINDICATOR_H_
#define QUALITYINDICATOR_H_

#include <string>
#include <SolutionSet.h>
#include <Problem.h>
#include <MetricsUtil.h>

class QualityIndicator {

private:
	SolutionSet * trueParetoFront_;
	double trueParetoFrontHypervolume_;
	Problem * problem_;
	MetricsUtil * utilities_;

public:
	QualityIndicator(Problem * problem, string paretoFrontFile);
	double getHypervolume(SolutionSet * solutionSet);
	double getTrueParetoFrontHypervolume();
	double getIGD(SolutionSet * solutionSet);
	double getGD(SolutionSet * solutionSet);
	double getSpread(SolutionSet * solutionSet);
	double getEpsilon(SolutionSet * solutionSet);

};

#endif /* QUALITYINDICATOR_H_ */
