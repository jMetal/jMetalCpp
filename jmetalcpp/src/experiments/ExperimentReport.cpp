//  ExperimentReport.cpp
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


#include <ExperimentReport.h>


/**
 * Constructor
 *
 * Contains default settings
 */
ExperimentReport::ExperimentReport() {

  experimentName_ = "noName";

  experimentBaseDirectory_ = "";
  paretoFrontDirectory_ = "";
  latexDirectory_ = "latex";

  independentRuns_ = 0;

  indicatorMinimize_["HV"] = false;
  indicatorMinimize_["EPSILON"] = true;
  indicatorMinimize_["SPREAD"] = true;
  indicatorMinimize_["GD"] = true;
  indicatorMinimize_["IGD"] = true;
  indicatorMinimize_["FIT"] = true;

  isSingleObjective_ = false;

} // ExperimentReport


void ExperimentReport::generateQualityIndicators() {


  if ((!isSingleObjective_) && (paretoFrontDirectory_.empty())) {
    generateReferenceFronts();
  }

  // TODO: Check if it is possible to use QualityIndicator class instead each independent class.
  // Problem: knowing number of objectives of each problem

  if (indicatorList_.size() > 0) {

    cout << "PF file: " << paretoFrontDirectory_ << endl;

    for (int algorithmIndex=0; algorithmIndex<algorithmNameList_.size(); algorithmIndex++) {

      string algorithmDirectory;
      algorithmDirectory = experimentBaseDirectory_ + "/data/" + algorithmNameList_[algorithmIndex] + "/";

      for (int problemIndex=0; problemIndex<problemList_.size(); problemIndex++) {

        string problemDirectory = algorithmDirectory + problemList_[problemIndex];
        string paretoFrontPath;

        if (!isSingleObjective_) {

          if (paretoFrontDirectory_.empty()) {

            string referenceFrontDirectory = experimentBaseDirectory_ + "/referenceFronts";
            paretoFrontPath = referenceFrontDirectory + "/" + problemList_[problemIndex] + ".rf";

          } else {
            paretoFrontPath = paretoFrontDirectory_ + "/" + paretoFrontFile_[problemIndex];
          } // if

        } // if

        for (int indicatorIndex = 0; indicatorIndex < indicatorList_.size(); indicatorIndex++) {


          resetFile(problemDirectory + "/" + indicatorList_[indicatorIndex]);

          if (indicatorList_[indicatorIndex].compare("FIT")==0) {

            string solutionFrontFile = problemDirectory + "/FUN";
            string qualityIndicatorFile = problemDirectory;

            Fitness * indicators = new Fitness();
            vector< vector<double> > solutionFront =
                indicators->utils_->readFront(solutionFrontFile);
            qualityIndicatorFile = qualityIndicatorFile + "/FIT";
            indicators->fitness(solutionFront, qualityIndicatorFile);
            delete indicators;

          } else {

            for (int numRun=0; numRun<independentRuns_; numRun++) {

              stringstream outputParetoFrontFilePath;
              outputParetoFrontFilePath << problemDirectory << "/FUN_" << numRun;
              string solutionFrontFile = outputParetoFrontFilePath.str();
              string qualityIndicatorFile = problemDirectory;
              double value;

              cout << "ExperimentReport: Quality indicator: " << indicatorList_[indicatorIndex] << endl;

              if (indicatorList_[indicatorIndex].compare("HV")==0) {

                Hypervolume * indicators = new Hypervolume();
                vector< vector<double> > solutionFront =
                    indicators->utils_->readFront(solutionFrontFile);
                vector< vector<double> > trueFront =
                    indicators->utils_->readFront(paretoFrontPath);
                value = indicators->hypervolume(solutionFront, trueFront, trueFront[0].size());
                delete indicators;
                qualityIndicatorFile = qualityIndicatorFile + "/HV";
              }
              if (indicatorList_[indicatorIndex].compare("SPREAD")==0) {
                Spread * indicators = new Spread();
                vector< vector<double> > solutionFront =
                    indicators->utils_->readFront(solutionFrontFile);
                vector< vector<double> > trueFront =
                    indicators->utils_->readFront(paretoFrontPath);
                value = indicators->spread(solutionFront, trueFront, trueFront[0].size());
                delete indicators;
                qualityIndicatorFile = qualityIndicatorFile + "/SPREAD";
              }
              if (indicatorList_[indicatorIndex].compare("IGD")==0) {
                InvertedGenerationalDistance * indicators = new InvertedGenerationalDistance();
                vector< vector<double> > solutionFront =
                    indicators->utils_->readFront(solutionFrontFile);
                vector< vector<double> > trueFront =
                    indicators->utils_->readFront(paretoFrontPath);
                value = indicators->invertedGenerationalDistance(solutionFront, trueFront, trueFront[0].size());
                delete indicators;
                qualityIndicatorFile = qualityIndicatorFile + "/IGD";
              }
              if (indicatorList_[indicatorIndex].compare("EPSILON")==0) {
                Epsilon * indicators = new Epsilon();
                vector< vector<double> > solutionFront =
                    indicators->utils_->readFront(solutionFrontFile);
                vector< vector<double> > trueFront =
                    indicators->utils_->readFront(paretoFrontPath);
                value = indicators->epsilon(solutionFront, trueFront, trueFront[0].size());
                delete indicators;
                qualityIndicatorFile = qualityIndicatorFile + "/EPSILON";
              }

              cout << "ExperimentReport: Quality indicator file: " << qualityIndicatorFile << endl;

              if (qualityIndicatorFile.compare(problemDirectory)!=0) {
                std::fstream out(qualityIndicatorFile.c_str(),
                    std::ios::out | std::ios::app);
                out << value << endl;
                out.close();
              } // if

            } // for

          } // if
        } // for
      } // for
    } // for
  } // if
} // generateQualityIndicators


