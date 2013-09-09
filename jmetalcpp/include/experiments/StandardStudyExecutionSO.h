//  StandardStudyExecutionSO.h
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

#ifndef __STANDARD_STUDY_EXECUTION_SO__
#define __STANDARD_STUDY_EXECUTION_SO__

#include <ExperimentExecution.h>
#include <gGA_Settings.h>
#include <ssGA_Settings.h>
#include <DE_Settings.h>
#include <PSO_Settings.h>
#include <string>

/**
 * Class implementing a typical experimental study. Five algorithms are
 * compared when solving the ZDT, DTLZ, and WFG benchmarks, and the hypervolume,
 * spread and additive epsilon indicators are used for performance assessment.
 */

class StandardStudyExecutionSO : public ExperimentExecution {

public:
  Algorithm * algorithmSettings(string problemName, int algorithmId,
      int experimentIndividualId);

};

#endif /* __STANDARD_STUDY_EXECUTION_SO__ */
