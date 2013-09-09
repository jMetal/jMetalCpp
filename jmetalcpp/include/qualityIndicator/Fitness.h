//  Fitness.h
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

#ifndef __FITNESS__
#define __FITNESS__

#include <MetricsUtil.h>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Fitness {

private:

public:

  MetricsUtil * utils_; // stores a reference to  qualityIndicatorUtils

  Fitness();
  ~Fitness();
  void fitness(vector <vector<double> > a, string file);

}; // Fitness

#endif /* __FITNESS__ */
