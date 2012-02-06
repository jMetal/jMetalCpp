/**
 * @file RandomGenerator.h
 * @author Juan J. Durillo
 * @version 1.0
 * @date 16 September 2011
 */

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
