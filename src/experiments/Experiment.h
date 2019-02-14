//  Experiment.h
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//       Sérgio Vieira <sergiosvieira@gmail.com>
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

#ifndef __EXPERIMENT__
#define __EXPERIMENT__

#include "JMetalHeader.h"
#include <FileUtils.h>
#include <stdlib.h>
#include <stdio.h>

using namespace JMetal;

/**
 * Abstract class representing jMetal experiments
 */

class Experiment
{
public:
    std::string experimentName_;
    VectorOfString algorithmNameList_; // List of the names of the algorithms to
    // be executed
    VectorOfString problemList_; // List of problems to be solved
    std::string experimentBaseDirectory_; // Directory to store the results
    int independentRuns_; // Number of independent runs per algorithm
    bool isSingleObjective_; // If this experiment is a singleObjective one or not
    Experiment();
    void checkExperimentDirectory();
    void resetFile(std::string file);
};

#endif /* __EXPERIMENT__ */
