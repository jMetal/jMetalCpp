//  Settings.h
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
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

#ifndef __SETTINGS__
#define __SETTINGS__

#include <string>
#include <Problem.h>
#include <Algorithm.h>
#include <ProblemFactory.h>

class Settings {
protected:
  Problem * problem_ ;
  string problemName_ ;
  string paretoFrontFile_ ;

public:
  Settings() ;
  Settings(char * problemName) ;
  virtual ~Settings() = 0;

  virtual Algorithm * configure() = 0 ;
  Algorithm * configure(map<string, void *> settings) ;
}; // Settings

#endif //__SETTINGS__
