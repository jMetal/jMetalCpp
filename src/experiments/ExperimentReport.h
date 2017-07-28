//  ExperimentReport.h
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



/**
 * Abstract class generating jMetal experiments reports
 */

class ExperimentReport : public Experiment
{

private:

    void generateReferenceFronts();
    void calculateStatistics(std::vector<double> vector_,std::map<std::string, double> * values);
    void printHeaderLatexCommands(std::string fileName);
    void printEndLatexCommands(std::string fileName);
    void printMeanStdDev(std::string fileName, int indicator, double*** mean,
                         double*** stdDev);
    void printMedianIQR(std::string fileName, int indicator, double*** median,
                        double*** IQR);

public:

    std::vector<std::string> paretoFrontFile_; // List of the files containing the pareto
    // fronts corresponding to the problems in
    // problemList_
    std::vector<std::string> indicatorList_; // List of the quality indicators to be applied
    std::string latexDirectory_; // Directory to store the latex files
    std::string paretoFrontDirectory_; // Directory containing the Pareto front files
   std::map<std::string, bool> indicatorMinimize_; // To indicate whether an indicator
    // is to be minimized. Hard-coded
    // in the constructor

    ExperimentReport();

    void generateQualityIndicators();
    void generateLatexTables();
    void generateRBoxplotScripts(int rows, int cols, std::vector<std::string> problems,
                                 std::string prefix, bool notch, ExperimentReport * experiment);
    void generateRWilcoxonScripts(std::vector<std::string> problems, std::string prefix,
                                  ExperimentReport * experiment);

}; // ExperimentReport

#endif /* __EXPERIMENT_REPORT__ */
