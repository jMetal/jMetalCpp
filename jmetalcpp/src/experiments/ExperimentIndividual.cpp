//  ExperimentIndividual.cpp
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

#include <ExperimentIndividual.h>

/**
 * Constructor
 */
ExperimentIndividual::ExperimentIndividual(int algorithmIndex, int problemIndex, int numRun) {
  algorithmIndex_ = algorithmIndex;
  problemIndex_ = problemIndex;
  numRun_ = numRun;
}

/**
 * Return the algorithm index atribute
 */
int ExperimentIndividual::getAlgorithmIndex() {
  return algorithmIndex_;
}

/**
 * Return the problem index atribute
 */
int ExperimentIndividual::getProblemIndex() {
  return problemIndex_;
}

/**
 * Return the algorithm index atribute
 */
int ExperimentIndividual::getNumRun() {
  return numRun_;
}
