//  StandardStudyExecution.h
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

#ifndef __STANDARD_STUDY_EXECUTION__
#define __STANDARD_STUDY_EXECUTION__

#include <ExperimentExecution.h>
#include <NSGAII_Settings.h>
#include <GDE3_Settings.h>
#include <SMPSO_Settings.h>
#include <string>

/**
 * Class implementing a typical experimental study. Five algorithms are
 * compared when solving the ZDT, DTLZ, and WFG benchmarks, and the hypervolume,
 * spread and additive epsilon indicators are used for performance assessment.
 */

class StandardStudyExecution : public ExperimentExecution {

public:
  Algorithm * algorithmSettings(string problemName, int algorithmId,
      int experimentIndividualId);

};

#endif /* __STANDARD_STUDY_EXECUTION__ */
