//  CMAES.cpp
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


#include <CMAES.h>


/*
 * This class implements the CMA-ES algorithm.
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
CMAES::CMAES(Problem *problem) : Algorithm(problem) {
  bestSolutionEver = NULL;
} // CMAES


SolutionSet * CMAES::execute() {
  
  
  //Read the parameters
  populationSize = *(int *) getInputParameter("populationSize");
  maxEvaluations  = *(int *) getInputParameter("maxEvaluations");
  
  //Initialize the variables
  counteval = 0;
  
  Comparator * comparator = new ObjectiveComparator(0);

  init();
  
  // iteration loop
  while (counteval < maxEvaluations) {
    
    // --- core iteration step ---
    population_ = samplePopulation(); // get a new population of solutions
    
    for(int i = 0; i < populationSize; i++) {
      if (!isFeasible(population_->get(i))) {
        //cout << "RESAMPLING!" << endl;
        population_->replace(i, resampleSingle(i));
      }
      problem_->evaluate(population_->get(i));
    }
    counteval += populationSize;
    
    storeBest(comparator);
    //cout << counteval << ": " << bestSolutionEver->getObjective(0) << endl;
    updateDistribution();
    
    delete population_;
    
  }
  
  deleteParams();
  
  delete comparator ;
  
  SolutionSet * resultPopulation  = new SolutionSet(1) ;
  resultPopulation->add(bestSolutionEver) ;
  
  return resultPopulation ;
  
} // execute


void CMAES::init() {
  
  /*User defined input parameters */
  
  // number of objective variables/problem dimension
  int N = problem_->getNumberOfVariables();

  // objective variables initial point
  default_random_engine generator;
  xmean = new double[N];
  for (int i = 0; i < N; i++) {
    double stddev = (problem_->getUpperLimit(i) - problem_->getLowerLimit(i)) /2;
    double mean = problem_->getLowerLimit(i) + stddev;
    normal_distribution<double> distribution(mean,stddev/2);
    xmean[i] = distribution(generator);
    //xmean[i] = PseudoRandom::randDouble(0, 1);
  }
  
  // coordinate wise standard deviation (step size)
  sigma = 0.3;
  //sigma = 1;
  
  /* Strategy parameter setting: Selection */
  
  // population size, offspring number
  int lambda = populationSize;
  //lambda = 4+Math.floor(3*Math.log(N));
  
  // number of parents/points for recombination
  mu = (int) floor(lambda/2);
  
  // muXone array for weighted recombination
  weights = new double[mu];
  double sum = 0;
  for (int i=0; i<mu; i++) {
    weights[i] = (log(mu + 1/2) - log(i + 1));
    sum += weights[i];
  }
  // normalize recombination weights array
  for (int i=0; i<mu; i++) {
    weights[i] = weights[i]/sum;
  }
  
  // variance-effectiveness of sum w_i x_i
  double sum1 = 0;
  double sum2 = 0;
  for (int i = 0; i < mu; i++) {
    sum1 += weights[i];
    sum2 += weights[i] * weights[i];
  }
  
  mueff = sum1 * sum1 / sum2;
  
  /* Strategy parameter setting: Adaptation */
  
  // time constant for cumulation for C
  cc = (4 + mueff/N) / (N + 4 + 2*mueff/N);
  
  // t-const for cumulation for sigma control
  cs = (mueff + 2) / (N + mueff + 5);
  
  // learning rate for rank-one update of C
  c1 = 2 / ((N+1.3)*(N+1.3) + mueff);
  
  // learning rate for rank-mu update
  cmu = fmin(1 - c1, 2 * (mueff - 2 + 1/mueff) / ((N+2)*(N+2) + mueff));
  
  // damping for sigma, usually close to 1
  damps = 1 + 2 * fmax(0, sqrt((mueff - 1) / (N+1)) -1) + cs;
  
  /* Initialize dynamic (internal) strategy parameters and constants */
  
  // diagonal D defines the scaling
  diagD = new double[N];
  
  // evolution paths for C and sigma
  pc = new double[N];
  ps = new double[N];
  
  // B defines the coordinate system
  B  = new double*[N];
  // covariance matrix C
  C  = new double*[N];
  for (int i = 0; i < N; i++) {
    B[i] = new double[N];
    C[i] = new double[N];
  }
  
  // C^-1/2
  invsqrtC = new double*[N];
  for (int i = 0; i < N; i++) {
    invsqrtC[i] = new double[N];
    pc[i] = 0;
    ps[i] = 0;
    diagD[i] = 1;
    for (int j = 0; j < N; j++) {
      B[i][j] = 0;
      invsqrtC[i][j] = 0;
    }
    for (int j = 0; j < i; j++) {
      C[i][j] = 0;
    }
    B[i][i] = 1;
    C[i][i] = diagD[i] * diagD[i];
    invsqrtC[i][i] = 1;
  }
  
  // track update of B and D
  eigeneval = 0;
  
  chiN = sqrt(N) * ( 1 - 1/(4*N) + 1/(21*N*N) );
  
  /* non-settable parameters */
  
  xold = new double[N];
  arx = new double*[lambda];
  for (int i = 0; i < lambda; i++) {
    arx[i] = new double[N];
  }
  
} // init


