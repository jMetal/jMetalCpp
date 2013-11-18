//  PAES_main.cpp
//
//  Author:
//       Cristian Zambrano <cristian_uteq@hotmail.com>
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

#include <Problem.h>
#include <Algorithm.h>
#include <Operator.h>
#include <Solution.h>
#include <RealSolutionType.h>
#include <PolynomialMutation.h>
#include <ProblemFactory.h>
#include <iostream>
#include <paes.h>
#include <time.h>

int main(int argc, char ** argv) {
  
  clock_t t_ini, t_fin;
  Problem   * problem   ; // The problem to solve
  Algorithm * algorithm ; // The algorithm to use
  Operator  * mutation  ; // Mutation operator
  
  if (argc>=2) {
    problem = ProblemFactory::getProblem(argc, argv);
    cout << "Selected problem: " << problem->getName() << endl;
  } else {
    cout << "No problem selected." << endl;
    cout << "Default problem will be used: Fonseca" << endl;
    problem = ProblemFactory::getProblem(const_cast<char *>("Fonseca"));
  }
  
  //QualityIndicator indicators ; // Object to get quality indicators
  
  algorithm = new paes(problem);
  
  // Algorithm parameters
  int archiveSizeValue = 100;
  int *archiveSizePtr = &archiveSizeValue;
  int biSectionsValue = 5;
  int *biSectionsPtr = &biSectionsValue;
  int maxEvaluationsValue = 25000;
  int *maxEvaluationsPtr = &maxEvaluationsValue;
  
  algorithm->setInputParameter("archiveSize",archiveSizePtr);
  algorithm->setInputParameter("biSections",biSectionsPtr);
  algorithm->setInputParameter("maxEvaluations",maxEvaluationsPtr);
  
  // Mutation (Real variables)
  map<string, void *> parameters; // Operator parameters
  parameters.clear();
  double probabilityValue1 = 1.0/problem->getNumberOfVariables();
  double *probabilityPtr1 = &probabilityValue1;
  double distributionIndexValue1 = 20.0;
  double *distributionIndexPtr1 = &distributionIndexValue1;
  parameters["probability"] =  probabilityPtr1 ;
  parameters["distributionIndex"] = distributionIndexPtr1 ;
  mutation = new PolynomialMutation(parameters);
  
  // Mutation (BinaryReal variables)
  //mutation = MutationFactory.getMutationOperator("BitFlipMutation");
  //mutation.setParameter("probability",0.1);
  algorithm->addOperator("mutation",mutation);
  
  // Checking parameters
  //cout << "PolynomialMutation:" << endl;
  //cout << *(double *) algorithm->getOperator("mutation")->getParameter("probability") << endl;
  //cout << *(double *) algorithm->getOperator("mutation")->getParameter("distributionIndex") << endl;
  
  t_ini = clock();
  SolutionSet * population = algorithm->execute();
  t_fin = clock();
  double secs = (double) (t_fin - t_ini);
  secs = secs / CLOCKS_PER_SEC;
  
  // Result messages
  cout << "Total execution time: " << secs << "s" << endl;
  cout << "Variables values have been writen to file VAR" << endl;
  population->printVariablesToFile("VAR");
  cout << "Objectives values have been writen to file FUN" << endl;
  population->printObjectivesToFile("FUN");
  
//  if (indicators != NULL) {
//    cout << "Quality indicators" << endl;
//    cout << "Hypervolume: " << indicators->getHypervolume(population) << endl;
//    cout << "GD         : " << indicators->getGD(population) << endl;
//    cout << "IGD        : " << indicators->getIGD(population) << endl;
//    cout << "Spread     : " << indicators->getSpread(population) << endl;
//    cout << "Epsilon    : " << indicators->getEpsilon(population) << endl;
//    
//    int evaluations = *(int *) algorithm->getOutputParameter("evaluations");;
//    cout << "Speed      : " << evaluations << " evaluations" << endl;
//  } // if
  
} // main




