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
  latexDirectory_ = experimentBaseDirectory_ + "/" + latexDirectory_;
  cout << "latex directory: " << latexDirectory_ << endl;

  vector<double> *** data = new vector<double>**[indicatorList_.size()];
  for (int indicator = 0; indicator < indicatorList_.size(); indicator++) {
    // A data vector per problem
    data[indicator] = new vector<double>*[problemList_.size()];

    for (int problem = 0; problem < problemList_.size(); problem++) {
      data[indicator][problem] = new vector<double>[algorithmNameList_.size()];

      for (int algorithm = 0; algorithm < algorithmNameList_.size(); algorithm++) {
        //data[indicator][problem][algorithm] = new Vector();

        string directory = experimentBaseDirectory_;
        directory += "/data/";
        directory += "/" + algorithmNameList_[algorithm];
        directory += "/" + problemList_[problem];
        directory += "/" + indicatorList_[indicator];

        // Read values from data files
        std::ifstream in(directory.c_str());
        if( !in ) {
          cout << "Error trying to read quality indicator file: " << directory << endl;
          exit(-1);
        } // if
        string aux;
        while( getline(in, aux ) ) {
          data[indicator][problem][algorithm].push_back(atof(aux.c_str()));
          cout << (atof(aux.c_str())) << endl;
        } // while
      } // for
    } // for
  } // for

  double *** mean;
  double *** median;
  double *** stdDeviation;
  double *** iqr;
  double *** max;
  double *** min;
  int *** numberOfValues;

  map<string, double> statValues;

  statValues["mean"] =  0.0;
  statValues["median"] = 0.0;
  statValues["stdDeviation"] = 0.0;
  statValues["iqr"] = 0.0;
  statValues["max"] = 0.0;
  statValues["min"] = 0.0;

  mean = new double**[indicatorList_.size()];
  median = new double**[indicatorList_.size()];
  stdDeviation = new double**[indicatorList_.size()];
  iqr = new double**[indicatorList_.size()];
  min = new double**[indicatorList_.size()];
  max = new double**[indicatorList_.size()];
  numberOfValues = new int**[indicatorList_.size()];

  for (int indicator = 0; indicator < indicatorList_.size(); indicator++) {
    // A data vector per problem
    mean[indicator] = new double*[problemList_.size()];
    median[indicator] = new double*[problemList_.size()];
    stdDeviation[indicator] = new double*[problemList_.size()];
    iqr[indicator] = new double*[problemList_.size()];
    min[indicator] = new double*[problemList_.size()];
    max[indicator] = new double*[problemList_.size()];
    numberOfValues[indicator] = new int*[problemList_.size()];

    for (int problem = 0; problem < problemList_.size(); problem++) {
      mean[indicator][problem] = new double[algorithmNameList_.size()];
      median[indicator][problem] = new double[algorithmNameList_.size()];
      stdDeviation[indicator][problem] = new double[algorithmNameList_.size()];
      iqr[indicator][problem] = new double[algorithmNameList_.size()];
      min[indicator][problem] = new double[algorithmNameList_.size()];
      max[indicator][problem] = new double[algorithmNameList_.size()];
      numberOfValues[indicator][problem] = new int[algorithmNameList_.size()];

      for (int algorithm = 0; algorithm < algorithmNameList_.size(); algorithm++) {
        sort(data[indicator][problem][algorithm].begin(),
            data[indicator][problem][algorithm].end());

        string directory = experimentBaseDirectory_;
        directory += "/" + algorithmNameList_[algorithm];
        directory += "/" + problemList_[problem];
        directory += "/" + indicatorList_[indicator];

        //cout << "----" << directory << "-----" << endl;
        //calculateStatistics(data[indicator][problem][algorithm], meanV, medianV, minV, maxV, stdDeviationV, iqrV);
        calculateStatistics(data[indicator][problem][algorithm], statValues);
        /*
        cout << "Mean: " << statValues.get("mean") << endl;
        cout << "Median : " << statValues.get("median") << endl;
        cout << "Std : " << statValues.get("stdDeviation") << endl;
        cout << "IQR : " << statValues.get("iqr") << endl;
        cout << "Min : " << statValues.get("min") << endl;
        cout << "Max : " << statValues.get("max") << endl;
        cout << "N_values: " << data[indicator][problem][algorithm].size() << endl;
         */
        mean[indicator][problem][algorithm] = statValues["mean"];
        median[indicator][problem][algorithm] = statValues["median"];
        stdDeviation[indicator][problem][algorithm] = statValues["stdDeviation"];
        iqr[indicator][problem][algorithm] = statValues["iqr"];
        min[indicator][problem][algorithm] = statValues["min"];
        max[indicator][problem][algorithm] = statValues["max"];
        numberOfValues[indicator][problem][algorithm] = data[indicator][problem][algorithm].size();
      }
    }
  }

  if (FileUtils::existsPath(latexDirectory_.c_str()) != 1) {
    if (FileUtils::createDirectory(latexDirectory_) == -1) {
      cout << "Error creating directory: " << latexDirectory_ << endl;
      exit(-1);
    } // if
    cout << "Creating " << latexDirectory_ << " directory" << endl;
  } // if
  cout << "Experiment name: " << experimentName_ << endl;
  string latexFile = latexDirectory_ + "/" + experimentName_ + ".tex";
  printHeaderLatexCommands(latexFile);
  for (int i = 0; i < indicatorList_.size(); i++) {
    printMeanStdDev(latexFile, i, mean, stdDeviation);
    printMedianIQR(latexFile, i, median, iqr);
  } // for
  printEndLatexCommands(latexFile);
} // generateLatexTables


