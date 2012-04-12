//  ExperimentExecution.h
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

#ifndef __EXPERIMENT_EXECUTION__
#define __EXPERIMENT_EXECUTION__

#include <vector>
#include <string>
#include <map>
#include <pthread.h>
#include <Settings.h>
#include <Algorithm.h>
#include <RunExperiment.h>
#include <Experiment.h>
#include <ExperimentIndividual.h>

using namespace std;

class ExperimentExecution : public Experiment {

private:

  map<string, void *> map_; // Map used to send experiment parameters to threads

public:

//  string experimentName_;
//  vector<string> algorithmNameList_; // List of the names of the algorithms to
//                                     // be executed
//  vector<string> problemList_; // List of problems to be solved
//  string experimentBaseDirectory_; // Directory to store the results
  string outputParetoFrontFile_; // Name of the file containing the output
                                 // Pareto front
  string outputParetoSetFile_; // Name of the file containing the output Pareto
                               // set
//  int independentRuns_; // Number of independent runs per algorithm
//  Settings ** algorithmSettings_; // Parameter settings of each algorithm
  //Algorithm ** algorithm_; // jMetal algorithms to be executed

  vector<ExperimentIndividual*> experimentIndividualList_;
  int experimentIndividualListIndex_;
  int experimentIndividualListSize_;

  //Properties [] problemsSettings_ ;

  ExperimentExecution();

  void runExperiment(int numberOfThreads);
  void runExperiment();
//  void checkExperimentDirectory();

  // FIX: ¿Qué hacer con esto?
//  virtual void algorithmSettings(string problemName, int problemId,
//      Algorithm ** algorithm) = 0;
//  virtual Algorithm * algorithmSettings(string problemName) = 0;

  virtual Algorithm * algorithmSettings(string problemName, int algorithmId) = 0;

};

#endif /* __EXPERIMENT_EXECUTION__ */
