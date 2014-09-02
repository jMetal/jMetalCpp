//  RunExperiment.cpp
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


#include <RunExperiment.h>


/**
 * Class implementing the steps to run an experiment
 */


/**
 * Constructor
 */
RunExperiment::RunExperiment(ExperimentExecution * experiment, map<string, void *> map,
    int id, int numberOfThreads, int numberOfProblems, int threadIndex,
    mutex * mtx) {

  threadIndex_ = threadIndex;

  experiment_ = experiment;
  id_ = id;
  map_ = map;
  numberOfThreads_ = numberOfThreads;
  numberOfProblems_ = numberOfProblems;

  mutex_ = mtx;

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
  independentRuns_ = *(int*) map_["independentRuns"];
  cout << independentRuns_ << endl;
  outputParetoFrontFile_ = *(string*) map_["outputParetoFrontFile"];
  cout << outputParetoFrontFile_ << endl;
  outputParetoSetFile_ = *(string*) map_["outputParetoSetFile"];
  cout << outputParetoSetFile_ << endl;

  int numberOfAlgorithms = algorithmNameList_.size();

  cout << "Experiment name: " <<  experimentName << endl;
  cout << "Experiment directory: " << experimentBaseDirectory_ << endl;
  cout << "Number of threads: " << numberOfThreads_ << endl;

  SolutionSet * resultFront = NULL;

  int problemIndex = -1;
  int algorithmIndex = -1;
  int numRun = -1;

  bool end = false;

  while (!end) {

    // WAIT MUTEX
//    int result = pthread_mutex_lock(mutex_) ;
//    if (result != 0) {
//      cerr << "RUNEXPERIMENT[" << threadIndex_ << "]: ERROR LOCKING THE MUTEX" << endl;
//      exit(-1) ;
//    }
    mutex_->lock();

    int experimentIndividualListIndex = experiment_->experimentIndividualListIndex_;
    //  cout << "Thread[" << threadIndex_ << "] experimentIndividualListIndex = " <<
    //      experimentIndividualListIndex << endl;
    // cout << "Thread[" << threadIndex_ << "] experiment_->experimentIndividualList_.size() = " <<
    //    experiment_->experimentIndividualList_.size() << endl;
    if (experimentIndividualListIndex < experiment_->experimentIndividualList_.size()) {
      ExperimentIndividual * expIndv
          = experiment_->experimentIndividualList_[experimentIndividualListIndex];
      problemIndex = expIndv->getProblemIndex();
      algorithmIndex = expIndv->getAlgorithmIndex();
      numRun = expIndv->getNumRun();
      experiment_->experimentIndividualListIndex_ = experimentIndividualListIndex + 1;
    } else {
      // cout << "Thread[" << threadIndex_ << "] is finishing." << endl;
      end = true;
    }

    // SIGNAL MUTEX
//    result = pthread_mutex_unlock(mutex_) ;
//    if (result != 0) {
//      cerr << "RUNEXPERIMENT[" << threadIndex_ << "]: ERROR UNLOCKING THE MUTEX" << endl;
//      exit(-1) ;
//    }
    mutex_->unlock();

    if (!end) {

      Problem * problem; // The problem to solve
      string problemName;
      string pfFilePath = "";

      // Get the problem from the list
      problemName = problemList_[problemIndex] ;

      char * problemName_ = (char *) problemName.c_str();
      // TODO: Improve Settings
      algorithm = experiment_->algorithmSettings(problemName, algorithmIndex,
          experimentIndividualListIndex);

      problem = algorithm->getProblem();

      // Create output directories
      string directory;
      directory = experimentBaseDirectory_ + "/data/" + algorithmNameList_[algorithmIndex] + "/" +
          problemList_[problemIndex];
      if (FileUtils::existsPath(directory.c_str()) != 1) {
        FileUtils::createDirectory(directory);
        cout << "Creating directory: " << directory << endl;
      }

      // Run the algorithm
      cout << "Thread[" << threadIndex_ << "]: Start of algorithm: " <<
          algorithmNameList_[algorithmIndex] << ", problem: " <<
          problemList_[problemIndex] << ", run: " << numRun << endl;
      resultFront= algorithm->execute();

      // Put the results in the output directory
      stringstream outputParetoFrontFilePath;
      stringstream outputParetoSetFilePath;
      if (experiment_->isSingleObjective_) {
        outputParetoFrontFilePath << directory << "/" << outputParetoFrontFile_;
        outputParetoSetFilePath << directory << "/" << outputParetoSetFile_;
      } else {
        outputParetoFrontFilePath << directory << "/" << outputParetoFrontFile_
            << "." << numRun;
        outputParetoSetFilePath << directory << "/" << outputParetoSetFile_
            << "." << numRun;
      }

      resultFront->printObjectivesToFile(outputParetoFrontFilePath.str(),
          experiment_->isSingleObjective_);
      resultFront->printVariablesToFile(outputParetoSetFilePath.str(),
          experiment_->isSingleObjective_);

      cout << "Thread[" << threadIndex_ << "]: End of algorithm: " <<
          algorithmNameList_[algorithmIndex] << ", problem: " <<
          problemList_[problemIndex] << ", run: " << numRun << endl;

      delete resultFront;
      delete experiment_->algorithmSettingsList_[experimentIndividualListIndex];

    } // if

  } // while

  cout << "Thread[" << threadIndex_ << "] has finished." << endl;

} // run

