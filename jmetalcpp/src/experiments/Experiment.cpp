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


/**
 * Abstract class representing jMetal experiments
 */


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

  map_["experimentDirectory"] = &experimentBaseDirectory_;
  map_["algorithmNameList"] = &algorithmNameList_;
  map_["problemList"] = &problemList_;
  map_["indicatorList"] = &indicatorList_;
  map_["paretoFrontDirectory"] = &paretoFrontDirectory_;
  map_["paretoFrontFile"] = &paretoFrontFile_;
  map_["independentRuns"] = &independentRuns_;
  map_["outputParetoFrontFile"] = &outputParetoFrontFile_;
  map_["outputParetoSetFile"] = &outputParetoSetFile_;
  // TODO: map_["problemsSettings"] = &problemsSettings_;

  SolutionSet ** resultFront = new SolutionSet*[algorithmNameList_.size()];

  if (problemList_.size() < numberOfThreads) {
    numberOfThreads = problemList_.size();
    cout << "Experiments: list of problems is shorter than the number of " <<
        "requested threads. Creating " << numberOfThreads << " threads." << endl;
  } // if
  else {
    cout << "Experiments: creating " << numberOfThreads << " threads." << endl;
  }
  //TODO: Continuar implementación
/*
  pthread_t[] p = new pthread_t[numberOfThreads];
  //Thread[] p = new RunExperiment[numberOfThreads];
  for (int i = 0; i < numberOfThreads; i++) {
    //p[i] = new Experiment(map_, i, numberOfThreads, problemList_.length);
    //p[i] = new RunExperiment(this, map_, i, numberOfThreads, problemList_.length);
    //p[i].start();
    //p[i] = new RunExperiment(this, map_, i, numberOfThreads, problemList_.length);
    //p[i].start();
  }

  try {
    for (int i = 0; i < numberOfThreads; i++) {
      p[i].join();
    }
  } catch (InterruptedException ex) {
    Logger.getLogger(Experiment.class.getName()).log(Level.SEVERE, null, ex);
  }
  */

} // runExperiment


/**
 * Runs the experiment
 */
void Experiment::runExperiment() {
  runExperiment(1);
} // runExperiment


void Experiment::checkExperimentDirectory() {
//TODO: Implementar checkExperimentDictory
//  File experimentDirectory;
//
//  experimentDirectory = new File(experimentBaseDirectory_);
//  if (experimentDirectory.exists()) {
//    System.out.println("Experiment directory exists");
//    if (experimentDirectory.isDirectory()) {
//      System.out.println("Experiment directory is a directory");
//    } else {
//      System.out.println("Experiment directory is not a directory. Deleting file and creating directory");
//    }
//    experimentDirectory.delete();
//    new File(experimentBaseDirectory_).mkdirs();
//  } // if
//  else {
//    System.out.println("Experiment directory does NOT exist. Creating");
//    new File(experimentBaseDirectory_).mkdirs();
//  } // else
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
  //TODO
} // generateRBoxplotScripts


/**
 * Invoking the generateScripts method on the RWilcoxon class
 */
void Experiment::generateRWilcoxonScripts(vector<string> problems, string prefix,
    Experiment * experiment) {
  //TODO
} //generateRWilcoxonScripts
