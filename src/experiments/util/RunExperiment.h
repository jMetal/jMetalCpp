//  RunExperiment.h
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

using namespace std;

class ExperimentExecution;

class RunExperiment {

public:

  ExperimentExecution * experiment_;
  int id_;
  map<string, void *> map_;
  int numberOfThreads_;
  int numberOfProblems_;

  RunExperiment(ExperimentExecution * experiment, map<string, void *> map, int id,
        int numberOfThreads, int numberOfProblems, int threadIndex,
        mutex * mtx);
  void run();

private:

  int threadIndex_;

  mutex * mutex_;

  string experimentName_;
  vector<string> algorithmNameList_; // List of the names of the algorithms to
                                     // be executed
  vector<string> problemList_; // List of problems to be solved
  string experimentBaseDirectory_; // Directory to store the results
  string latexDirectory_; // Directory to store the latex files
  string rDirectory_; // Directory to store the generated R scripts
  string paretoFrontDirectory_; // Directory containing the Pareto front files
  string outputParetoFrontFile_; // Name of the file containing the output
                                 // Pareto front
  string outputParetoSetFile_; // Name of the file containing the output
                               // Pareto set
  int independentRuns_; // Number of independent runs per algorithm
  // TODO: Settings[] algorithmSettings_; // Parameter settings of each algorithm

}; // RunExperiment

#endif /* __RUNEXPERIMENT__ */
