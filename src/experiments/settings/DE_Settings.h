//  DE_Settings.h
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

#ifndef __DE_SETTINGS__
#define __DE_SETTINGS__

#include <Settings.h>
#include <DE.h>
#include <DifferentialEvolutionCrossover.h>
#include <DifferentialEvolutionSelection.h>

class DE_Settings : public Settings {
private:
	int populationSize_        ;
	int maxEvaluations_        ;
	double crParameter_        ;
  double fParameter_         ;
  string deVariantParameter_ ;

  Algorithm * algorithm ;
  Operator  * crossover ; // Crossover operator
  Operator  * selection ; // Selection operator

public:
  DE_Settings() ;
  DE_Settings(string problemName) ;
	~DE_Settings() ;

  Algorithm * configure() ;
}; // DE_Settings

#endif // __DE_SETTINGS__
