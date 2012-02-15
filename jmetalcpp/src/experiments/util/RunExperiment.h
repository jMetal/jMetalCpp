//  RunExperiment.h
//
//  Author:
//       Esteban López <esteban@lcc.uma.es>
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

#ifdef WIN32
 #define WINDOWS
#elif WIN64
 #define WINDOWS
#endif

#ifndef __RUNEXPERIMENT__
#define __RUNEXPERIMENT__

#include <string>
#include <Experiment.h>
#include <sys/stat.h>

#ifdef WINDOWS
  #include <dir.h>
#endif

using namespace std;

class RunExperiment {

public:

  Experiment * experiment_;
  int id_;
  map<string, void *> map_;
  int numberOfThreads_;
  int numberOfProblems_;

  RunExperiment(Experiment * experiment, map<string, void *> map, int id,
        int numberOfThreads, int numberOfProblems);
  void run();

private:

  int first_;
  int last_;

  string experimentName_;
  vector<string> algorithmNameList_; // List of the names of the algorithms to
                                     // be executed
  vector<string> problemList_; // List of problems to be solved
  vector<string> paretoFrontFile_; // List of the files containing the pareto
                                   // fronts corresponding to the problems in
                                   // problemList_
  vector<string> indicatorList_; // List of the quality indicators to be applied
  string experimentBaseDirectory_; // Directory to store the results
  string latexDirectory_; // Directory to store the latex files
  string rDirectory_; // Directory to store the generated R scripts
  string paretoFrontDirectory_; // Directory containing the Pareto front files
  string outputParetoFrontFile_; // Name of the file containing the output
                                 // Pareto front
  string outputParetoSetFile_; // Name of the file containing the output
                               // Pareto set
  int independentRuns_; // Number of independent runs per algorithm
  // TODO: Settings[] algorithmSettings_; // Paremeter settings of each algorithm

  int existsPath(const char* path);
  void createDirectory(string path);

}; // RunExperiment

#endif /* __RUNEXPERIMENT__ */
