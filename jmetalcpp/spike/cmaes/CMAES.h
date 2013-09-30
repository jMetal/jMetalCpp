//  CMAES.h
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

#ifndef __CMAES__
#define __CMAES__

#include <Algorithm.h>
#include <Problem.h>
#include <SolutionSet.h>

#include <PseudoRandom.h>

/**
 * This class implements the CMA-ES algorithm.
 */

class CMAES : public Algorithm {

  private:
    
    /**
     * Stores the population size
     */
    int populationSize_;
    /**
     * Stores the population
     */
    SolutionSet * population_;
//    double ** population_;
    
//    int N;
//    long seed = System.currentTimeMillis();
//    Random rand = new Random(seed); // Note: it also Serializable
//
//    final MyMath math = new MyMath();
    double axisratio; 
//    long counteval;
//    long countiter;
//
//    long bestever_eval; // C style, TODO:  better make use of class CMASolution?
//    double[] bestever_x;
//    double bestever_fit = Double.NaN; 
//    // CMASolution bestever; // used as output variable
//
    double sigma;
 //   double * typicalX; // eventually used to set initialX
//    double[] initialX; // set in the end of init()
    double * LBound;
    double * UBound;    // bounds
    double * xmean;
//    double xmean_fit = Double.NaN;
    double * pc;
    double * ps;
    double ** C;
//    double maxsqrtdiagC;
//    double minsqrtdiagC;
    double ** B;
    double * diagD;
    bool flgdiag; // 0 == full covariance matrix
//    
    /* init information */
    double * startsigma;
    double maxstartsigma;
    double minstartsigma;
//    
//    boolean iniphase;
// 
//    /**
//     * state (postconditions):
//     *  -1 not yet initialized
//     *   0 initialized init()
//     *   0.5 reSizePopulation
//     *   1 samplePopulation, sampleSingle, reSampleSingle
//     *   2.5 updateSingle
//     *   3 updateDistribution
//     */
//    double state = -1;
//    long citerlastwritten = 0;
//    long countwritten = 0;
//    int lockDimension = 0;
//    int mode = 0;
//    final int SINGLE_MODE = 1; // not in use anymore, keep for later developements?
//    final int PARALLEL_MODE = 2;
//
//    
//    long countCupdatesSinceEigenupdate;
    
//    double recentFunctionValue; 
//    double recentMaxFunctionValue;
//    double recentMinFunctionValue;
    int idxRecentOffspring; 
//    
    double ** arx;
//    SolutionSet * arx;
//    /** recent population, no idea whether this is useful to be public */
//    public double[][] population; // returned not as a copy
    double * xold;
//    
    double * BDz;
    double * artmp;
    
    double * init();
    SolutionSet * samplePopulation();
//    double ** samplePopulation();
    
//    double * resampleSingle(int index);
    
//    double ** genoPhenoTransformation(double ** popx, double ** popy);
    SolutionSet * genoPhenoTransformation(double ** popx, SolutionSet * popy);
    double * genoPhenoTransformation(double * popx, double * popy);

  public:
    CMAES(Problem * problem);
    SolutionSet * execute();
    
    
  
};

#endif /* __CMAES__ */