/**
 * Calculates statistical values from a vector of Double objects
 */
void Experiment::calculateStatistics(vector<double> vector, map<string, double> values) {
  if (vector.size() > 0) {
    double sum, minimum, maximum, sqsum, min, max, median, mean, iqr, stdDeviation;

    sqsum = 0.0;
    sum = 0.0;
    min = 1E300;
    max = -1E300;
    median = 0;

    for (int i = 0; i < vector.size(); i++) {
      double val = vector[i];
      sqsum += val * val;
      sum += val;
      if (val < min) {
        min = val;
      }
      if (val > max) {
        max = val;
      } // if
    } // for

    // Mean
    mean = sum / vector.size();

    // Standard deviation
    if (sqsum / vector.size() - mean * mean < 0.0) {
      stdDeviation = 0.0;
    } else {
      stdDeviation = sqrt(sqsum / vector.size() - mean * mean);
    } // if

    values["mean"] = mean;
    values["median"] = Statistics::calculateMedian(vector, 0, vector.size() - 1);
    values["iqr"] = Statistics::calculateIQR(vector);
    values["stdDeviation"] = stdDeviation;
    values["min"] = min;
    values["max"] = max;
  } // if
  else {
    values["mean"] = std::numeric_limits<double>::quiet_NaN();
    values["median"] = std::numeric_limits<double>::quiet_NaN();
    values["iqr"] = std::numeric_limits<double>::quiet_NaN();
    values["stdDeviation"] = std::numeric_limits<double>::quiet_NaN();
    values["min"] = std::numeric_limits<double>::quiet_NaN();
    values["max"] = std::numeric_limits<double>::quiet_NaN();
  } // else
} // calculateStatistics


void Experiment::printHeaderLatexCommands(string fileName) {
  std::ofstream out(fileName.c_str());
  out << "\\documentclass{article}" << endl;
  out << "\\title{" << experimentName_ << "}" << endl;
  out << "\\usepackage{colortbl}" << endl;
  out << "\\usepackage[table*]{xcolor}" << endl;
  out << "\\xdefinecolor{gray95}{gray}{0.65}" << endl;
  out << "\\xdefinecolor{gray25}{gray}{0.8}" << endl;
  out << "\\author{}" << endl;
  out << "\\begin{document}" << endl;
  out << "\\maketitle" << endl;
  out << "\\section{Tables}" << endl;
  out.close();
} // printHeaderLatexCommands


void Experiment::printEndLatexCommands(string fileName) {
  std::ofstream out(fileName.c_str());
  out << "\\end{document}" << endl;
  out.close();
} //printEndLatexCommands


