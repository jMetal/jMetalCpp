//  Experiment.h
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

#ifndef __EXPERIMENT__
#define __EXPERIMENT__

#include <string>
#include <map>
#include <vector>
#include <pthread.h>
#include <Algorithm.h>
#include <Settings.h>
#include <RunExperiment.h>
#include <FileUtils.h>
#include <RBoxplot.h>
#include <RWilcoxon.h>

using namespace std;


template<typename T, size_t N>
T * end(T (&ra)[N]) {
    return ra + N;
}


/**
 * Abstract class representing jMetal experiments
 */

class Experiment {

private:

  map<string, void *> map_; // Map used to send experiment parameters to threads

  void calculateStatistics(vector<int> vector_, map<string, double> values);
  void printHeaderLatexCommands(string fileName);
  void printEndLatexCommands(string fileName);
  void printMeanStdDev(string fileName, int indicator, double*** mean,
      double*** stdDev);
  void printMedianIQR(string fileName, int indicator, double*** median,
      double*** IQR);

public:

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
  string paretoFrontDirectory_; // Directory containing the Pareto front files
  string outputParetoFrontFile_; // Name of the file containing the output
                                 // Pareto front
  string outputParetoSetFile_; // Name of the file containing the output Pareto
                               // set
  int independentRuns_; // Number of independent runs per algorithm
  Settings ** algorithmSettings_; // Paremeter settings of each algorithm
  //Algorithm ** algorithm_; // jMetal algorithms to be executed
  map<string, bool> indicatorMinimize_; // To indicate whether an indicator
                                        // is to be minimized. Hard-coded
                                        // in the constructor

  //Properties [] problemsSettings_ ;

  Experiment();

  void runExperiment(int numberOfThreads);
  void runExperiment();
  void checkExperimentDirectory();
  void generateLatexTables();
  void generateRBoxplotScripts(int rows, int cols, vector<string> problems,
      string prefix, bool notch, Experiment * experiment);
  void generateRWilcoxonScripts(vector<string> problems, string prefix,
      Experiment * experiment);

  virtual void algorithmSettings(string problemName, int problemId,
      Algorithm ** algorithm) = 0;

};

#endif /* __EXPERIMENT__ */
