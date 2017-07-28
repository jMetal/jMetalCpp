//  RunExperiment.h
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

#ifndef __RUNEXPERIMENT__
#define __RUNEXPERIMENT__

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <stddef.h>
#include <sys/stat.h>
#include <Algorithm.h>
#include <ExperimentExecution.h>
#include <FileUtils.h>
#include <Problem.h>
#include <SolutionSet.h>



class ExperimentExecution;

class RunExperiment
{

public:

    ExperimentExecution * experiment_;
    int id_;
   std::map<std::string, void *> map_;
    int numberOfThreads_;
    int numberOfProblems_;

    RunExperiment(ExperimentExecution * experiment,std::map<std::string, void *> map, int id,
                  int numberOfThreads, int numberOfProblems, int threadIndex,
                  mutex * mtx);
    void run();

private:

    int threadIndex_;

    mutex * mutex_;

    std::string experimentName_;
    std::vector<std::string> algorithmNameList_; // List of the names of the algorithms to
    // be executed
    std::vector<std::string> problemList_; // List of problems to be solved
    std::string experimentBaseDirectory_; // Directory to store the results
    std::string latexDirectory_; // Directory to store the latex files
    std::string rDirectory_; // Directory to store the generated R scripts
    std::string paretoFrontDirectory_; // Directory containing the Pareto front files
    std::string outputParetoFrontFile_; // Name of the file containing the output
    // Pareto front
    std::string outputParetoSetFile_; // Name of the file containing the output
    // Pareto set
    int independentRuns_; // Number of independent runs per algorithm
    // TODO: Settings[] algorithmSettings_; // Parameter settings of each algorithm

}; // RunExperiment

#endif /* __RUNEXPERIMENT__ */
