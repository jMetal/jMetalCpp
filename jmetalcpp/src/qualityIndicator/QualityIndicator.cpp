//  QualityIndicator.cpp
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


#include <QualityIndicator.h>


/**
 * Constructor
 * @param paretoFrontFile
 */
QualityIndicator::QualityIndicator(Problem * problem,
																	 string paretoFrontFile) {
  problem_ = problem;
  dim_ = problem_->getNumberOfObjectives();
  utilities_ = new MetricsUtil();
  trueParetoFront_ = utilities_->readNonDominatedSolutionSet(paretoFrontFile);
  Hypervolume * hv = new Hypervolume();
  trueParetoFrontHypervolume_ = hv->hypervolume(trueParetoFront_->writeObjectivesToMatrix(),
      trueParetoFront_->writeObjectivesToMatrix(), problem_->getNumberOfObjectives());
  delete hv;
} // Constructor


/**
 * Destructor
 */
QualityIndicator::~QualityIndicator() {
  delete utilities_;
} // ~QualityIndicator


/**
 * Returns the hypervolume of solution set
 * @param solutionSet
 * @return The value of the hypervolume indicator
 */
double QualityIndicator::getHypervolume(SolutionSet * solutionSet) {
  Hypervolume * hv = new Hypervolume();
	double res =  hv->hypervolume(solutionSet->writeObjectivesToMatrix(),
	    trueParetoFront_->writeObjectivesToMatrix(),
	    dim_);
	delete hv;
	return res;
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
  InvertedGenerationalDistance * igd = new InvertedGenerationalDistance();
  double res = igd->invertedGenerationalDistance(
      solutionSet->writeObjectivesToMatrix(),
      trueParetoFront_->writeObjectivesToMatrix(),
      dim_);
  delete igd;
  return res;
} // getIGD


/**
 * Returns the generational distance of solution set
 * @param solutionSet
 * @return The value of the hypervolume indicator
 */
double QualityIndicator::getGD(SolutionSet * solutionSet) {
  GenerationalDistance * gd = new GenerationalDistance();
  double res = gd->generationalDistance(solutionSet->writeObjectivesToMatrix(),
      trueParetoFront_->writeObjectivesToMatrix(),
      dim_);
  delete gd;
  return res;
} // getGD


/**
 * Returns the spread of solution set
 * @param solutionSet
 * @return The value of the hypervolume indicator
 */
double QualityIndicator::getSpread(SolutionSet * solutionSet) {
  Spread * s = new Spread();
  double res = s->spread(solutionSet->writeObjectivesToMatrix(),
      trueParetoFront_->writeObjectivesToMatrix(),
      dim_);
  delete s;
  return res;
} // getSpread


/**
 * Returns the epsilon indicator of solution set
 * @param solutionSet
 * @return The value of the hypervolume indicator
 */
double QualityIndicator::getEpsilon(SolutionSet * solutionSet) {
  Epsilon * e = new Epsilon();
  double res = e->epsilon(solutionSet->writeObjectivesToMatrix(),
      trueParetoFront_->writeObjectivesToMatrix(),
      dim_);
  delete e;
  return res;
} // getEpsilon
