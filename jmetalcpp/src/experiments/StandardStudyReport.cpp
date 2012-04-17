//  StandardStudyReport.cpp
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


#include <StandardStudyReport.h>


/**
 * Class implementing a typical experimental study. Five algorithms are
 * compared when solving the ZDT, DTLZ, and WFG benchmarks, and the hypervolume,
 * spread and additive epsilon indicators are used for performance assessment.
 */


int main(int argc, char ** argv) {
  StandardStudyReport * exp = new StandardStudyReport() ;

  exp->experimentName_ = "StandardStudy";

  const char * algorithmNameList_[] = {
      "NSGAII", "SMPSO", "GDE3"};
  exp->algorithmNameList_.assign(algorithmNameList_, end(algorithmNameList_));

  const char * problemList_[] = {
      "ZDT1", "ZDT2", "ZDT3", "ZDT4", "ZDT6"};
  exp->problemList_.assign(problemList_, end(problemList_));

  const char * paretoFrontFile_[] = {
      "ZDT1.pf", "ZDT2.pf", "ZDT3.pf", "ZDT4.pf", "ZDT6.pf"};
  exp->paretoFrontFile_.assign(paretoFrontFile_, end(paretoFrontFile_));

  const char * indicatorList_[] = {
      "HV", "SPREAD", "EPSILON"};
  exp->indicatorList_.assign(indicatorList_, end(indicatorList_));

  int numberOfAlgorithms = exp->algorithmNameList_.size();

  //exp->experimentBaseDirectory_ = "/Users/antonio/Softw/pruebas/jmetal/kk/" +
  exp->experimentBaseDirectory_ = "C:/antonio/Softw/pruebas/jmetal-cpp/" +
                                 exp->experimentName_;
  //exp->paretoFrontDirectory_ = "/Users/antonio/Softw/pruebas/data/paretoFronts";
  //exp->paretoFrontDirectory_ = "C:/antonio/Softw/pruebas/data/paretoFronts";
  exp->paretoFrontDirectory_ = "C:/antonio/Softw/pruebas/data/newParetoFronts";

  exp->independentRuns_ = 20;

  // Generate quality indicators
  exp->generateQualityIndicators();

  // Generate latex tables (comment this sentence is not desired)
  exp->generateLatexTables();

  // Configure the R scripts to be generated
  int rows = 3 ;
  int columns = 2 ;
  string prefix = "ZDT";
  const char * problemsValues[] = {
      "ZDT1", "ZDT2", "ZDT3", "ZDT4", "ZDT6"};
  vector<string> problems (problemsValues, end(problemsValues));

  bool notch;
  exp->generateRBoxplotScripts(rows, columns, problems, prefix, notch = false, exp);
  exp->generateRWilcoxonScripts(problems, prefix, exp);

  delete exp;

} // main

