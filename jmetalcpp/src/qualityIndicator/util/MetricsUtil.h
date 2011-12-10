/*
  * @file MetricsUtil.h
  * @author Esteban López
  * @date 24 November 2011
 */

#ifndef __METRICSUTIL__
#define __METRICSUTIL__

#include <limits>


/**
  * @class MetricsUtil
  * @brief This class provides some utilities to compute quality indicators
**/

class MetricsUtil {
private:
  int populationSize_;
  //int maxEvaluations_;
  //QualityIndicator *indicators_;
  //Problem *problem_;
public:
	int getSumaUno(int i);
	//TODO: double **readFront(string path);
	double *getMaximumValues(double **front, int frontSize, int noObjectives);
	double *getMinimumValues(double **front, int frontSize, int noObjectives);
	//TODO: double distance(double *a, double *b);
	//TODO: double distanceToClosedPoint(double *point, double **front);
	//TODO: double distanceToNearestPoint(double *point, double **front);
	double **getNormalizedFront(double **front, int frontSizeX, int frontSizeY,
			double *maximumValue, double *minimumValue);
	double **invertedFront(double **front, int frontSizeX, int frontSizeY);
	//TODO: SolutionSet readNonDominatedSolutionSet(string path);
};


#endif /* __METRICSUTIL__ */
