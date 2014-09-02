//  ExperimentIndividual.h
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

#ifndef __EXPERIMENT_INDIVIDUAL__
#define __EXPERIMENT_INDIVIDUAL__

class ExperimentIndividual {

private:
  int algorithmIndex_;
  int problemIndex_;
  int numRun_;

public:
  ExperimentIndividual(int algorithmIndex, int problemIndex, int numRun);
  int getAlgorithmIndex();
  int getProblemIndex();
  int getNumRun();

}; // ExperimentIndividual

#endif /* __EXPERIMENT_INDIVIDUAL__ */
