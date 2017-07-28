//  RunExperiment.cpp
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


#include <RunExperiment.h>


/**
 * Class implementing the steps to run an experiment
 */


/**
 * Constructor
 */
RunExperiment::RunExperiment(ExperimentExecution * experiment,std::map<std::string, void *> map,
                             int id, int numberOfThreads, int numberOfProblems, int threadIndex,
                             mutex * mtx)
{

    threadIndex_ = threadIndex;

    experiment_ = experiment;
    id_ = id;
    map_ = map;
    numberOfThreads_ = numberOfThreads;
    numberOfProblems_ = numberOfProblems;

    mutex_ = mtx;

    int partitions = numberOfProblems / numberOfThreads;

} // RunExperiment


void RunExperiment::run()
{

    Algorithm * algorithm; // jMetal algorithm to be executed

    std::string experimentName = *(string*) map_["name"];
    std::cout << experimentName << std::endl;
    experimentBaseDirectory_ = *(string*) map_["experimentDirectory"];
    std::cout << experimentBaseDirectory_ << std::endl;
    algorithmNameList_ = *(std::vector<std::string>*) map_["algorithmNameList"];
    problemList_ = *(std::vector<std::string>*) map_["problemList"];
    independentRuns_ = *(int*) map_["independentRuns"];
    std::cout << independentRuns_ << std::endl;
    outputParetoFrontFile_ = *(string*) map_["outputParetoFrontFile"];
    std::cout << outputParetoFrontFile_ << std::endl;
    outputParetoSetFile_ = *(string*) map_["outputParetoSetFile"];
    std::cout << outputParetoSetFile_ << std::endl;

    int numberOfAlgorithms = algorithmNameList_.size();

    std::cout << "Experiment name: " <<  experimentName << std::endl;
    std::cout << "Experiment directory: " << experimentBaseDirectory_ << std::endl;
    std::cout << "Number of threads: " << numberOfThreads_ << std::endl;

    SolutionSet * resultFront = nullptr;

    int problemIndex = -1;
    int algorithmIndex = -1;
    int numRun = -1;

    bool end = false;

    while (!end)
    {

        // WAIT MUTEX
//    int result = pthread_mutex_lock(mutex_) ;
//    if (result != 0) {
//      cerr << "RUNEXPERIMENT[" << threadIndex_ << "]: ERROR LOCKING THE MUTEX" << std::endl;
//      exit(-1) ;
//    }
        mutex_->lock();

        int experimentIndividualListIndex = experiment_->experimentIndividualListIndex_;
        //  std::cout << "Thread[" << threadIndex_ << "] experimentIndividualListIndex = " <<
        //      experimentIndividualListIndex << std::endl;
        // std::cout << "Thread[" << threadIndex_ << "] experiment_->experimentIndividualList_.size() = " <<
        //    experiment_->experimentIndividualList_.size() << std::endl;
        if (experimentIndividualListIndex < experiment_->experimentIndividualList_.size())
        {
            ExperimentIndividual * expIndv
                = experiment_->experimentIndividualList_[experimentIndividualListIndex];
            problemIndex = expIndv->getProblemIndex();
            algorithmIndex = expIndv->getAlgorithmIndex();
            numRun = expIndv->getNumRun();
            experiment_->experimentIndividualListIndex_ = experimentIndividualListIndex + 1;
        }
        else
        {
            // std::cout << "Thread[" << threadIndex_ << "] is finishing." << std::endl;
            end = true;
        }

        // SIGNAL MUTEX
//    result = pthread_mutex_unlock(mutex_) ;
//    if (result != 0) {
//      cerr << "RUNEXPERIMENT[" << threadIndex_ << "]: ERROR UNLOCKING THE MUTEX" << std::endl;
//      exit(-1) ;
//    }
        mutex_->unlock();

        if (!end)
        {

            Problem * problem; // The problem to solve
            std::string problemName;
            std::string pfFilePath = "";

            // Get the problem from the list
            problemName = problemList_[problemIndex] ;

            char * problemName_ = (char *) problemName.c_str();
            // TODO: Improve Settings
            algorithm = experiment_->algorithmSettings(problemName, algorithmIndex,
                        experimentIndividualListIndex);

            problem = algorithm->getProblem();

            // Create output directories
            std::string directory;
            directory = experimentBaseDirectory_ + "/data/" + algorithmNameList_[algorithmIndex] + "/" +
                        problemList_[problemIndex];
            if (FileUtils::existsPath(directory.c_str()) != 1)
            {
                FileUtils::createDirectory(directory);
                std::cout << "Creating directory: " << directory << std::endl;
            }

            // Run the algorithm
            std::cout << "Thread[" << threadIndex_ << "]: Start of algorithm: " <<
                 algorithmNameList_[algorithmIndex] << ", problem: " <<
                 problemList_[problemIndex] << ", run: " << numRun << std::endl;
            resultFront= algorithm->execute();

            // Put the results in the output directory
            stringstream outputParetoFrontFilePath;
            stringstream outputParetoSetFilePath;
            if (experiment_->isSingleObjective_)
            {
                outputParetoFrontFilePath << directory << "/" << outputParetoFrontFile_;
                outputParetoSetFilePath << directory << "/" << outputParetoSetFile_;
            }
            else
            {
                outputParetoFrontFilePath << directory << "/" << outputParetoFrontFile_
                                          << "." << numRun;
                outputParetoSetFilePath << directory << "/" << outputParetoSetFile_
                                        << "." << numRun;
            }

            resultFront->printObjectivesToFile(outputParetoFrontFilePath.str(),
                                               experiment_->isSingleObjective_);
            resultFront->printVariablesToFile(outputParetoSetFilePath.str(),
                                              experiment_->isSingleObjective_);

            std::cout << "Thread[" << threadIndex_ << "]: End of algorithm: " <<
                 algorithmNameList_[algorithmIndex] << ", problem: " <<
                 problemList_[problemIndex] << ", run: " << numRun << std::endl;

            delete resultFront;
            delete experiment_->algorithmSettingsList_[experimentIndividualListIndex];

        } // if

    } // while

    std::cout << "Thread[" << threadIndex_ << "] has finished." << std::endl;

} // run