void Experiment::printMeanStdDev(string fileName, int indicator, double *** mean,
    double *** stdDev) {
  std::ofstream out(fileName.c_str());
  out << "\\" << endl;
  out << "\\begin{table}" << endl;
  out << "\\caption{" << indicatorList_[indicator] << ". Mean and standard deviation}" << endl;
  out << "\\label{table:mean." << indicatorList_[indicator] << "}" << endl;
  out << "\\centering" << endl;
  out << "\\begin{scriptsize}" << endl;
  out << "\\begin{tabular}{l";

  // calculate the number of columns
  for (int i = 0; i < algorithmNameList_.size(); i++) {
    out << "l";
  }
  out << "}" << endl;

  out << "\\hline";
  // write table head
  for (int i = -1; i < algorithmNameList_.size(); i++) {
    if (i == -1) {
      out << " & ";
    } else if (i == (algorithmNameList_.size() - 1)) {
      out << " " << algorithmNameList_[i] << "\\\\" << endl;
    } else {
      out << "" << algorithmNameList_[i] << " & ";
    }
  }
  out << "\\hline" << endl;

  char m[20], s[20];
  // write lines
  for (int i = 0; i < problemList_.size(); i++) {
    // find the best value and second best value
    double bestValue       ;
    double bestValueIQR    ;
    double secondBestValue ;
    double secondBestValueIQR ;
    int bestIndex = -1 ;
    int secondBestIndex = -1 ;
    if (indicatorMinimize_[indicatorList_[indicator]] == true) {// minimize by default
      bestValue = std::numeric_limits<double>::max();
      bestValueIQR = std::numeric_limits<double>::max();
      secondBestValue = std::numeric_limits<double>::max();
      secondBestValueIQR = std::numeric_limits<double>::max();
      for (int j = 0; j < (algorithmNameList_.size()); j++) {
        if ((mean[indicator][i][j] < bestValue) ||
                ((mean[indicator][i][j] == bestValue) && (stdDev[indicator][i][j] < bestValueIQR))) {
          secondBestIndex = bestIndex ;
          secondBestValue = bestValue ;
          secondBestValueIQR = bestValueIQR ;
          bestValue = mean[indicator][i][j];
          bestValueIQR = stdDev[indicator][i][j];
          bestIndex = j;
        }
        else if ((mean[indicator][i][j] < secondBestValue) ||
            ((mean[indicator][i][j] == secondBestValue) && (stdDev[indicator][i][j] < secondBestValueIQR))) {
          secondBestIndex = j ;
          secondBestValue = mean[indicator][i][j] ;
          secondBestValueIQR = stdDev[indicator][i][j] ;
        } // else if
      }
    } // if
    else { // indicator to maximize e.g., the HV
      bestValue = std::numeric_limits<double>::min();
      bestValueIQR = std::numeric_limits<double>::min();
      secondBestValue = std::numeric_limits<double>::min();
      secondBestValueIQR = std::numeric_limits<double>::min();
      for (int j = 0; j < (algorithmNameList_.size()); j++) {
        if ((mean[indicator][i][j] > bestValue) ||
                ((mean[indicator][i][j] == bestValue) && (stdDev[indicator][i][j] < bestValueIQR))) {
          secondBestIndex = bestIndex ;
          secondBestValue = bestValue ;
          secondBestValueIQR = bestValueIQR ;
          bestValue = mean[indicator][i][j];
          bestValueIQR = stdDev[indicator][i][j];
          bestIndex = j;
        }
        else if ((mean[indicator][i][j] > secondBestValue) ||
            ((mean[indicator][i][j] == secondBestValue) && (stdDev[indicator][i][j] < secondBestValueIQR))) {
          secondBestIndex = j ;
          secondBestValue = mean[indicator][i][j] ;
          secondBestValueIQR = stdDev[indicator][i][j] ;
        } // else if
      } // for
    } // else

    out << problemList_[i] << " & ";
    for (int j = 0; j < (algorithmNameList_.size() - 1); j++) {
      if (j == bestIndex) {
        out << "\\cellcolor{gray95}";
      }
      if (j == secondBestIndex) {
        out << "\\cellcolor{gray25}";
      }

      sprintf(m, "%10.2e", mean[indicator][i][j]);
      sprintf(s, "%8.1e", stdDev[indicator][i][j]);
      out << "$" << m << "_{" << s << "}$ & ";
    }
    if (bestIndex == (algorithmNameList_.size() - 1)) {
      out << "\\cellcolor{gray95}";
    }
    sprintf(m, "%10.2e", mean[indicator][i][algorithmNameList_.size() - 1]);
    sprintf(s, "%8.1e", stdDev[indicator][i][algorithmNameList_.size() - 1]);
    out << "$" << m << "_{" << s << "}$ \\\\" << endl;
  } // for
  //out << "" + mean[0][problemList_.length-1][algorithmNameList_.length-1] + "\\\\"+ "\n" ) ;

  out << "\\hline" << endl;
  out << "\\end{tabular}" << endl;
  out << "\\end{scriptsize}" << endl;
  out << "\\end{table}" << endl;
  out.close();
} // printMeanStdDev


