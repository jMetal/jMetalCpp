//  SMPSOD.cpp
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//
//  Copyright (c) 2014 Antonio J. Nebro
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


#include <SMPSOD.h>


/**
 * Constructor
 * @param problem Problem to solve
 */
SMPSOD::SMPSOD(Problem *problem) : Algorithm(problem) {
  r1Max  = 1.0;
  r1Min  = 0.0;
  r2Max  = 1.0;
  r2Min  = 0.0;
  C1Max  = 2.5;
  C1Min  = 1.5;
  C2Max  = 2.5;
  C2Min  = 1.5;
  WMax   = 0.4;
  WMin   = 0.1;
  ChVel1 = -1.0;
  ChVel2 = -1.0;
} // SMPSOD


/**
 * Initialize all parameter of the algorithm
 */
void SMPSOD::initParams() {
  particlesSize = *(int *) getInputParameter("swarmSize");
  maxIterations = *(int *) getInputParameter("maxIterations");

  //indicators = *(QualityIndicator *) getInputParameter("indicators");

  if (getInputParameter("functionType") != NULL) {
    string funcType = *(string *) getInputParameter("functionType");
    functionType = funcType;
  }

  iteration = 0 ;

  particles = new SolutionSet(particlesSize);
  lBest     = new Solution*[particlesSize];
  gBest     = new Solution*[particlesSize];

  // Create the speed_ vector
  speed = new double*[particlesSize];
  for (int i=0; i<particlesSize; i++) {
    speed[i] = new double[problem_->getNumberOfVariables()];
  }

  deltaMax = new double[problem_->getNumberOfVariables()];
  deltaMin = new double[problem_->getNumberOfVariables()];
  for (int i = 0; i < problem_->getNumberOfVariables(); i++) {
    deltaMax[i] = (problem_->getUpperLimit(i) -
        problem_->getLowerLimit(i)) / 2.0;
    deltaMin[i] = -deltaMax[i];
  } // for
} // initParams


/**
 * Free all the memory reserved by the algorithm
 */
void SMPSOD::deleteParams() {

  for (int i = 0; i < particlesSize; i++) {
      delete [] speed[i];
      delete [] neighborhood[i];
      delete gBest[i];
      delete lBest[i];
  }
  delete [] neighborhood;
  delete [] speed;
  delete [] gBest;
  delete [] lBest;
  delete particles;
  delete [] deltaMax;
  delete [] deltaMin;

  delete [] z;
  for (int i=0; i<particlesSize; i++) {
    delete [] lambda[i];
  }
  delete [] lambda;

} // deleteParams


/**
 * Adaptive inertia
 */
double SMPSOD::inertiaWeight(int iter, int miter, double wma, double wmin) {
  return wma; // - (((wma-wmin)*(double)iter)/(double)miter);
} // inertiaWeight


/**
 * constriction coefficient (M. Clerc)
 */
double SMPSOD::constrictionCoefficient(double c1, double c2) {
  double rho = c1 + c2;
  //rho = 1.0 ;
  if (rho <= 4) {
    return 1.0;
  } else {
    return 2 / (2 - rho - sqrt(pow(rho, 2.0) - 4.0 * rho));
  }
} // constrictionCoefficient


/**
 * velocity bounds
 */
double SMPSOD::velocityConstriction(double v, double *deltaMax,
    double *deltaMin, int variableIndex,
    int particleIndex) {

  double result;

  double dmax = deltaMax[variableIndex];
  double dmin = deltaMin[variableIndex];

  result = v;

  if (v > dmax) {
    result = dmax;
  }

  if (v < dmin) {
    result = dmin;
  }

  return result;
} // velocityConstriction


/**
 * Update the speed of each particle
 */
void SMPSOD::computeSpeed(int iter, int miter) {

  double r1, r2, W, C1, C2;
  double wmax, wmin;
  XReal *bestGlobal;

  for (int i = 0; i < particlesSize; i++) {
    XReal *particle     = new XReal(particles->get(i));
    XReal *bestParticle = new XReal(lBest[i]);

    bestGlobal = new XReal(gBest[i]);

    //Params for velocity equation
    r1 = PseudoRandom::randDouble(r1Min, r1Max);
    r2 = PseudoRandom::randDouble(r2Min, r2Max);
    C1 = PseudoRandom::randDouble(C1Min, C1Max);
    C2 = PseudoRandom::randDouble(C2Min, C2Max);
    W  = PseudoRandom::randDouble(WMin, WMax);

    wmax = WMax;
    wmin = WMin;

    for (int var = 0; var < particle->size(); var++) {
      //Computing the velocity of this particle
      speed[i][var] = velocityConstriction(constrictionCoefficient(C1, C2) *
                  (inertiaWeight(iter, miter, wmax, wmin) * speed[i][var] +
                      C1 * r1 * (bestParticle->getValue(var) -
                          particle->getValue(var)) +
                          C2 * r2 * (bestGlobal->getValue(var) -
                              particle->getValue(var))), deltaMax, deltaMin, var, i) ;
    }

    delete bestGlobal;
    delete particle;
    delete bestParticle;
  }
} // computeSpeed


