//  NSGAIIStudy.cpp
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


#include <NSGAIIStudy.h>


/**
 * Class implementing an example of experiment using NSGA-II as base algorithm.
 * The experiment consisting in studying the effect of the crossover probability
 * in NSGA-II.
 */


/**
 * Configures the algorithms in each independent run
 * @param problem The problem to solve
 * @param problemIndex
 * @param algorithm Array containing the algorithms to run
 */
void NSGAIIStudy::algorithmSettings(string problemName,
      int problemIndex, Algorithm ** algorithm) {

  int numberOfAlgorithms = algorithmNameList_.size();

// TODO: Usaremos esta parte cuando usemos el Settings no global
//  map<string, void *> * parameters
//    = new map<string, void *>[numberOfAlgorithms];
//
//  double crossoverProbability_0 = 1.0;
//  double crossoverProbability_1 = 0.9;
//  double crossoverProbability_2 = 0.8;
//  double crossoverProbability_3 = 0.7;
//  parameters[0]["crossoverProbability_"] = &crossoverProbability_0;
//  parameters[1]["crossoverProbability_"] = &crossoverProbability_1;
//  parameters[2]["crossoverProbability_"] = &crossoverProbability_2;
//  parameters[3]["crossoverProbability_"] = &crossoverProbability_3;
//
//  if (paretoFrontFile_[problemIndex].compare("") != 0) {
//     // FIX: (paretoFrontFile_[problemIndex] == NULL)) {
//    for (int i = 0; i < numberOfAlgorithms; i++)
//      parameters[i]["paretoFrontFile_"] = &paretoFrontFile_[problemIndex];
//  } // if

  for (int i = 0; i < numberOfAlgorithms; i++) {
    Settings * settings = new NSGAII_Settings(problemName);
    algorithm[i] = settings->configure();
    // TODO: Cambiar a settings no global?
    //settings = settings->configure(parameters[i]);
//    algorithmSettings_[i] = new NSGAII_Settings(problemName);
//    algorithm[i] = algorithmSettings_[i]->configure();
  }
} // algorithmSettings


/**
 * Configures the algorithms in each independent run
 * @param problem The problem to solve
 */
Algorithm * NSGAIIStudy::algorithmSettings(string problemName) {

  Settings * settings = new NSGAII_Settings(problemName);
  return settings->configure();

} // algorithmSettings


int main(int argc, char ** argv) {
  NSGAIIStudy * exp = new NSGAIIStudy() ; // exp = experiment

  exp->experimentName_ = "NSGAIIStudy";

  const char * algorithmNameList_[] = {
      //"NSGAIIa", "NSGAIIb", "NSGAIIc", "NSGAIId"};
      "NSGAIIa", "NSGAIIb"};
  exp->algorithmNameList_.assign(algorithmNameList_, end(algorithmNameList_));

  const char * problemList_[] = {
      //"ZDT1", "ZDT2", "ZDT3", "ZDT4", "DTLZ1", "WFG2"};
      //"ZDT1", "ZDT2", "ZDT3", "ZDT4", "DTLZ1"};
      //"ZDT1"};
      "ZDT1", "ZDT2", "ZDT3", "ZDT4", "ZDT6"};
  exp->problemList_.assign(problemList_, end(problemList_));

  const char * paretoFrontFile_[] = {
      //"ZDT1.pf", "ZDT2.pf", "ZDT3.pf","ZDT4.pf", "DTLZ1.2D.pf", "WFG2.2D.pf"};
      //"ZDT1.pf", "ZDT2.pf", "ZDT3.pf","ZDT4.pf", "DTLZ1.2D.pf"};
      //"ZDT1.pf"};
      "ZDT1.pf", "ZDT2.pf", "ZDT3.pf", "ZDT4.pf", "ZDT6.pf"};
  exp->paretoFrontFile_.assign(paretoFrontFile_, end(paretoFrontFile_));

  const char * indicatorList_[] = {
      //"HV", "SPREAD", "IGD", "EPSILON"};
      "HV", "SPREAD", "EPSILON"};
  exp->indicatorList_.assign(indicatorList_, end(indicatorList_));

  int numberOfAlgorithms = exp->algorithmNameList_.size();

  //exp->experimentBaseDirectory_ = "/Users/antonio/Softw/pruebas/jmetal/kk/" +
  exp->experimentBaseDirectory_ = "C:/antonio/Softw/pruebas/jmetal-cpp/" +
                                 exp->experimentName_;
  //exp->paretoFrontDirectory_ = "/Users/antonio/Softw/pruebas/data/paretoFronts";
  exp->paretoFrontDirectory_ = "C:/antonio/Softw/pruebas/data/paretoFronts";

  exp->algorithmSettings_ = new Settings*[numberOfAlgorithms];

  exp->independentRuns_ = 4;

  // Run the experiments
  int numberOfThreads;
  exp->runExperiment(numberOfThreads = 1);

  cout << "Run Experiment terminado..." << endl;

  // Generate latex tables (comment this sentence is not desired)
  exp->generateLatexTables();

  // Configure the R scripts to be generated
  int rows = 2 ;
  int columns = 3 ;
  string prefix = "Problems";
  const char * problemsValues[] = {
      //"ZDT1", "ZDT2","ZDT3", "ZDT4", "DTLZ1", "WFG2"};
      //"ZDT1", "ZDT2","ZDT3", "ZDT4", "DTLZ1"};
      //"ZDT1"};
      "ZDT1", "ZDT2", "ZDT3", "ZDT4", "ZDT6"};
  vector<string> problems (problemsValues, end(problemsValues));

  bool notch;
  exp->generateRBoxplotScripts(rows, columns, problems, prefix, notch = true, exp);
  exp->generateRWilcoxonScripts(problems, prefix, exp);

//  for (int i=0; i<numberOfAlgorithms; i++)
//    delete exp->algorithmSettings_[i];
//  delete [] exp->algorithmSettings_;
  delete exp;

  cout << "main ended..." << endl;

} // main