void ExperimentReport::generateReferenceFronts() {

  string referenceFrontDirectory = experimentBaseDirectory_ + "/referenceFronts";

  if (FileUtils::existsPath(referenceFrontDirectory.c_str()) != 1) {
    FileUtils::createDirectory(referenceFrontDirectory);
    cout << "Creating " << referenceFrontDirectory << endl;
  }

  for (int problemIndex=0; problemIndex<problemList_.size(); problemIndex++) {

    string paretoFrontPath = referenceFrontDirectory + "/" + problemList_[problemIndex] + ".rf";

    MetricsUtil * metricsUtils = new MetricsUtil();
    NonDominatedSolutionList * solutionSet = new NonDominatedSolutionList();
    for (int algorithmIndex=0; algorithmIndex<algorithmNameList_.size(); algorithmIndex++) {

      string problemDirectory = experimentBaseDirectory_ + "/data/" + algorithmNameList_[algorithmIndex] +
          "/" + problemList_[problemIndex];

      for (int numRun=0; numRun<independentRuns_; numRun++) {


        stringstream outputParetoFrontFilePath;
        outputParetoFrontFilePath << problemDirectory << "/FUN_" << numRun;
        string solutionFrontFile = outputParetoFrontFilePath.str();
        string qualityIndicatorFile = problemDirectory;
        double value;

        metricsUtils->readNonDominatedSolutionSet(solutionFrontFile, solutionSet);

      } // for
    } // for

    solutionSet->printObjectivesToFile(paretoFrontPath);

    delete solutionSet;
    delete metricsUtils;

  } // for

} // generateQualityIndicators