SolutionSet * CMAES::samplePopulation() {
  
  default_random_engine generator;
  normal_distribution<double> distribution(0.0,1.0);
  
  int N = problem_->getNumberOfVariables();
  double * artmp = new double[N];
  double sum;
  
  for (int iNk = 0; iNk < populationSize; iNk++) {
    
    for (int i = 0; i < N; i++) {
      //artmp[i] = diagD[i] * PseudoRandom::randDouble(-2, 2);
      artmp[i] = diagD[i] * distribution(generator);
    }
    for (int i = 0; i < N; i++) {
      sum = 0.0;
      for (int j = 0; j < N; j++) {
        sum += B[i][j] * artmp[j];
      }
      arx[iNk][i] = xmean[i] + sigma * sum;
    }
  }
  
  delete [] artmp;
  
  return genoPhenoTransformation(arx);
  
} // samplePopulation


SolutionSet * CMAES::genoPhenoTransformation(double ** popx) {

  SolutionSet * population_ = new SolutionSet(populationSize);
  for (int i = 0; i < populationSize; i++) {
    Solution * solution = new Solution(problem_);
    for (int j = 0; j < problem_->getNumberOfVariables(); j++) {
      solution->getDecisionVariables()[j]->setValue(popx[i][j]);
    }
    population_->add(solution);
  }
  return population_;

} // genoPhenoTransformation


bool CMAES::isFeasible(Solution * solution) {

  bool res = true;
  Variable ** x = solution->getDecisionVariables();

  for (int i = 0; i < problem_->getNumberOfVariables(); i++) {
    double value = x[i]->getValue();
    if ((value < problem_->getLowerLimit(i)) || (value > problem_->getUpperLimit(i))) {
      res = false;
    }
  }
  return res;

} // isFeasible


Solution * CMAES::resampleSingle(int iNk) {

  for (int i = 0; i < problem_->getNumberOfVariables(); i++) {
    if (arx[iNk][i] > problem_->getUpperLimit(i)) {
      arx[iNk][i] = problem_->getUpperLimit(i);
    } else if (arx[iNk][i] < problem_->getLowerLimit(i)) {
      arx[iNk][i] = problem_->getLowerLimit(i);
    }
  }

  return genoPhenoTransformation(arx[iNk]);

} // resampleSingle


Solution * CMAES::genoPhenoTransformation(double * x) {

  Solution * solution = new Solution(problem_);
  for (int i = 0; i < problem_->getNumberOfVariables(); i++) {
    solution->getDecisionVariables()[i]->setValue(x[i]);
  }
  return solution;

} // genoPhenoTransformation


void CMAES::storeBest(Comparator * comparator) {

  Solution * bestInPopulation = new Solution(population_->best(comparator));
  if ((bestSolutionEver == NULL) ||
          (bestSolutionEver->getObjective(0)
          > bestInPopulation->getObjective(0))) {
    if (bestSolutionEver != NULL) {
      delete bestSolutionEver;
    }
    bestSolutionEver = bestInPopulation;
  } else {
    delete bestInPopulation;
  }

} // storeBest
  

