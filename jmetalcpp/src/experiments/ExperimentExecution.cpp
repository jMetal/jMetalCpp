//  ExperimentExecution.cpp
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


#include <ExperimentExecution.h>


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
ExperimentExecution::ExperimentExecution() {

  experimentName_ = "noName";

  //CHECK: problemsSettings_ = NULL;

  //CHECK: algorithmNameList_ = NULL;
  //CHECK: problemList_ = NULL;
  //CHECK: paretoFrontFile_ = NULL;
  //CHECK: indicatorList_ = NULL;

  experimentBaseDirectory_ = "";
//  paretoFrontDirectory_ = "";
//  latexDirectory_ = "latex";

  outputParetoFrontFile_ = "FUN";
  outputParetoSetFile_ = "VAR";

//  algorithmSettings_ = NULL;
  //algorithm_ = NULL;

  independentRuns_ = 0;

//  indicatorMinimize_["HV"] = false;
//  indicatorMinimize_["EPSILON"] = true;
//  indicatorMinimize_["SPREAD"] = true;
//  indicatorMinimize_["GD"] = true;
//  indicatorMinimize_["IGD"] = true;
//
  experimentIndividualListIndex_ = 0;
  experimentIndividualListSize_ = -1;

} // ExperimentExecution


/**
 * Runs the experiment
 */
void ExperimentExecution::runExperiment(int numberOfThreads) {
  // Step 1: check experiment base directory
  checkExperimentDirectory();

  map_["name"] = &experimentName_;
  map_["experimentDirectory"] = &experimentBaseDirectory_;
  map_["algorithmNameList"] = &algorithmNameList_;
  map_["problemList"] = &problemList_;
//  map_["indicatorList"] = &indicatorList_;
//  map_["paretoFrontDirectory"] = &paretoFrontDirectory_;
//  map_["paretoFrontFile"] = &paretoFrontFile_;
  map_["independentRuns"] = &independentRuns_;
  map_["outputParetoFrontFile"] = &outputParetoFrontFile_;
  map_["outputParetoSetFile"] = &outputParetoSetFile_;
  //CHECK: map_["problemsSettings"] = &problemsSettings_;

  //SolutionSet ** resultFront = new SolutionSet*[algorithmNameList_.size()];

  cout << "Inicializando lista de tareas..." << endl;

  cout << "algorithmNameList_.size() = " << algorithmNameList_.size() << endl;

  experimentIndividualListSize_ =
      problemList_.size() * algorithmNameList_.size() * independentRuns_;
  for (int i=0; i<problemList_.size(); i++) {
    for (int j=0; j<algorithmNameList_.size(); j++) {
      for (int k=0; k<independentRuns_; k++) {
//        cout << "i,j,k = " << i << "," << j << "," << k << endl;
        ExperimentIndividual * expInd = new ExperimentIndividual(j, i, k);
//        cout << "Experimento individual creado" << endl;
        experimentIndividualList_.push_back(expInd);
//        cout << "Experimento añadido al vector..." << endl;
      }
    }
  }

  cout << "Lista de tareas inicializada..." << endl;

//  if (problemList_.size() < numberOfThreads) {
//    numberOfThreads = problemList_.size();
//    cout << "Experiments: list of problems is shorter than the number of " <<
//        "requested threads. Creating " << numberOfThreads << " threads." << endl;
//  } // if
//  else {
//    cout << "Experiments: creating " << numberOfThreads << " threads." << endl;
//  }

  int result;

  pthread_mutex_t mutex;
  result = pthread_mutex_init(&mutex, NULL) ;
  if (result != 0) {
    perror("ERROR INITIALIZING THE MUTEX");
    exit(-1) ;
  }
  else
    cout << "------- MUTEX OK ------" << endl ;

  pthread_t * p = new pthread_t[numberOfThreads];
  RunExperiment ** experiments_ = new RunExperiment*[numberOfThreads];
  for (int i = 0; i < numberOfThreads; i++) {
    experiments_[i] = new RunExperiment(this, map_, i, numberOfThreads,
        problemList_.size(), i, &mutex);
    result = pthread_create(&p[i], NULL, executeRun, experiments_[i]);
    if (result != 0) {
      perror("ERROR CREATING THREADS");
      exit(-1) ;
    }
  }

  for (int i = 0; i < numberOfThreads; i++) {
    result = pthread_join(p[i], NULL) ;
    cout << "Join con el thread " << i << endl;
    if (result != 0) {
      perror("ERROR MAKING THREAD JOIN");
      exit(-1) ;
    }
  }

  cout << "Join terminado...." << endl;

  delete [] p;
  for (int i=0; i< numberOfThreads; i++)
    delete experiments_[i];
  delete [] experiments_;

  cout << "Experiments borrados..." << endl;

} // runExperiment


/**
 * Runs the experiment
 */
void ExperimentExecution::runExperiment() {
  runExperiment(1);
} // runExperiment


//void ExperimentExecution::checkExperimentDirectory() {
//  int res = FileUtils::existsPath(experimentBaseDirectory_.c_str());
//  switch (res) {
//  case 0:
//    cout << "Experiment directory does NOT exist. Creating" << endl;
//    if (FileUtils::createDirectory(experimentBaseDirectory_) == -1) {
//      cout << "Error creating directory" << endl;
//      exit(-1);
//    }
//    break;
//  case 1:
//    cout << "Experiment directory exists." << endl;
//    cout << "Experiment directory is a directory" << endl;
//    break;
//  case 2:
//    cout << "Experiment directory exists." << endl;
//    cout << "Experiment directory is not a directory. Deleting file and creating directory" << endl;
//    if( remove(experimentBaseDirectory_.c_str()) != 0 ) {
//      cout << "Error deleting file." << endl;
//      exit(-1);
//    } else {
//      cout << "File successfully deleted." << endl;
//    }
//    if (FileUtils::createDirectory(experimentBaseDirectory_) == -1) {
//      cout << "Error creating directory" << endl;
//      exit(-1);
//    }
//    break;
//  case -1:
//    cout << "Error checking experiment directory" << endl;
//    exit(-1);
//  }
//} // checkExperimentDirectory
