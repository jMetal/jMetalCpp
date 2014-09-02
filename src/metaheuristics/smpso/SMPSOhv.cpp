//  SMPSOhv.cpp
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


#include <SMPSOhv.h>


/**
 * This class implements an asynchronous version of OMOPSO algorithm
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
SMPSOhv::SMPSOhv(Problem *problem) : Algorithm(problem) {
  r1Max  = 1.0;
  r1Min  = 0.0;
  r2Max  = 1.0;
  r2Min  = 0.0;
  C1Max  = 2.5;
  C1Min  = 1.5;
  C2Max  = 2.5;
  C2Min  = 1.5;
  WMax   = 0.1;
  WMin   = 0.1;
  ChVel1 = -1;
  ChVel2 = -1;
} // SMPSOhv


/**
 * Initialize all parameter of the algorithm
 */
void SMPSOhv::initParams() {
  swarmSize     = *(int *) getInputParameter("swarmSize");
  archiveSize   = *(int *) getInputParameter("archiveSize");
  maxIterations = *(int *) getInputParameter("maxIterations");

  //indicators = *(QualityIndicator *) getInputParameter("indicators");

  polynomialMutation = operators_["mutation"] ;

  iteration = 0;

  particles     = new SolutionSet(swarmSize);
  best          = new Solution*[swarmSize];
  leaders       = new FastHypervolumeArchive(archiveSize,problem_->getNumberOfObjectives());

  // Create the dominator for equadless and dominance
  dominance          = new DominanceComparator();
  crowdingDistanceComparator = new CrowdingDistanceComparator();
  distance           = new Distance();

  // Create the speed_ vector
  speed = new double*[swarmSize];

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
void SMPSOhv::deleteParams() {

  for (int i = 0; i < swarmSize; i++) {
      delete [] speed[i];
  }
  delete [] speed;
  delete dominance;
  delete crowdingDistanceComparator;
  delete distance;
  delete particles;
  for (int i = 0; i < swarmSize; i++) {
      delete best[i];
  }
  delete [] best;
  delete [] deltaMax;
  delete [] deltaMin;
  delete leaders;

} // deleteParams


/**
 * Adaptive inertia
 */
double SMPSOhv::inertiaWeight(int iter, int miter, double wma, double wmin) {
  return wma; // - (((wma-wmin)*(double)iter)/(double)miter);
} // inertiaWeight


/**
 * constriction coefficient (M. Clerc)
 */
double SMPSOhv::constrictionCoefficient(double c1, double c2) {
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
double SMPSOhv::velocityConstriction(double v, double *deltaMax,
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
void SMPSOhv::computeSpeed(int iter, int miter) {
  double r1, r2, W, C1, C2;
  double wmax, wmin;
  XReal *bestGlobal;

  for (int i = 0; i < swarmSize; i++) {
    XReal *particle     = new XReal(particles->get(i));
    XReal *bestParticle = new XReal(best[i]);

    //Select a global best for calculate the speed of particle i, bestGlobal
    Solution *one, *two;
    int pos1 = PseudoRandom::randInt(0,leaders->size()-1);

    //int pos1 = PseudoRandom::randInt(0,leaders->size()-1);
    int pos2 = PseudoRandom::randInt(0,leaders->size()-1);
    one = leaders->get(pos1);
    two = leaders->get(pos2);

    if (crowdingDistanceComparator->compare(one,two) < 1) {
      bestGlobal = new XReal(one);
    } else {
      bestGlobal = new XReal(two);
    }

    //Params for velocity equation
    r1 = PseudoRandom::randDouble(r1Min, r1Max);
    r2 = PseudoRandom::randDouble(r2Min, r2Max);
    C1 = PseudoRandom::randDouble(C1Min, C1Max);
    C2 = PseudoRandom::randDouble(C2Min, C2Max);
    W  = PseudoRandom::randDouble(WMin, WMax);

    wmax = WMax;
    wmin = WMin;

    for (int var = 0; var < particle->getNumberOfDecisionVariables(); var++) {
      //Computing the velocity of this particle
      speed[i][var] = velocityConstriction(constrictionCoefficient(C1, C2) *
                  (inertiaWeight(iter, miter, wmax, wmin) *
                      speed[i][var] +
                      C1 * r1 * (bestParticle->getValue(var) -
                          particle->getValue(var)) +
                          C2 * r2 * (bestGlobal->getValue(var) -
                              particle->getValue(var))), deltaMax,
                              deltaMin,
                              var,
                              i);
    }
    delete bestGlobal;
    delete particle;
    delete bestParticle;
  }
} // computeSpeed


/**
 * Update the position of each particle
 */
void SMPSOhv::computeNewPositions() {

  for (int i = 0; i < swarmSize; i++) {
    XReal * particle = new XReal(particles->get(i));
    for (int var = 0; var < particle->getNumberOfDecisionVariables(); var++) {
      particle->setValue(var, particle->getValue(var) + speed[i][var]);

      if (particle->getValue(var) < problem_->getLowerLimit(var)) {
        particle->setValue(var, problem_->getLowerLimit(var));
        speed[i][var] = speed[i][var] * ChVel1;
      }
      if (particle->getValue(var) > problem_->getUpperLimit(var)){
        particle->setValue(var, problem_->getUpperLimit(var));
        speed[i][var] = speed[i][var] * ChVel2;
      }
    }
    delete particle;
  }

} // computeNewPositions


/**
 * Apply a mutation operator to some particles in the swarm
 */
void SMPSOhv::mopsoMutation(int actualIteration, int totalIterations) {
  for (int i = 0; i < particles->size(); i++) {
    if ( (i % 6) == 0) {
      polynomialMutation->execute(particles->get(i));
    }
  }
} // mopsoMutation


/**
 * Runs of the SMPSO algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet *SMPSOhv::execute() {

  initParams();

  success = false;
  //->Step 1 (and 3) Create the initial population and evaluate
  for (int i = 0; i < swarmSize; i++){
    Solution *particle = new Solution(problem_);
    problem_->evaluate(particle);
    problem_->evaluateConstraints(particle);
    particles->add(particle);
  }

  //-> Step2. Initialize the speed of each particle to 0
  for (int i = 0; i < swarmSize; i++) {
    speed[i] = new double[problem_->getNumberOfVariables()];
    for (int j = 0; j < problem_->getNumberOfVariables(); j++) {
      speed[i][j] = 0.0;
    }
  }

  // Step4 and 5
  for (int i = 0; i < particles->size(); i++){
    Solution *particle = new Solution(particles->get(i));
    if (leaders->add(particle) == false){
      delete particle;
    }
  }

  //-> Step 6. Initialize the memory of each particle
  for (int i = 0; i < particles->size(); i++){
    Solution *particle = new Solution(particles->get(i));
    best[i] = particle;
  }

  //Crowding the leaders_
  //distance->crowdingDistanceAssignment(leaders, problem_->getNumberOfObjectives());
  leaders->computeHVContribution();

  //-> Step 7. Iterations ..
  while (iteration < maxIterations) {
    //Compute the speed_
    computeSpeed(iteration, maxIterations);

    //Compute the new positions for the particles_
    computeNewPositions();

    //Mutate the particles_
    mopsoMutation(iteration,maxIterations);

    //Evaluate the new particles in new positions
    for (int i = 0; i < particles->size(); i++){
      Solution *particle = particles->get(i);
      problem_->evaluate(particle);
      problem_->evaluateConstraints(particle);
    }

    //Update the archive
    for (int i = 0; i < particles->size(); i++) {
      Solution *particle = new Solution(particles->get(i));
      if (leaders->add(particle) == false) {
        delete particle;
      }
    }

    //Update the memory of this particle
    for (int i = 0; i < particles->size(); i++) {
      int flag = dominance->compare(particles->get(i), best[i]);
      if (flag != 1) { // the new particle is best_ than the older remembered
        Solution *particle = new Solution(particles->get(i));
        delete best[i];
        best[i] = particle;
      }
    }

    iteration++;
  }

  // Build the solution set result
  SolutionSet * result = new SolutionSet(leaders->size());
  for (int i=0;i<leaders->size();i++) {
    result->add(new Solution(leaders->get(i)));
  }

  // Free memory
  deleteParams();

  return result;
} // execute
