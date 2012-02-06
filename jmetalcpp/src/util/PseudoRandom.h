/**
 * @file Variable.cpp
 * @author Juan J. Durillo
 * @version 1.0
 * @date 19 September 2011
 */

#ifndef _PseudoRandom_h
#define _PseudoRandom_h

#include <iostream>
#include <RandomGenerator.h>

/**
 * This file is aimed at defining the interface for the random generator. 
 * The idea is that all the random numbers will be generated using a single
 * random generator which will be accesible throug this interface.
 **/

class PseudoRandom {
//private:
public:
  static RandomGenerator * randomGenerator_;
  PseudoRandom();

public:
  static double randDouble();//    static int randInt();
  static int randInt(int minBound, int maxBound);
  static double randDouble(double minBound, double maxBound);
};


#endif
