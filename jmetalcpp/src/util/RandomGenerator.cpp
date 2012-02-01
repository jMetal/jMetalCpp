/**
 * @file RandomGenerator.cpp
 * @author Juan J. Durillo
 * @version 1.0
 * @date 16 September 2011
 **/

#include <RandomGenerator.h>
#include <cstdlib>

using  namespace std;

/**
 *  This class is based on the random geneartor provided in the source
 *  code of Deb's implementation of NSGA-II.
 *  That implementation can be found in:
 *  http://www.iitk.ac.in/kangal/codes/nsga2/nsga2-v1.1.tar
 **/

RandomGenerator::RandomGenerator() {
  srand(time(NULL));
  //srand(0);
    cout << (unsigned)time(0) << endl; 
    seed_ = ((double) rand() / (double) (RAND_MAX )); 
    cout << "Seed value is: " << seed_ << endl;
    
//    seed_ = RAND_MAX;
//    cout << "Seed value is: " << seed_ << endl;


//    seed_ = (double) ((float) (float) seed_ / (float) RAND_MAX);
//    cout << "Seed value is: " << seed_ << endl;

    
    randomize();
} // RandomGenerator

int RandomGenerator::rnd (int low, int high) { 
    int res;
    if (low >= high){
        res = low;
    } else {
        res = low + (int)(randomperc()*(high-low+1));
        if (res > high){
            res = high;
        }
    }
    return (res);
}



double RandomGenerator::rndreal(double low, double high) {
    return (low + (high - low) * randomperc());
}


void RandomGenerator::randomize() {
    int j1;
    
    for (j1=0; j1<=54;j1++) {
        oldrand_[j1] = .0;
    } // for
    
    jrand_ = 0;
    warmup_random(seed_);
    
} // randomize


void RandomGenerator::warmup_random(double seed) {
    int j1, i1;
    double new_random, prev_random;
    oldrand_[54] = seed;
    new_random  = 0.000000001;
    prev_random = seed;
    
    for (j1=1; j1 <= 54; j1++) {
        i1 = (21*j1)%54;
        oldrand_[i1] = new_random;
        new_random = prev_random - new_random;
        
        if (new_random < 0.0) {
            new_random += 1.0;
        }
        
        prev_random = oldrand_[i1];
    }
    
    advance_random();
    advance_random();
    advance_random();
    jrand_ = 0;
    
    return;
}

void RandomGenerator::advance_random() {
    int j1;
    double new_random;
    for(j1=0; j1<24; j1++){
        new_random = oldrand_[j1]-oldrand_[j1+31];
        if(new_random<0.0){
            new_random = new_random+1.0;
        }
        oldrand_[j1] = new_random;
    }
    for(j1=24; j1<55; j1++){
        new_random = oldrand_[j1]-oldrand_[j1-24];
        if(new_random<0.0){
            new_random = new_random+1.0;
        }
        oldrand_[j1] = new_random;
    }
}

double RandomGenerator::randomperc() {
    jrand_++;
    if(jrand_>=55){
        jrand_ = 1;
        advance_random();
    }
    return oldrand_[jrand_];
}




