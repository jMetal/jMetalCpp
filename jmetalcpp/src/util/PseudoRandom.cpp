/**
 * @file PseudoRandom.cpp
 * @author Juan J. Durillo
 * @version 1.0
 * @date 19 September 2011
 */

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
    
