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
#include <Comparator.h>
#include <ObjectiveComparator.h>

#include <UtilsCMAES.h>

#include <math.h>
#include <random>


/**
 * This class implements the CMA-ES algorithm.
 */

class CMAES : public Algorithm {

  private:
    
    /**
     * Stores the population size
     */
    int populationSize;
    
    int counteval;
    int maxEvaluations;
    
    double sigma;
    
    double * xmean;
    double * xold;
    
    /*
     * Strategy parameter setting: Selection
     */
    int mu;
    double * weights;
    double mueff;
    
    /*
     * Strategy parameter setting: Adaptation
     */
    double cc;
    double cs;
    double c1;
    double cmu;
    double damps;
    
    /*
     * Dynamic (internal) strategy parameters and constants
     */
    double * pc;
    double * ps;
    double ** B;
    double * diagD;
    double ** C;
    double ** invsqrtC;
    int eigeneval;
    double chiN;
    
    double ** arx;
    SolutionSet * population_;
    Solution * bestSolutionEver;
    
    void init();
    SolutionSet * samplePopulation();
    SolutionSet * genoPhenoTransformation(double ** popx);
    Solution * genoPhenoTransformation(double * x);
    bool isFeasible(Solution * solution);
    Solution * resampleSingle(int iNk);
    void storeBest(Comparator * comparator);
    void updateDistribution();
    void deleteParams();
    
  public:
    CMAES(Problem * problem);
    SolutionSet * execute();

};

#endif /* __CMAES__ */
