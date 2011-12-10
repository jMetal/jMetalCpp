/*
 * @file QualityIndicator.cpp
 * @author Esteban López
 * @date 01 December 2011
 */


#include <QualityIndicator.h>


/**
 * Constructor
 * @param paretoFrontFile
 */
QualityIndicator::QualityIndicator(Problem * problem,
																	 string paretoFrontFile) {
  problem_ = problem ;
  utilities_ = new MetricsUtil() ;
  trueParetoFront_ = utilities_->readNonDominatedSolutionSet(paretoFrontFile);
  trueParetoFrontHypervolume_ = new Hypervolume()->hypervolume(
               trueParetoFront_.writeObjectivesToMatrix(),
               trueParetoFront_.writeObjectivesToMatrix(),
               problem_.getNumberOfObjectives());
} // Constructor


/**
 * Returns the hypervolume of solution set
 * @param solutionSet
 * @return The value of the hypervolume indicator
 */
double QualityIndicator::getHypervolume(SolutionSet * solutionSet) {
	return new Hypervolume().hypervolume(solutionSet.writeObjectivesToMatrix(),
	                                         trueParetoFront_.writeObjectivesToMatrix(),
	                                         problem_.getNumberOfObjectives());
} // getHypervolume


/**
 * Returns the hypervolume of the true Pareto front
 * @return The hypervolume of the true Pareto front
 */
double QualityIndicator::getTrueParetoFrontHypervolume() {
	return trueParetoFrontHypervolume_ ;
} // getTrueParetoFrontHypervolume


/**
 * Returns the inverted generational distance of solution set
 * @param solutionSet
 * @return The value of the hypervolume indicator
 */
double QualityIndicator::getIGD(SolutionSet * solutionSet) {
  return new InvertedGenerationalDistance().invertedGenerationalDistance(
                  solutionSet.writeObjectivesToMatrix(),
                  trueParetoFront_.writeObjectivesToMatrix(),
                  problem_.getNumberOfObjectives());
} // getIGD


/**
 * Returns the generational distance of solution set
 * @param solutionSet
 * @return The value of the hypervolume indicator
 */
double QualityIndicator::getGD(SolutionSet * solutionSet) {
  return new GenerationalDistance().generationalDistance(
                  solutionSet.writeObjectivesToMatrix(),
                  trueParetoFront_.writeObjectivesToMatrix(),
                  problem_.getNumberOfObjectives());
} // getGD


/**
 * Returns the spread of solution set
 * @param solutionSet
 * @return The value of the hypervolume indicator
 */
double QualityIndicator::getSpread(SolutionSet * solutionSet) {
  return new Spread().spread(solutionSet.writeObjectivesToMatrix(),
                             trueParetoFront_.writeObjectivesToMatrix(),
                             problem_.getNumberOfObjectives());
} // getSpread


/**
 * Returns the epsilon indicator of solution set
 * @param solutionSet
 * @return The value of the hypervolume indicator
 */
double QualityIndicator::getEpsilon(SolutionSet * solutionSet);
return new Epsilon().epsilon(solutionSet.writeObjectivesToMatrix(),
                             trueParetoFront_.writeObjectivesToMatrix(),
                             problem_.getNumberOfObjectives());
} // getEpsilon
