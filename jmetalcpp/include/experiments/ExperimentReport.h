//  ExperimentReport.h
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

#ifndef __EXPERIMENT_REPORT__
#define __EXPERIMENT_REPORT__

#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <limits>
#include <iostream>
#include <sstream>
#include <stddef.h>
#include <fstream>
#include <FileUtils.h>
#include <RBoxplot.h>
#include <RWilcoxon.h>
#include <Statistics.h>
#include <Hypervolume.h>
#include <Spread.h>
#include <InvertedGenerationalDistance.h>
#include <Epsilon.h>
#include <Fitness.h>
#include <MetricsUtil.h>
#include <Experiment.h>

using namespace std;

/**
 * Abstract class generating jMetal experiments reports
 */

class ExperimentReport : public Experiment {

private:

  void generateReferenceFronts();
  void calculateStatistics(vector<double> vector_, map<string, double> * values);
  void printHeaderLatexCommands(string fileName);
  void printEndLatexCommands(string fileName);
  void printMeanStdDev(string fileName, int indicator, double*** mean,
      double*** stdDev);
  void printMedianIQR(string fileName, int indicator, double*** median,
      double*** IQR);

public:

  vector<string> paretoFrontFile_; // List of the files containing the pareto
                                   // fronts corresponding to the problems in
                                   // problemList_
  vector<string> indicatorList_; // List of the quality indicators to be applied
  string latexDirectory_; // Directory to store the latex files
  string paretoFrontDirectory_; // Directory containing the Pareto front files
  map<string, bool> indicatorMinimize_; // To indicate whether an indicator
                                        // is to be minimized. Hard-coded
                                        // in the constructor

  ExperimentReport();

  void generateQualityIndicators();
  void generateLatexTables();
  void generateRBoxplotScripts(int rows, int cols, vector<string> problems,
      string prefix, bool notch, ExperimentReport * experiment);
  void generateRWilcoxonScripts(vector<string> problems, string prefix,
      ExperimentReport * experiment);

}; // ExperimentReport

#endif /* __EXPERIMENT_REPORT__ */
