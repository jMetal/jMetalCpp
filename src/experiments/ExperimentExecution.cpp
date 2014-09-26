//  ExperimentExecution.cpp
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


#include <ExperimentExecution.h>


void* executeRun(void* ctx) {
  RunExperiment* cptr = (RunExperiment*)ctx;
  cptr->run();
  //pthread_exit(0);
} // executeRun


/**
 * Constructor
 *
 * Contains default settings
 */
ExperimentExecution::ExperimentExecution() {

  experimentName_ = "noName";

  experimentBaseDirectory_ = "";

  outputParetoFrontFile_ = "FUN";
  outputParetoSetFile_ = "VAR";

  independentRuns_ = 0;

  experimentIndividualListIndex_ = 0;
  experimentIndividualListSize_ = -1;

  isSingleObjective_ = false;

} // ExperimentExecution


/**
 * Runs the experiment
 */
void ExperimentExecution::runExperiment(int numberOfThreads) {

  checkExperimentDirectory();

  map_["name"] = &experimentName_;
  map_["experimentDirectory"] = &experimentBaseDirectory_;
  map_["algorithmNameList"] = &algorithmNameList_;
  map_["problemList"] = &problemList_;
  map_["independentRuns"] = &independentRuns_;
  map_["outputParetoFrontFile"] = &outputParetoFrontFile_;
  map_["outputParetoSetFile"] = &outputParetoSetFile_;

  cout << "Initializing task list..." << endl;
  //cout << "algorithmNameList_.size() = " << algorithmNameList_.size() << endl;

  experimentIndividualListSize_ =
      problemList_.size() * algorithmNameList_.size() * independentRuns_;
  for (int i=0; i<problemList_.size(); i++) {
    for (int j=0; j<algorithmNameList_.size(); j++) {
      for (int k=0; k<independentRuns_; k++) {
        ExperimentIndividual * expInd = new ExperimentIndividual(j, i, k);
        experimentIndividualList_.push_back(expInd);
      }
    }
  }

  algorithmSettingsList_ = new Settings*[experimentIndividualList_.size()];

  cout << "Task list initialized." << endl;

  int result;

  //pthread_mutex_t mutex;
  mutex mtx;
  //result = pthread_mutex_init(&mutex, NULL) ;
//  if (result != 0) {
//    perror("ERROR WHILE INITIALIZING THE MUTEX");
//    exit(-1) ;
//  }
//  else
//    cout << "------- MUTEX OK ------" << endl ;

  //pthread_t * p = new pthread_t[numberOfThreads];
  //thread * p = new thread[numberOfThreads];
  vector<thread> threads;
  RunExperiment ** experiments_ = new RunExperiment*[numberOfThreads];
  for (int i = 0; i < numberOfThreads; i++) {
    experiments_[i] = new RunExperiment(this, map_, i, numberOfThreads,
        problemList_.size(), i, &mtx);
//    result = pthread_create(&p[i], NULL, executeRun, experiments_[i]);
//    if (result != 0) {
//      perror("ERROR WHILE CREATING THREADS");
//      exit(-1) ;
//    }
    threads.push_back(thread(executeRun, experiments_[i]));
  }

//  for (int i = 0; i < numberOfThreads; i++) {
//    result = pthread_join(p[i], NULL) ;
//    cout << "Joined thread number " << (i+1) << "." <<endl;
//    if (result != 0) {
//      perror("ERROR WHILE MAKING THREAD JOIN");
//      exit(-1) ;
//    }
//    p[i]->join();
//  }
  for (auto& th : threads) th.join();

  cout << "All the threads have finished." << endl;

  for (int i=0; i < experimentIndividualList_.size(); i++) {
    delete experimentIndividualList_[i];
  }

  delete [] algorithmSettingsList_;
//  delete [] p;

  for (int i=0; i < numberOfThreads; i++)
    delete experiments_[i];
  delete [] experiments_;

} // runExperiment


/**
 * Runs the experiment
 */
void ExperimentExecution::runExperiment() {
  runExperiment(1);
} // runExperiment
