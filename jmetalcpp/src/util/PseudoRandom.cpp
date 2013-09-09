//  PseudoRandom.cpp
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

#include <PseudoRandom.h>

using namespace std;

/**
 * This file is aimed at defining the interface for the random generator. 
 * The idea is that all the random numbers will be generated using a single
 * random generator which will be accesible throug this interface.
 **/

RandomGenerator * PseudoRandom::randomGenerator_ = NULL ;

PseudoRandom::PseudoRandom() {
  //randomGenerator_ = NULL ;
  if (PseudoRandom::randomGenerator_ == NULL) {
    PseudoRandom::randomGenerator_ = new RandomGenerator();
  }
}

//static int PseudoRandom::randInt() {
//    if (randomGenerator_ == NULL) {
//        new PseudoRandom();
//    }
//    return randomGenerator_->rando
//}

double PseudoRandom::randDouble() {
  if (PseudoRandom::randomGenerator_ == NULL) {
    PseudoRandom::randomGenerator_ = new RandomGenerator();
  }
  return PseudoRandom::randomGenerator_->rndreal(0.0,1.0);
}

int PseudoRandom::randInt(int minBound, int maxBound) {
  if (PseudoRandom::randomGenerator_ == NULL) {
    PseudoRandom::randomGenerator_ = new RandomGenerator();
  }
  return PseudoRandom::randomGenerator_->rnd(minBound,maxBound);
}

double PseudoRandom::randDouble(double minBound, double maxBound) {
  if (PseudoRandom::randomGenerator_ == NULL) {
    PseudoRandom::randomGenerator_ = new RandomGenerator();
  }
  return PseudoRandom::randomGenerator_->rndreal(minBound,maxBound);
}
    