/**
 * Update the position of each particle
 */
void SMPSOD::computeNewPositions() {

  for (int i = 0; i < particlesSize; i++) {
    XReal *particle = new XReal(particles->get(i)) ;
    for (int var = 0; var < particle->size(); var++) {
      particle->setValue(var, particle->getValue(var) + speed[i][var]) ;

      double c1 = PseudoRandom::randDouble(-1.0, 0.1);
      double c2 = PseudoRandom::randDouble(-1.0, 0.1);

      if (particle->getValue(var) < problem_->getLowerLimit(var)) {
        particle->setValue(var, problem_->getLowerLimit(var));
        speed[i][var] = speed[i][var] * ChVel1; //
        //speed[i][var] = speed[i][var] * c1; //
      }
      if (particle->getValue(var) > problem_->getUpperLimit(var)) {
        particle->setValue(var, problem_->getUpperLimit(var));
        speed[i][var] = speed[i][var] * ChVel2; //
        //speed[i][var] = speed[i][var] * c2; //
      }
    }
    problem_->evaluate(particles->get(i));
    updateReference(particles->get(i));
    delete particle;
  }

} // computeNewPositions


/**
 * Runs of the SMPSOD algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet *SMPSOD::execute() {

  initParams();

  //->Step 1 (and 3) Create the initial population and evaluate
  for (int i = 0; i < particlesSize; i++){
    Solution *particle = new Solution(problem_);
    problem_->evaluate(particle);
    problem_->evaluateConstraints(particle);
    particles->add(particle);
  }

  //-> Step2. Initialize the speed of each particle to 0
  for (int i = 0; i < particlesSize; i++) {
    for (int j = 0; j < problem_->getNumberOfVariables(); j++) {
      speed[i][j] = 0.0;
    }
  }

  // MOEA/D parameters
  T = 20;
  delta = 0.9;
  nr = 2;
  neighborhood = new int*[particlesSize];
  for (int i=0; i<particlesSize; i++) {
    neighborhood[i] = new int[T];
  }
  z = new double[problem_->getNumberOfObjectives()];
  lambda = new double*[particlesSize];
  for (int i=0; i<particlesSize; i++) {
    lambda[i] = new double[problem_->getNumberOfObjectives()];
  }
  initUniformWeight();
  initNeighborhood();
  initIdealPoint();

  //-> Step 6. Initialize the memory of each particle
  for (int i = 0; i < particles->size(); i++){
    lBest[i] = new Solution(particles->get(i));;
    gBest[i] = new Solution(particles->get(i));;
    updateGlobalBest(i,2);
  }

  //-> Step 7. Iterations ..
  while (iteration < maxIterations) {
    //Compute the speed_
    computeSpeed(iteration, maxIterations);

    //Compute the new positions for the particles_
    computeNewPositions();

    for (int i = 0; i < particles->size(); i++) {
      int type;
      double rnd = PseudoRandom::randDouble();

      // STEP 2.1. Mating selection based on probability
      if (rnd < delta) // if (rnd < realb)
      {
        type = 1;   // neighborhood
      } else {
        type = 2;   // whole population
      }

      updateLocalBest(particles->get(i), i, 1);
      updateGlobalBest(i, 2) ;
    }

    iteration++;
  }

  // Build the solution set result
  SolutionSet *result = new SolutionSet(particlesSize);
  for (int i=0;i<particlesSize;i++) {
    result->add(new Solution(gBest[i]));
  }

  // Free memory
  deleteParams();

  return result;
} // execute


/**
 * initUniformWeight
 */
void SMPSOD::initUniformWeight() {
  if ((problem_->getNumberOfObjectives() == 2) && (particlesSize < 300)) {
    for (int n = 0; n < particlesSize; n++) {
      double a = 1.0 * n / (particlesSize - 1);
      lambda[n][0] = a;
      lambda[n][1] = 1 - a;
    } // for
  } else {
    cerr << "Error at SMPSOD::initUniformWeight()." << endl;
    cerr << "Number of objectives greater than 2 or particles size greater than 300 " <<
        "is not yet supported." << endl;
    exit(-1);
  } // if
} // initUniformWeight


void SMPSOD::initNeighborhood() {
  double *x = new double[particlesSize];
  int *idx = new int[particlesSize];

  for (int i = 0; i < particlesSize; i++) {
    // calculate the distances based on weight vectors
    for (int j = 0; j < particlesSize; j++) {
      x[j] = UtilsMOEAD::distVector(lambda[i], lambda[j],
                            problem_->getNumberOfObjectives());
      idx[j] = j;
    } // for

    // find 'niche' nearest neighboring subproblems
    UtilsMOEAD::minFastSort(x, idx, particlesSize, T);

    for (int k = 0; k < T; k++) {
      neighborhood[i][k] = idx[k];
    }
  } // for

  delete [] idx;
  delete [] x;
} // initNeighborhood


