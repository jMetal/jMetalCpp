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
RunExperiment::RunExperiment(ExperimentExecution * experiment, map<string, void *> map,
    int id, int numberOfThreads, int numberOfProblems, int threadIndex,
    pthread_mutex_t * mutex) {

  threadIndex_ = threadIndex;

  experiment_ = experiment;
  id_ = id;
  map_ = map;
  numberOfThreads_ = numberOfThreads;
  numberOfProblems_ = numberOfProblems;

  mutex_ = mutex;

  int partitions = numberOfProblems / numberOfThreads;

} // RunExperiment


void RunExperiment::run() {

  Algorithm * algorithm; // jMetal algorithm to be executed

  string experimentName = *(string*) map_["name"];
  cout << experimentName << endl;
  experimentBaseDirectory_ = *(string*) map_["experimentDirectory"];
  cout << experimentBaseDirectory_ << endl;
  algorithmNameList_ = *(vector<string>*) map_["algorithmNameList"];
  problemList_ = *(vector<string>*) map_["problemList"];
//  indicatorList_ = *(vector<string>*) map_["indicatorList"];
//  paretoFrontDirectory_ = *(string*) map_["paretoFrontDirectory"];
//  cout << paretoFrontDirectory_ << endl;
//  paretoFrontFile_ = *(vector<string>*) map_["paretoFrontFile"];
  independentRuns_ = *(int*) map_["independentRuns"];
  cout << independentRuns_ << endl;
  outputParetoFrontFile_ = *(string*) map_["outputParetoFrontFile"];
  cout << outputParetoFrontFile_ << endl;
  outputParetoSetFile_ = *(string*) map_["outputParetoSetFile"];
  cout << outputParetoSetFile_ << endl;

  int numberOfAlgorithms = algorithmNameList_.size();

  cout << "Name: " <<  experimentName << endl;
  cout << "experimentDirectory: " << experimentBaseDirectory_ << endl;
  cout << "numberOfThreads_: " << numberOfThreads_ << endl;

  SolutionSet * resultFront = NULL;

  int problemIndex = -1;
  int algorithmIndex = -1;
  int numRun = -1;

  bool end = false;

  while (!end) {

    // WAIT MUTEX
    int result = pthread_mutex_lock(mutex_) ;
    if (result != 0) {
      cerr << "RUNEXPERIMENT [" << threadIndex_ << "]: ERROR LOCKING THE MUTEX" << endl;
      exit(-1) ;
    }

    int experimentIndividualListIndex = experiment_->experimentIndividualListIndex_;
    cout << "Thread[" << threadIndex_ << "] experimentIndividualListIndex = " << experimentIndividualListIndex << endl;
    cout << "Thread[" << threadIndex_ << "] experiment_->experimentIndividualList_.size() = " << experiment_->experimentIndividualList_.size() << endl;
    if (experimentIndividualListIndex < experiment_->experimentIndividualList_.size()) {
      ExperimentIndividual * expIndv
          = experiment_->experimentIndividualList_[experimentIndividualListIndex];
      problemIndex = expIndv->getProblemIndex();
      algorithmIndex = expIndv->getAlgorithmIndex();
      numRun = expIndv->getNumRun();
      experiment_->experimentIndividualListIndex_ = experimentIndividualListIndex + 1;
    } else {
      cout << "Thread[" << threadIndex_ << "] debe terminar..." << endl;
      end = true;
    }

    if (end) {
      cout << "Thread[" << threadIndex_ << "] esta terminando..." << endl;
    }

    // SIGNAL MUTEX
    result = pthread_mutex_unlock(mutex_) ;
    if (result != 0) {
      cerr << "RUNEXPERIMENT [" << threadIndex_ << "]: ERROR UNLOCKING THE MUTEX" << endl;
      exit(-1) ;
    }

    if (end) {
      cout << "Thread[" << threadIndex_ << "] ha desbloqueado el mutex..." << endl;
    }

    if (!end) {

      Problem * problem; // The problem to solve
      string problemName;
      string pfFilePath = "";

      // STEP 2: get the problem from the list
      problemName = problemList_[problemIndex] ;

      // STEP 3: check the file containing the Pareto front of the problem
      // FIX: añadir bloqueo
      //synchronized(experiment_) {
//      if (indicatorList_.size() > 0) {
//
//        const char* paretoFrontPath = (paretoFrontDirectory_ + "/" +
//            paretoFrontFile_[problemIndex]).c_str();
//        int paretoFrontResult = FileUtils::existsPath(paretoFrontPath);
//
//        // FIX: Arreglar caso cuando no existe el fichero!!!!
//        cout << "Thread [" << threadIndex_ << "]: paretoFrontResult: " <<paretoFrontResult << endl;
//
//        //int isDir = 0;
//        if (paretoFrontResult != -1) {
//          if (paretoFrontResult == 2) {
//            pfFilePath = paretoFrontDirectory_ + "/" +
//                paretoFrontFile_[problemIndex];
//          }
//        } else {
//          cout << "Error searching for this path: " << paretoFrontPath << endl;
//          exit(-1);
//        }
//      } // if
      //}

      char * problemName_ = (char *) problemName.c_str();
      // FIX Settings
      algorithm = experiment_->algorithmSettings(problemName, algorithmIndex,
          experimentIndividualListIndex);

      //cout << "Algorithm settings ended!" << endl;

      //cout << algorithm->getInputParameter("populationSize") << endl;

      //cout << "problemName_ = " << problemName_ << endl;

      problem = algorithm->getProblem();

      //cout << "Problem?" << endl;

      //cout << typeid(algorithm).name() << endl;

      // STEP 6: create output directories
      string directory;
      directory = experimentBaseDirectory_ + "/data/" + algorithmNameList_[algorithmIndex] + "/" +
          problemList_[problemIndex];
      if (FileUtils::existsPath(directory.c_str()) != 1) {
        FileUtils::createDirectory(directory);
        cout << "Creating " << directory << endl;
      }

      // STEP 7: run the algorithm
      cout << "Thread [" << threadIndex_ << "]: Running algorithm: " << algorithmNameList_[algorithmIndex] << ", problem: " <<
          problemList_[problemIndex] << ", run: " << numRun << endl;
      resultFront= algorithm->execute();

      // STEP 8: put the results in the output directory
      stringstream outputParetoFrontFilePath;
      outputParetoFrontFilePath << directory << "/" << outputParetoFrontFile_
          << "." << numRun;
      stringstream outputParetoSetFilePath;
      outputParetoSetFilePath << directory << "/" << outputParetoSetFile_
          << "." << numRun;
      resultFront->printObjectivesToFile(outputParetoFrontFilePath.str());
      resultFront->printVariablesToFile(outputParetoSetFilePath.str());

      cout << "Thread [" << threadIndex_ << "]: Ended algorithm: " << algorithmNameList_[algorithmIndex] << ", problem: " <<
          problemList_[problemIndex] << ", run: " << numRun << endl;

//      // STEP 9: calculate quality indicators
//      if (indicatorList_.size() > 0) {
//
//        QualityIndicator * indicators;
//        cout << "PF file: " << pfFilePath << endl;
//        indicators = new QualityIndicator(problem, pfFilePath);
//
//        cout << "Thread [" << threadIndex_ << "]: Quality indicator created!" << endl;
//
//        for (int j = 0; j < indicatorList_.size(); j++) {
//          string qualityIndicatorFile = directory;
//          double value;
//
//          cout << "Thread [" << threadIndex_ << "]: Quality indicator: " << indicatorList_[j] << endl;
//
//          if (indicatorList_[j].compare("HV")==0) {
//            value = indicators->getHypervolume(resultFront);
//            qualityIndicatorFile = qualityIndicatorFile + "/HV";
//          }
//          if (indicatorList_[j].compare("SPREAD")==0) {
//            value = indicators->getSpread(resultFront);
//            qualityIndicatorFile = qualityIndicatorFile + "/SPREAD";
//          }
//          if (indicatorList_[j].compare("IGD")==0) {
//            value = indicators->getIGD(resultFront);
//            qualityIndicatorFile = qualityIndicatorFile + "/IGD";
//          }
//          if (indicatorList_[j].compare("EPSILON")==0) {
//            value = indicators->getEpsilon(resultFront);
//            qualityIndicatorFile = qualityIndicatorFile + "/EPSILON";
//          }
//
//          cout << "Thread [" << threadIndex_ << "]: Quality indicator file: " << qualityIndicatorFile << endl;
//
//          if (qualityIndicatorFile.compare(directory)!=0) {
//            std::fstream out(qualityIndicatorFile.c_str(),
//                std::ios::out | std::ios::app);
//            out << value << endl;
//            out.close();
//          }
//
//        } // for
//        //delete indicators;
//      } // if

      delete resultFront;
      //delete algorithm;
      //experiment_->deleteSettings();
      delete experiment_->algorithmSettingsList_[experimentIndividualListIndex];

    } // if

    if (end) {
      cout << "Thread[" << threadIndex_ << "] ya no hace nada mas..." << endl;
    }

  } // while

  if (end) {
    cout << "Thread[" << threadIndex_ << "] sale del while..." << endl;
  }

} // run

