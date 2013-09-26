//  RandomGenerator.h
//
//  Author:
//       Juan J. Durillo <durillo@lcc.uma.es>
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

#ifndef _RandomGenerator_h
#define _RandomGenerator_h

#include <iostream>
#include <ctime>


/**
 *  This class is based on the random geneartor provided in the source
 *  code of Deb's implementation of NSGA-II.
 *  That implementation can be found in:
 *  http://www.iitk.ac.in/kangal/codes/nsga2/nsga2-v1.1.tar
 **/

class RandomGenerator {

private:
  double seed_;
  double oldrand_[55];
  int jrand_;
  void randomize();
  void warmup_random(double seed);
  void advance_random();
  double randomperc();
    
public:
  RandomGenerator(void);
  ~RandomGenerator(void);
  int rnd (int low, int high);
  double rndreal(double low, double high);
    
}; // RandomGenerator

#endif
