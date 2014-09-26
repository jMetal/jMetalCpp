//  StandardStudyExecutionSO.cpp
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


#include <StandardStudyExecutionSO.h>


/**
 * Class implementing a typical experimental study. Three algorithms are
 * compared when solving the ZDT, DTLZ, and WFG benchmarks, and the hypervolume,
 * spread and additive epsilon indicators are used for performance assessment.
 */


/**
 * Configures the algorithms in each independent run
 * @param problemName Name of the problem to solve
 * @algorithmId Index of the algorithm to be configured
 * @param experimentIndividualId Index of the experiment individual
 */
Algorithm * StandardStudyExecutionSO::algorithmSettings(string problemName,
    int algorithmId, int experimentIndividualId) {

  Algorithm * alg;

  switch (algorithmId) {
  case 0:
    algorithmSettingsList_[experimentIndividualId] =
        new gGA_Settings(problemName);
    alg = (algorithmSettingsList_[experimentIndividualId])->configure();
    break;
  case 1:
    algorithmSettingsList_[experimentIndividualId] =
        new ssGA_Settings(problemName);
    alg = (algorithmSettingsList_[experimentIndividualId])->configure();
    break;
  case 2:
    algorithmSettingsList_[experimentIndividualId] =
        new DE_Settings(problemName);
    alg = (algorithmSettingsList_[experimentIndividualId])->configure();
    break;
  case 3:
    algorithmSettingsList_[experimentIndividualId] =
        new PSO_Settings(problemName);
    alg = (algorithmSettingsList_[experimentIndividualId])->configure();
    break;
  }

  return alg;

} // algorithmSettings


int main(int argc, char ** argv) {

  StandardStudyExecutionSO * exp = new StandardStudyExecutionSO() ;

  // Name of the experiment:
  exp->experimentName_ = "StandardStudySO";

  // List of algorithm names to be used in the experiment
  // (please, refer to the README to check the possible values):
  vector<string> algorithmNameList_ {
      "gGA", "ssGA", "DE", "PSO"};

  // List of problem names to be used in the experiment
  // (please, refer to the README to check the possible values):
  vector<string> problemList_ {
      "Sphere", "Griewank"};

  // Directory where the execution results will be stored:
  exp->experimentBaseDirectory_ = "C:/jMetal/pruebas/jmetal-cpp/" +
                                 exp->experimentName_;

  // Number of independent runs of each algorithm for each problem:
  exp->independentRuns_ = 20;

  // Number of threads to be used to execute the experiment
  int numberOfThreads = 3;

  exp->algorithmNameList_ = algorithmNameList_;
  exp->problemList_ = problemList_;
  int numberOfAlgorithms = exp->algorithmNameList_.size();
  exp->isSingleObjective_ = true;

  cout << "Experiment (" << exp->experimentName_ << ") is starting." << endl;

  exp->runExperiment(numberOfThreads);

  cout << "Experiment (" << exp->experimentName_ << ") has finished." << endl;

  delete exp;

} // main

