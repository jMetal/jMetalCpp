//  FitnessCollector.h
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

#ifndef __FITNESS_COLLECTOR__
#define __FITNESS_COLLECTOR__

#include <IntDouble.h>

class FitnessCollector {
  
public:
  
  double * history;
  int historyLength;
  
  IntDouble ** fitness; // int holds index for respective arx
  IntDouble ** raw;     // sorted differently than fitness!
  
  /* 
   * history of delta fitness / sigma^2. Here delta fitness is the minimum of 
   * fitness value differences with distance lambda/2 in the ranking.
   */
  double * deltaFitHist;
  int idxDeltaFitHist;
    
//public:
  
  FitnessCollector();
  IntDouble * minRaw(int size);
  IntDouble * maxRaw(int size);
  
};

#endif /* __FITNESS_COLLECTOR__ */