void Experiment::printMedianIQR(string fileName, int indicator, double *** median,
    double *** IQR) {
  std::ofstream out(fileName.c_str());
  out << "\\" << endl;
  out << "\\begin{table}" << endl;
  out << "\\caption{" << indicatorList_[indicator] << ". Median and IQR}" << endl;
  out << "\\label{table:median." << indicatorList_[indicator] << "}" << endl;
  out << "\\begin{scriptsize}" << endl;
  out << "\\centering" << endl;
  out << "\\begin{tabular}{l";

  // calculate the number of columns
  for (int i = 0; i < algorithmNameList_.size(); i++) {
    out << "l";
  }
  out << "}" << endl;

  out << "\\hline";
  // write table head
  for (int i = -1; i < algorithmNameList_.size(); i++) {
    if (i == -1) {
      out << " & ";
    } else if (i == (algorithmNameList_.size() - 1)) {
      out << " " << algorithmNameList_[i] << "\\\\" << endl;
    } else {
      out << "" << algorithmNameList_[i] << " & ";
    }
  }
  out << "\\hline" << endl;

  char m[20], s[20];
  // write lines
  for (int i = 0; i < problemList_.size(); i++) {
    // find the best value and second best value
    double bestValue       ;
    double bestValueIQR    ;
    double secondBestValue ;
    double secondBestValueIQR ;
    int bestIndex = -1 ;
    int secondBestIndex = -1 ;
    if (indicatorMinimize_[indicatorList_[indicator]] == true) {// minimize by default
      bestValue = std::numeric_limits<double>::max();
      bestValueIQR = std::numeric_limits<double>::max();
      secondBestValue = std::numeric_limits<double>::max();
      secondBestValueIQR = std::numeric_limits<double>::max();
      for (int j = 0; j < (algorithmNameList_.size()); j++) {
        if ((median[indicator][i][j] < bestValue) ||
            ((median[indicator][i][j] == bestValue) && (IQR[indicator][i][j] < bestValueIQR))) {
          secondBestIndex = bestIndex ;
          secondBestValue = bestValue ;
          secondBestValueIQR = bestValueIQR ;
          bestValue = median[indicator][i][j];
          bestValueIQR = IQR[indicator][i][j];
          bestIndex = j;
        }
        else if ((median[indicator][i][j] < secondBestValue) ||
            ((median[indicator][i][j] == secondBestValue) && (IQR[indicator][i][j] < secondBestValueIQR))) {
          secondBestIndex = j ;
          secondBestValue = median[indicator][i][j] ;
          secondBestValueIQR = IQR[indicator][i][j] ;
        } // else if
      } // for
    } // if
    else { // indicator to maximize e.g., the HV
      bestValue = std::numeric_limits<double>::min();
      bestValueIQR = std::numeric_limits<double>::min();
      secondBestValue = std::numeric_limits<double>::min();
      secondBestValueIQR = std::numeric_limits<double>::min();
      for (int j = 0; j < (algorithmNameList_.size()); j++) {
        if ((median[indicator][i][j] > bestValue) ||
            ((median[indicator][i][j] == bestValue) && (IQR[indicator][i][j] < bestValueIQR))) {
          secondBestIndex = bestIndex ;
          secondBestValue = bestValue ;
          secondBestValueIQR = bestValueIQR ;
          bestValue = median[indicator][i][j];
          bestValueIQR = IQR[indicator][i][j];
          bestIndex = j;
        }
        else if ((median[indicator][i][j] > secondBestValue) ||
            ((median[indicator][i][j] == secondBestValue) && (IQR[indicator][i][j] < secondBestValueIQR))) {
          secondBestIndex = j ;
          secondBestValue = median[indicator][i][j] ;
          secondBestValueIQR = IQR[indicator][i][j] ;
        } // else if
      } // for
    } // else


    out << problemList_[i] + " & ";
    for (int j = 0; j < (algorithmNameList_.size() - 1); j++) {
      if (j == bestIndex) {
        out << "\\cellcolor{gray95}";
      }
      if (j == secondBestIndex) {
        out << "\\cellcolor{gray25}";
      }
      sprintf(m, "%10.2e", median[indicator][i][j]);
      sprintf(s, "%8.1e", IQR[indicator][i][j]);
      out << "$" << m << "_{" << s << "}$ & ";
    }
    if (bestIndex == (algorithmNameList_.size() - 1)) {
      out << "\\cellcolor{gray95}";
    }
    sprintf(m, "%10.2e", median[indicator][i][algorithmNameList_.size() - 1]);
    sprintf(s, "%8.1e", IQR[indicator][i][algorithmNameList_.size() - 1]);
    out << "$" << m << "_{" << s << "}$ \\\\" << endl;
  } // for
  //out << "" << mean[0][problemList_.size()-1][algorithmNameList_.size()-1] << "\\\\" << endl;

  out << "\\hline" << endl;
  out << "\\end{tabular}" << endl;
  out << "\\end{scriptsize}" << endl;
  out << "\\end{table}" << endl;
  out.close();
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