void SMPSOD::initIdealPoint() {
  for (int i = 0; i < problem_->getNumberOfObjectives(); i++) {
    z[i] = 1.0e+30;
  } // for

  for (int i = 0; i < particlesSize; i++) {
    updateReference(particles->get(i));
  } // for
} // initIdealPoint


void SMPSOD::updateReference(Solution *individual) {
  for (int n = 0; n < problem_->getNumberOfObjectives(); n++) {
    if (individual->getObjective(n) < z[n]) {
      z[n] = individual->getObjective(n);
    }
  }
} // updateReference


void SMPSOD::updateGlobalBest(int solution, int type) {
  double gBestFitness;
  gBestFitness = fitnessFunction(gBest[solution], lambda[solution]) ;
  if (type == 1) {
    for (int i = 0 ; i < T; i++) { // T == neighborhood[i].size()
      double v1 = fitnessFunction(particles->get(neighborhood[solution][i]), lambda[solution]) ;
      double v2 = gBestFitness ;
      if (v1 < v2) {
        delete gBest[solution];
        gBest[solution] = new Solution(particles->get(i)) ;
        gBestFitness = fitnessFunction(gBest[solution], lambda[solution]) ;
      }
    }
  }
  else {
    for (int i = 0 ; i < particles->size(); i++) {
      double v1 = fitnessFunction(particles->get(i), lambda[solution]) ;
      double v2 = gBestFitness ;
      if (v1 < v2) {
        delete gBest[solution];
        gBest[solution] = new Solution(particles->get(i)) ;
        gBestFitness = fitnessFunction(gBest[solution], lambda[solution]) ;
      }
    }
  }
} // updateGlobalBest


void SMPSOD::updateLocalBest(Solution *indiv, int id, int type) {
  // indiv: child solution
  // id:   the id of current subproblem
  // type: update solutions in - neighborhood (1) or whole population (otherwise)
  int size;
  int time;

  time = 0;

  if (type == 1) {
    size = T; // = neighborhood[id].length;
  } else {
    size = particles->size();
  }
  int *perm = new int[size];

  UtilsMOEAD::randomPermutation(perm, size);

  for (int i = 0; i < size; i++) {
    int k;
    if (type == 1) {
      k = neighborhood[id][perm[i]];
    } else {
      k = perm[i];      // calculate the values of objective function regarding the current subproblem
    }
    double f1, f2;

    f1 = fitnessFunction(lBest[k], lambda[k]);
    f2 = fitnessFunction(indiv, lambda[k]);

    if (f2 < f1) {
      //particles_.replace(k, new Solution(indiv));
      delete lBest[k];
      lBest[k] = new Solution(indiv);
      //population[k].indiv = indiv;
      time++;
    }
    // the maximal number of solutions updated is not allowed to exceed 'limit'
    if (time >= nr) {
      break;
    }
  }

  delete [] perm;
} // updateProblem


double SMPSOD::fitnessFunction(Solution *sol, double *lambda) {
  double fitness = 0.0;

  if (functionType=="_TCHE") {
    double maxFun = -1.0e+30;

    for (int n = 0; n < problem_->getNumberOfObjectives(); n++) {
      double diff = fabs(sol->getObjective(n) - z[n]);

      double feval;
      if (lambda[n] == 0) {
        feval = 0.0001 * diff;
      } else {
        feval = diff * lambda[n];
      }
      if (feval > maxFun) {
        maxFun = feval;
      }
    } // for

    fitness = maxFun;

  } else if (functionType == "_AGG") {
    double sum = 0.0;
    for (int n = 0; n < problem_->getNumberOfObjectives(); n++) {
      sum += (lambda[n]) * sol->getObjective(n);
    }

    fitness = sum;

  } else if (functionType == "_PBI") {
    double d1, d2, nl;
    double theta = 5.0;

    d1 = d2 = nl = 0.0;

    for (int i = 0; i < problem_->getNumberOfObjectives(); i++) {
      d1 += (sol->getObjective(i) - z[i]) * lambda[i];
      nl += pow(lambda[i], 2.0);
    }
    nl = sqrt(nl);
    d1 = fabs(d1) / nl;

    for (int i = 0; i < problem_->getNumberOfObjectives(); i++) {
      d2 += pow((sol->getObjective(i) - z[i]) - d1 * (lambda[i] / nl), 2.0);
    }
    d2 = sqrt(d2);

    fitness = (d1 + theta * d2);

  } else {
    cerr << "FPSO.fitnessFunction: unknown type " << functionType << endl;
    exit(-1);
  }
  return fitness;
} // fitnessFunction
