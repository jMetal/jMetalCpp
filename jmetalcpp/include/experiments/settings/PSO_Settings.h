//  PSO_Settings.h
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

#ifndef __PSO_SETTINGS__
#define __PSO_SETTINGS__

#include <Settings.h>
#include <PSO.h>
#include <PolynomialMutation.h>

class PSO_Settings : public Settings {

private:
  int    swarmSize_                 ;
  int    maxIterations_             ;
  double mutationDistributionIndex_ ;
  double mutationProbability_       ;

  Algorithm * algorithm ;
  Operator  * mutation  ; // Mutation operator

public:
  PSO_Settings() ;
  PSO_Settings(string problemName) ;
	~PSO_Settings() ;

  Algorithm * configure() ;
}; // PSO_Settings

#endif // __PSO_SETTINGS__
