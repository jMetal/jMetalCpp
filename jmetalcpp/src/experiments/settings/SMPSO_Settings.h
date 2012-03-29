//  SMPSO_Settings.h
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

#ifndef __SMPSO_SETTINGS__
#define __SMPSO_SETTINGS__

#include <Settings.h>
#include <SMPSO.h>
//#include <SBXCrossover.h>
#include <PolynomialMutation.h>
//#include <BinaryTournament2.h>

class SMPSO_Settings : public Settings{

private:
  int    swarmSize_                 ;
  int    maxIterations_             ;
  int    archiveSize_               ;
  double mutationDistributionIndex_ ;
  double mutationProbability_       ;
//	int populationSize_                 ;
//	int maxEvaluations_                 ;
//	double mutationProbability_         ;
//	double crossoverProbability_        ;
//	double mutationDistributionIndex_   ;
//	double crossoverDistributionIndex_  ;

  Algorithm * algorithm ;
//  Operator  * crossover ; // Crossover operator
  Operator  * mutation  ; // Mutation operator
//  Operator  * selection ; // Selection operator

public:
  SMPSO_Settings() ;
  SMPSO_Settings(string problemName) ;
	~SMPSO_Settings() ;

  Algorithm * configure() ;
}; // SMPSO_Settings

#endif // __SMPSO_SETTINGS__
