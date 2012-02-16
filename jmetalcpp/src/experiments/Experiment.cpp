//  Experiment.cpp
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


#include <Experiment.h>


void* executeRun(void* ctx) {
  RunExperiment* cptr = (RunExperiment*)ctx;
  cptr->run();
  pthread_exit(0);
} // executeRun


/**
 * Constructor
 *
 * Contains default settings
 */
Experiment::Experiment() {

  experimentName_ = "noName";

  //CHECK: problemsSettings_ = NULL;

  //CHECK: algorithmNameList_ = NULL;
  //CHECK: problemList_ = NULL;
  //CHECK: paretoFrontFile_ = NULL;
  //CHECK: indicatorList_ = NULL;

  experimentBaseDirectory_ = "";
  paretoFrontDirectory_ = "";
  latexDirectory_ = "latex";

  outputParetoFrontFile_ = "FUN";
  outputParetoSetFile_ = "VAR";

  algorithmSettings_ = NULL;
  //algorithm_ = NULL;

  independentRuns_ = 0;

  indicatorMinimize_["HV"] = false;
  indicatorMinimize_["EPSILON"] = true;
  indicatorMinimize_["SPREAD"] = true;
  indicatorMinimize_["GD"] = true;
  indicatorMinimize_["IGD"] = true;

} // Experiment


/**
 * Runs the experiment
 */
void Experiment::runExperiment(int numberOfThreads) {
  // Step 1: check experiment base directory
  checkExperimentDirectory();

  map_["name"] = &experimentName_;
  map_["experimentDirectory"] = &experimentBaseDirectory_;
  map_["algorithmNameList"] = &algorithmNameList_;
  map_["problemList"] = &problemList_;
  map_["indicatorList"] = &indicatorList_;
  map_["paretoFrontDirectory"] = &paretoFrontDirectory_;
  map_["paretoFrontFile"] = &paretoFrontFile_;
  map_["independentRuns"] = &independentRuns_;
  map_["outputParetoFrontFile"] = &outputParetoFrontFile_;
  map_["outputParetoSetFile"] = &outputParetoSetFile_;
  //CHECK: map_["problemsSettings"] = &problemsSettings_;

  SolutionSet ** resultFront = new SolutionSet*[algorithmNameList_.size()];

  if (problemList_.size() < numberOfThreads) {
    numberOfThreads = problemList_.size();
    cout << "Experiments: list of problems is shorter than the number of " <<
        "requested threads. Creating " << numberOfThreads << " threads." << endl;
  } // if
  else {
    cout << "Experiments: creating " << numberOfThreads << " threads." << endl;
  }

  int result;
  pthread_t * p = new pthread_t[numberOfThreads];
  RunExperiment ** experiments_ = new RunExperiment*[numberOfThreads];
  for (int i = 0; i < numberOfThreads; i++) {
    experiments_[i] = new RunExperiment(this, map_, i, numberOfThreads, problemList_.size());
    result = pthread_create(&p[i], NULL, executeRun, experiments_[i]);
    if (result != 0) {
      perror("ERROR CREATING THREADS");
      exit(-1) ;
    }
  }

  for (int i = 0; i < numberOfThreads; i++) {
    result = pthread_join(p[i], NULL) ;
    if (result != 0) {
      perror("ERROR MAKING THREAD JOIN");
      exit(-1) ;
    }
  }

} // runExperiment


/**
 * Runs the experiment
 */
void Experiment::runExperiment() {
  runExperiment(1);
} // runExperiment


void Experiment::checkExperimentDirectory() {
  int res = FileUtils::existsPath(experimentBaseDirectory_.c_str());
  switch (res) {
  case 0:
    cout << "Experiment directory does NOT exist. Creating" << endl;
    if (FileUtils::createDirectory(experimentBaseDirectory_) == -1) {
      cout << "Error creating directory" << endl;
      exit(-1);
    }
    break;
  case 1:
    cout << "Experiment directory exists." << endl;
    cout << "Experiment directory is a directory" << endl;
    break;
  case 2:
    cout << "Experiment directory exists." << endl;
    cout << "Experiment directory is not a directory. Deleting file and creating directory" << endl;
    //FIX Borrar fichero
    //experimentDirectory.delete();
    if (FileUtils::createDirectory(experimentBaseDirectory_) == -1) {
      cout << "Error creating directory" << endl;
      exit(-1);
    }
    break;
  case -1:
    cout << "Error checking experiment directory" << endl;
    exit(-1);
  }
} // checkExperimentDirectory


void Experiment::generateLatexTables() {
  //TODO
} // generateLatexTables


/**
 * Calculates statistical values from a vector of Double objects
 */
void Experiment::calculateStatistics(vector<int> vector, map<string, double> values) {
  //TODO
} // calculateStatistics


void Experiment::printHeaderLatexCommands(string fileName) {
  //TODO
} // printHeaderLatexCommands


void Experiment::printEndLatexCommands(string fileName) {
  //TODO
} //printEndLatexCommands


void Experiment::printMeanStdDev(string fileName, int indicator, double *** mean,
    double *** stdDev) {
  //TODO
} // printMeanStdDev


void Experiment::printMedianIQR(string fileName, int indicator, double *** median,
    double *** IQR) {
  //TODO
} // printMedianIQR


/**
 * Invoking the generateScripts method on the RBoxplot class
 */
void Experiment::generateRBoxplotScripts (int rows, int cols, vector<string> problems,
    string prefix, bool notch, Experiment * experiment) {
  RBoxplot::generateScripts(rows, cols, problems, prefix, notch, this);
} // generateRBoxplotScripts


/**
 * Invoking the generateScripts method on the RWilcoxon class
 */
void Experiment::generateRWilcoxonScripts(vector<string> problems, string prefix,
    Experiment * experiment) {
  RWilcoxon::generateScripts(problems, prefix, this);
} //generateRWilcoxonScripts
