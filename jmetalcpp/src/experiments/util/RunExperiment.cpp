//  RunExperiment.cpp
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


#include <RunExperiment.h>


/**
 * Class implementing the steps to run an experiment
 */


/**
 * Constructor
 */
RunExperiment::RunExperiment(Experiment * experiment, map<string, void *> map,
    int id, int numberOfThreads, int numberOfProblems) {

  experiment_ = experiment;
  id_ = id;
  map_ = map;
  numberOfThreads_ = numberOfThreads;
  numberOfProblems_ = numberOfProblems;

  int partitions = numberOfProblems / numberOfThreads;

  first_ = partitions * id;
  if (id == (numberOfThreads - 1)) {
    last_ = numberOfProblems - 1;
  } else {
    last_ = first_ + partitions - 1;
  }

  cout << "Id: " << id << "  Partitions: " << partitions << " First: "
      << first_ << " Last: " + last_ << endl;

} // RunExperiment


void RunExperiment::run() {

  Algorithm ** algorithm; // jMetal algorithms to be executed

  string experimentName = *(string*) map_["name"];
  experimentBaseDirectory_ = *(string*) map_["experimentDirectory"];
  algorithmNameList_ = *(vector<string>*) map_["algorithmNameList"];
  problemList_ = *(vector<string>*) map_["problemList"];
  indicatorList_ = *(vector<string>*) map_["indicatorList"];
  paretoFrontDirectory_ = *(string*) map_["paretoFrontDirectory"];
  paretoFrontFile_ = *(vector<string>*) map_["paretoFrontFile"];
  independentRuns_ = *(int*) map_["independentRuns"];
  outputParetoFrontFile_ = *(string*) map_["outputParetoFrontFile"];
  outputParetoSetFile_ = *(string*) map_["outputParetoSetFile"];

  int numberOfAlgorithms = algorithmNameList_.size();
  cout << "Experiment: Number of algorithms: " << numberOfAlgorithms << endl;
  cout << "Experiment: runs: " << independentRuns_ << endl;
  algorithm = new Algorithm*[numberOfAlgorithms] ;

  cout << "Name: " <<  experimentName << endl;
  cout << "experimentDirectory: " << experimentBaseDirectory_ << endl;
  cout << "numberOfThreads_: " << numberOfThreads_ << endl;
  cout << "numberOfProblems_: " << numberOfProblems_ << endl;
  cout << "first: " << first_ << endl;
  cout << "last: " << last_ << endl;

  SolutionSet * resultFront = NULL;


  for (int problemId = first_; problemId <= last_; problemId++) {
    Problem * problem; // The problem to solve
    string problemName;

    // STEP 2: get the problem from the list
    problemName = problemList_[problemId] ;

    // STEP 3: check the file containing the Pareto front of the problem
    // FIX: añadir bloqueo
    //synchronized(experiment_) {
    if (indicatorList_.size() > 0) {

      const char* paretoFrontPath = (paretoFrontDirectory_ + "/" + paretoFrontFile_[problemId]).c_str ();
      int paretoFrontResult = FileUtils::existsPath(paretoFrontPath);

      //int isDir = 0;
      if (paretoFrontResult != -1) {
        if (paretoFrontResult == 1) {
          paretoFrontFile_[problemId] = paretoFrontDirectory_ + "/" + paretoFrontFile_[problemId];
        } else {
          paretoFrontFile_[problemId] = "";
        }
      } else {
        cout << "Error searching for this path: " << paretoFrontPath << endl;
        exit(-1);
      }
    } // if
    //}

    char * problemName_ = (char *) problemName.c_str();
    experiment_->algorithmSettings(problemName, problemId, algorithm);

    problem = algorithm[0]->getProblem();
    for (int runs = 0; runs < independentRuns_; runs++) {
      cout << "Iruns: " << runs<< endl;
      // STEP 4: configure the algorithms

      // STEP 5: run the algorithms
      for (int i = 0; i < numberOfAlgorithms; i++) {

        cout << typeid(algorithm[i]).name() << endl;

        // STEP 6: create output directories
        string directory;
        directory = experimentBaseDirectory_ + "/data/" + algorithmNameList_[i] + "/" +
            problemList_[problemId];
        if (FileUtils::existsPath(directory.c_str()) != 1) {
          FileUtils::createDirectory(directory);
          cout << "Creating " << directory << endl;
        }

        // STEP 7: run the algorithm
        cout << "Running algorithm: " << algorithmNameList_[i] << ", problem: " <<
            problemList_[problemId] << ", run: " << runs << endl;
        resultFront= algorithm[i]->execute();

        // STEP 8: put the results in the output directory
        stringstream outputParetoFrontFilePath;
        outputParetoFrontFilePath << directory << "/" << outputParetoFrontFile_
            << "." << runs;
        stringstream outputParetoSetFilePath;
        outputParetoSetFilePath << directory << "/" << outputParetoSetFile_
            << "." << runs;
        resultFront->printObjectivesToFile(outputParetoFrontFilePath.str());
        resultFront->printVariablesToFile(outputParetoSetFilePath.str());

        // STEP 9: calculate quality indicators
        if (indicatorList_.size() > 0) {

          // TODO: Implementar indicadores de calidad
          /*
          QualityIndicator indicators;
          //System.out.println("PF file: " + paretoFrontFile_[problemId]);
          indicators = new QualityIndicator(problem, paretoFrontFile_[problemId]);

          for (int j = 0; j < indicatorList_.length; j++) {
            if (indicatorList_[j].equals("HV")) {
              double value = indicators.getHypervolume(resultFront);
              FileWriter os;
              try {
                os = new FileWriter(experimentDirectory + "/HV", true);
                os.write("" + value + "\n");
                os.close();
              } catch (IOException ex) {
                Logger.getLogger(Experiment.class.getName()).log(Level.SEVERE, null, ex);
              }
            }
            if (indicatorList_[j].equals("SPREAD")) {
              FileWriter os = null;
              try {
                double value = indicators.getSpread(resultFront);
                os = new FileWriter(experimentDirectory + "/SPREAD", true);
                os.write("" + value + "\n");
                os.close();
              } catch (IOException ex) {
                Logger.getLogger(Experiment.class.getName()).log(Level.SEVERE, null, ex);
              } finally {
                try {
                  os.close();
                } catch (IOException ex) {
                  Logger.getLogger(Experiment.class.getName()).log(Level.SEVERE, null, ex);
                }
              }
            }
            if (indicatorList_[j].equals("IGD")) {
              FileWriter os = null;
              try {
                double value = indicators.getIGD(resultFront);
                os = new FileWriter(experimentDirectory + "/IGD", true);
                os.write("" + value + "\n");
                os.close();
              } catch (IOException ex) {
                Logger.getLogger(Experiment.class.getName()).log(Level.SEVERE, null, ex);
              } finally {
                try {
                  os.close();
                } catch (IOException ex) {
                  Logger.getLogger(Experiment.class.getName()).log(Level.SEVERE, null, ex);
                }
              }
            }
            if (indicatorList_[j].equals("EPSILON")) {
              FileWriter os = null;
              try {
                double value = indicators.getEpsilon(resultFront);
                os = new FileWriter(experimentDirectory + "/EPSILON", true);
                os.write("" + value + "\n");
                os.close();
              } catch (IOException ex) {
                Logger.getLogger(Experiment.class.getName()).log(Level.SEVERE, null, ex);
              } finally {
                try {
                  os.close();
                } catch (IOException ex) {
                  Logger.getLogger(Experiment.class.getName()).log(Level.SEVERE, null, ex);
                }
              }
            }
          } // for
          */
        } // if
      } // for
    } // for
  } //for
} // run

