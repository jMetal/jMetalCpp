//  NSGAIIStudy.h
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

#ifndef __NSGAIISTUDY__
#define __NSGAIISTUDY__

#include <Experiment.h>
#include <NSGAII_Settings.h>
#include <Settings.h>
#include <string>

/**
 * Class implementing an example of experiment using NSGA-II as base algorithm.
 * The experiment consisting in studying the effect of the crossover probability
 * in NSGA-II.
 */

class NSGAIIStudy : public Experiment {

public:
  void algorithmSettings(string problemName, int problemIndex, Algorithm ** algorithm);
  Algorithm * algorithmSettings(string problemName);

};



#endif /* __NSGAIISTUDY__ */