void ExperimentReport::generateLatexTables() {
  latexDirectory_ = experimentBaseDirectory_ + "/" + latexDirectory_;
  cout << "latex directory: " << latexDirectory_ << endl;

  vector<double> *** data = new vector<double>**[indicatorList_.size()];
  for (int indicator = 0; indicator < indicatorList_.size(); indicator++) {
    // A data vector per problem
    data[indicator] = new vector<double>*[problemList_.size()];

    for (int problem = 0; problem < problemList_.size(); problem++) {
      data[indicator][problem] = new vector<double>[algorithmNameList_.size()];

      for (int algorithm = 0; algorithm < algorithmNameList_.size(); algorithm++) {

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
        calculateStatistics(data[indicator][problem][algorithm], &statValues);

        /*
        cout << "Mean: " << statValues["mean"] << endl;
        cout << "Median : " << statValues["median"] << endl;
        cout << "Std : " << statValues["stdDeviation"] << endl;
        cout << "IQR : " << statValues["iqr"] << endl;
        cout << "Min : " << statValues["min"] << endl;
        cout << "Max : " << statValues["max"] << endl;
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

  // Free memory:
  for (int indicator = 0; indicator < indicatorList_.size(); indicator++) {
    for (int problem = 0; problem < problemList_.size(); problem++) {
      delete [] data[indicator][problem];
      delete [] mean[indicator][problem];
      delete [] median[indicator][problem];
      delete [] stdDeviation[indicator][problem];
      delete [] iqr[indicator][problem];
      delete [] max[indicator][problem];
      delete [] min[indicator][problem];
      delete [] numberOfValues[indicator][problem];

    }
    delete [] data[indicator];
    delete [] mean[indicator];
    delete [] median[indicator];
    delete [] stdDeviation[indicator];
    delete [] iqr[indicator];
    delete [] max[indicator];
    delete [] min[indicator];
    delete [] numberOfValues[indicator];
  }
  delete [] data;
  delete [] mean;
  delete [] median;
  delete [] stdDeviation;
  delete [] iqr;
  delete [] max;
  delete [] min;
  delete [] numberOfValues;

} // generateLatexTables


/**
 * Calculates statistical values from a vector of Double objects
 */
void ExperimentReport::calculateStatistics(vector<double> vector, map<string, double> * values) {
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

    (*values)["mean"] = mean;
    (*values)["median"] = Statistics::calculateMedian(vector, 0, vector.size() - 1);
    (*values)["iqr"] = Statistics::calculateIQR(vector);
    (*values)["stdDeviation"] = stdDeviation;
    (*values)["min"] = min;
    (*values)["max"] = max;
  } // if
  else {
    (*values)["mean"] = std::numeric_limits<double>::quiet_NaN();
    (*values)["median"] = std::numeric_limits<double>::quiet_NaN();
    (*values)["iqr"] = std::numeric_limits<double>::quiet_NaN();
    (*values)["stdDeviation"] = std::numeric_limits<double>::quiet_NaN();
    (*values)["min"] = std::numeric_limits<double>::quiet_NaN();
    (*values)["max"] = std::numeric_limits<double>::quiet_NaN();
  } // else
} // calculateStatistics


void ExperimentReport::printHeaderLatexCommands(string fileName) {
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


void ExperimentReport::printEndLatexCommands(string fileName) {
  std::fstream out(fileName.c_str(), std::ios::out | std::ios::app);
  out << "\\end{document}" << endl;
  out.close();
} //printEndLatexCommands


void ExperimentReport::printMeanStdDev(string fileName, int indicator, double *** mean,
    double *** stdDev) {
  std::fstream out(fileName.c_str(), std::ios::out | std::ios::app);
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
  for (int i = -1; i < (int) (algorithmNameList_.size()); i++) {
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
      bestValue = -std::numeric_limits<double>::max();
      bestValueIQR = -std::numeric_limits<double>::max();
      secondBestValue = -std::numeric_limits<double>::max();
      secondBestValueIQR = -std::numeric_limits<double>::max();
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


void ExperimentReport::printMedianIQR(string fileName, int indicator, double *** median,
    double *** IQR) {
  std::fstream out(fileName.c_str(), std::ios::out | std::ios::app);
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
  for (int i = -1; i < (int) (algorithmNameList_.size()); i++) {
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
      bestValue = -std::numeric_limits<double>::max();
      bestValueIQR = -std::numeric_limits<double>::max();
      secondBestValue = -std::numeric_limits<double>::max();
      secondBestValueIQR = -std::numeric_limits<double>::max();
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
void ExperimentReport::generateRBoxplotScripts (int rows, int cols, vector<string> problems,
    string prefix, bool notch, ExperimentReport * experiment) {
  RBoxplot::generateScripts(rows, cols, problems, prefix, notch, this);
} // generateRBoxplotScripts


/**
 * Invoking the generateScripts method on the RWilcoxon class
 */
void ExperimentReport::generateRWilcoxonScripts(vector<string> problems, string prefix,
    ExperimentReport * experiment) {
  RWilcoxon::generateScripts(problems, prefix, this);
} //generateRWilcoxonScripts