void CMAES::updateDistribution() {
  
  int N = problem_->getNumberOfVariables();
  int lambda = populationSize;
  
  double * arfitness = new double[lambda];
  int * arindex = new int[lambda];
  
  /* Sort by fitness and compute weighted mean into xmean */
  
  //minimization
  for (int i = 0; i < lambda; i++) {
    arfitness[i] = population_->get(i)->getObjective(0);
    arindex[i] = i;
  }
  UtilsCMAES::minFastSort(arfitness, arindex, lambda);
  
  // calculate xmean and BDz~N(0,C)
  for (int i = 0; i < N; i++) {
    xold[i] = xmean[i];
    xmean[i] = 0.;
    for (int iNk = 0; iNk < mu; iNk++) {
      xmean[i] += weights[iNk] * arx[arindex[iNk]][i];
    }
    //BDz[i] = sqrt(sp->getMueff()) * (xmean[i] - xold[i]) / sigma;
  }
  
  /* Cumulation: Update evolution paths */
  
  double * artmp = new double[N];
  for (int i = 0; i < N; i++) {
    artmp[i] = 0;
    //double value = (xmean[i] - xold[i]) / sigma;
    for (int j = 0; j < N; j++) {
      //artmp[i] += invsqrtC[i][j] * value;
      artmp[i] += invsqrtC[i][j] * (xmean[j] - xold[j]) / sigma;
    }
  }
  // cumulation for sigma (ps)
  for (int i = 0; i < N; i++) {
    ps[i] = (1. - cs) * ps[i]
        + sqrt(cs * (2. - cs) * mueff)
        * artmp[i];
  }
  
  // calculate norm(ps)^2
  double psxps = 0.0;
  for (int i = 0; i < N; i++) {
    psxps += ps[i] * ps[i];
  }
  
  // cumulation for covariance matrix (pc)
  int hsig = 0;
  if ((sqrt(psxps) / sqrt(1. - pow(1. - cs, 2. * counteval/lambda)) / chiN)
          < (1.4 + 2. / (N + 1.))) {
    hsig = 1;
  }
  for (int i = 0; i < N; i++) {
    pc[i] = (1. - cc) * pc[i]
            + hsig * sqrt(cc * (2. - cc) * mueff) * (xmean[i] - xold[i]) / sigma;
  }
  
  /* Adapt covariance matrix C */
  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      C[i][j] =  (1 - c1 -cmu)
              * C[i][j]
              + c1
              * (pc[i] * pc[j] + (1 - hsig) * cc
              * (2. - cc) * C[i][j]);
      for (int k = 0; k < mu; k++) {
        /*
         * additional rank mu
         * update
         */
        C[i][j] += cmu
                * weights[k]
                * (arx[arindex[k]][i] - xold[i])
                * (arx[arindex[k]][j] - xold[j]) / sigma
                / sigma;
      }
    }
  }
  
  /* Adapt step size sigma */
  
  sigma *= exp((cs/damps) * (sqrt(psxps)/chiN - 1));
  
  /* Decomposition of C into B*diag(D.^2)*B' (diagonalization) */
  
  if (counteval - eigeneval > lambda /(c1+cmu)/N/10) { // to achieve O(N^2)
    
    eigeneval = counteval;
    
    // enforce symmetry
    for (int i = 0; i < N; i++) {
      for (int j = 0; j <= i; j++) {
        B[i][j] = B[j][i] = C[i][j];
      }
    }
    
    // eigen decomposition, B==normalized eigenvectors
    double * offdiag = new double[N];
    UtilsCMAES::tred2(N, B, diagD, offdiag);
    UtilsCMAES::tql2(N, diagD, offdiag, B);
    if (UtilsCMAES::checkEigenSystem(N, C, diagD, B) > 0) { // for debugging
      counteval = maxEvaluations;
    }
    
    for (int i = 0; i < N; i++) {
      if (diagD[i] < 0) { // numerical problem?
        cerr << "CMAES::updateDistribution(): WARNING - an eigenvalue has become negative." << endl;
        counteval = maxEvaluations;
        //throw new JMException("Exception in CMAES.execute(): an eigenvalue has become negative.") ;
      }
      diagD[i] = sqrt(diagD[i]);
    }
    // diagD is a vector of standard deviations now
    
    //invsqrtC = B * diag(D.^-1) * B';
    double ** artmp2 = new double*[N];
    for (int i = 0; i < N; i++) {
      artmp2[i] = new double[N];
      //double value = (xmean[i] - xold[i]) / sigma;
      for (int j = 0; j < N; j++) {
        artmp2[i][j] = B[i][j] * (1/diagD[j]);
      }
    }
    for (int i = 0; i < N; i++) {
      //double value = (xmean[i] - xold[i]) / sigma;
      for (int j = 0; j < N; j++) {
        invsqrtC[i][j] = 0.0;
        for (int k = 0; k < N; k++) {
          invsqrtC[i][j] += artmp2[i][k] * B[j][k];
        }
      }
    }
    
    for (int i = 0; i < N; i++) {
      delete [] artmp2[i];
    }
    delete [] offdiag;
    delete [] artmp2;

  }
  
  delete [] arfitness;
  delete [] arindex;
  delete [] artmp;

} // updateDistribution()


void CMAES::deleteParams() {
  int N = problem_->getNumberOfVariables();
  int lambda = populationSize;
  delete [] xmean;
  delete [] weights;
  delete [] diagD;
  delete [] pc;
  delete [] ps;
  for (int i = 0; i < N; i++) {
    delete [] B[i];
    delete [] C[i];
    delete [] invsqrtC[i];
  }
  delete [] B;
  delete [] C;
  delete [] invsqrtC;
  delete [] xold;
  for (int i = 0; i < lambda; i++) {
    delete [] arx[i];
  }
  delete [] arx;
} // freeMemory
