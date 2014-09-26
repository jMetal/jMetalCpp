//  SMPSO.cpp
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


#include <SMPSO.h>


/*
 * This class implements the SMPSO algorithm.
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
SMPSO::SMPSO(Problem *problem) : Algorithm(problem) {
  r1Max_ = 1.0;
  r1Min_ = 0.0;
  r2Max_ = 1.0;
  r2Min_ = 0.0;
  C1Max_ = 2.5;
  C1Min_ = 1.5;
  C2Max_ = 2.5;
  C2Min_ = 1.5;
  WMax_ = 0.1;
  WMin_ = 0.1;
  ChVel1_ = -1;
  ChVel2_ = -1;
} // SMPSO


/**
 * Initialize all parameter of the algorithm
 */
void SMPSO::initParams() {
  swarmSize_ = *(int *) getInputParameter("swarmSize");
  archiveSize_ = *(int *) getInputParameter("archiveSize");
  maxIterations_ = *(int *) getInputParameter("maxIterations");
  
  setAlgParams();
  
  // TODO: indicators_ = (QualityIndicator) getInputParameter("indicators");

  polynomialMutation_ = operators_["mutation"] ;

  iteration_ = 0 ;

  success_ = false;

  particles_ = new SolutionSet(swarmSize_);
  best_ = new Solution*[swarmSize_];
  leaders_ = new CrowdingArchive(archiveSize_, problem_->getNumberOfObjectives());

  // Create comparators for dominance and crowding distance
  dominance_ = new DominanceComparator();
  crowdingDistanceComparator_ = new CrowdingDistanceComparator();
  distance_ = new Distance();

  // Create the speed_ vector
  int numberOfVariables = problem_->getNumberOfVariables();
  //speed_ = new double[swarmSize_][numberOfVariables];
  speed_ = new double*[swarmSize_];
  // TODO: Liberar memoria al finalizar

  deltaMax_ = new double[problem_->getNumberOfVariables()];
  deltaMin_ = new double[problem_->getNumberOfVariables()];
  for (int i = 0; i < problem_->getNumberOfVariables(); i++) {
    deltaMax_[i] = (problem_->getUpperLimit(i) -
      problem_->getLowerLimit(i)) / 2.0;
    deltaMin_[i] = -deltaMax_[i];
  } // for
} // initParams
  
/**
 * Read all user input parameters
 * Possible params: r1Max, r1Min, r2Max, r2Min, C1Max, C1Min, C2Max, C2Min,
 *   WMax, Wmin, ChVel1, ChVel2
 */
void SMPSO::setAlgParams() {
  
  void * r1MaxPtr   = getInputParameter("r1Max");
  void * r1MinPtr   = getInputParameter("r1Min");
  void * r2MaxPtr   = getInputParameter("r2Max");
  void * r2MinPtr   = getInputParameter("r2Min");
  void * C1MaxPtr   = getInputParameter("C1Min");
  void * C1MinPtr   = getInputParameter("C1Max");
  void * C2MaxPtr   = getInputParameter("C2Max");
  void * C2MinPtr   = getInputParameter("C2Min");
  void * WMaxPtr    = getInputParameter("WMax");
  void * WMinPtr    = getInputParameter("WMin");
  void * ChVel1Ptr  = getInputParameter("ChVel1");
  void * ChVel2Ptr  = getInputParameter("ChVel2");
  
  if (r1MaxPtr != NULL) r1Max_ = * (double *) r1MaxPtr;
  if (r1MinPtr != NULL) r1Min_ = * (double *) r1MinPtr;
  if (r2MaxPtr != NULL) r2Max_ = * (double *) r2MaxPtr;
  if (r2MinPtr != NULL) r2Min_ = * (double *) r2MinPtr;
  if (C1MaxPtr != NULL) C1Max_ = * (double *) C1MaxPtr;
  if (C1MinPtr != NULL) C1Min_ = * (double *) C1MinPtr;
  if (C2MaxPtr != NULL) C2Max_ = * (double *) C2MaxPtr;
  if (C2MinPtr != NULL) C2Min_ = * (double *) C2MinPtr;
  if (WMaxPtr != NULL) WMax_ = * (double *) WMaxPtr;
  if (WMinPtr != NULL) WMin_ = * (double *) WMinPtr;
  if (ChVel1Ptr != NULL) ChVel1_ = * (double *) ChVel1Ptr;
  if (ChVel2Ptr != NULL) ChVel2_ = * (double *) ChVel2Ptr;

} // setAlgParams


/**
 * Free all the memory reserved by the algorithm
 */
void SMPSO::deleteParams() {

  for (int i = 0; i < swarmSize_; i++) {
    delete [] speed_[i];
  }
  delete [] speed_;
  delete dominance_;
  delete crowdingDistanceComparator_;
  delete distance_;
  delete [] deltaMax_;
  delete [] deltaMin_;
  delete particles_;
  for (int i = 0; i < swarmSize_; i++) {
    delete best_[i];
  }
  delete [] best_;
  delete leaders_;

} // deleteParams


// Adaptive inertia
double SMPSO::inertiaWeight(int iter, int miter, double wma, double wmin) {
  return wma; // - (((wma-wmin)*(double)iter)/(double)miter);
} // inertiaWeight


// constriction coefficient (M. Clerc)
double SMPSO::constrictionCoefficient(double c1, double c2) {
  double rho = c1 + c2;
  //rho = 1.0 ;
  if (rho <= 4) {
    return 1.0;
  } else {
    return 2 / (2 - rho - sqrt(pow(rho, 2.0) - 4.0 * rho));
  }
} // constrictionCoefficient


// velocity bounds
double SMPSO::velocityConstriction(double v, double * deltaMax,
                                    double * deltaMin, int variableIndex,
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
void SMPSO::computeSpeed(int iter, int miter) {
  double r1, r2, W, C1, C2;
  double wmax, wmin, deltaMax, deltaMin;
  XReal * bestGlobal;

  for (int i = 0; i < swarmSize_; i++) {
    XReal * particle = new XReal(particles_->get(i)) ;
    XReal * bestParticle = new XReal(best_[i]) ;

    //Select a global best_ for calculate the speed of particle i, bestGlobal
    Solution * one;
    Solution * two;
    int pos1 = PseudoRandom::randInt(0, leaders_->size() - 1);
    int pos2 = PseudoRandom::randInt(0, leaders_->size() - 1);
    one = leaders_->get(pos1);
    two = leaders_->get(pos2);

    if (crowdingDistanceComparator_->compare(one, two) < 1) {
      bestGlobal = new XReal(one);
    } else {
      bestGlobal = new XReal(two);
    }
    //Params for velocity equation
    r1 = PseudoRandom::randDouble(r1Min_, r1Max_);
    r2 = PseudoRandom::randDouble(r2Min_, r2Max_);
    C1 = PseudoRandom::randDouble(C1Min_, C1Max_);
    C2 = PseudoRandom::randDouble(C2Min_, C2Max_);
    W  = PseudoRandom::randDouble(WMin_, WMax_);
    //
    wmax = WMax_;
    wmin = WMin_;

    for (int var = 0; var < particle->getNumberOfDecisionVariables(); var++) {
      //Computing the velocity of this particle
      speed_[i][var] = velocityConstriction(constrictionCoefficient(C1, C2) *
        (inertiaWeight(iter, miter, wmax, wmin) *
        speed_[i][var] +
        C1 * r1 * (bestParticle->getValue(var) -
        particle->getValue(var)) +
        C2 * r2 * (bestGlobal->getValue(var) -
        particle->getValue(var))), deltaMax_, //[var],
        deltaMin_, //[var],
        var,
        i);
    } // for

    delete bestGlobal;
    delete particle;
    delete bestParticle;

  }// for

} // computeSpeed


/**
 * Update the position of each particle
 */
void SMPSO::computeNewPositions() {
  for (int i = 0; i < swarmSize_; i++) {
    XReal * particle = new XReal(particles_->get(i)) ;
    for (int var = 0; var < particle->getNumberOfDecisionVariables(); var++) {
      particle->setValue(var, particle->getValue(var) +  speed_[i][var]) ;

      if (particle->getValue(var) < problem_->getLowerLimit(var)) {
        particle->setValue(var, problem_->getLowerLimit(var));
        speed_[i][var] = speed_[i][var] * ChVel1_; //
      }
      if (particle->getValue(var) > problem_->getUpperLimit(var)) {
        particle->setValue(var, problem_->getUpperLimit(var));
        speed_[i][var] = speed_[i][var] * ChVel2_; //
      }
    }// for
    delete particle;
  }// for
} // computeNewPositions


/**
 * Apply a mutation operator to some particles in the swarm
 */
void SMPSO::mopsoMutation(int actualIteration, int totalIterations) {
  for (int i = 0; i < particles_->size(); i++) {
    if ( (i % 6) == 0)
      polynomialMutation_->execute(particles_->get(i));
    //if (i % 3 == 0) { //particles_ mutated with a non-uniform mutation %3
    //  nonUniformMutation_.execute(particles_.get(i));
    //} else if (i % 3 == 1) { //particles_ mutated with a uniform mutation operator
    //  uniformMutation_.execute(particles_.get(i));
    //} else //particles_ without mutation
    //;
  }
} // mopsoMutation


/**
 * Runs of the SMPSO algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet * SMPSO::execute() {

  initParams();

  success_ = false;
  //->Step 1 (and 3) Create the initial population and evaluate
  for (int i = 0; i < swarmSize_; i++) {
    Solution * particle = new Solution(problem_);
    problem_->evaluate(particle);
    problem_->evaluateConstraints(particle);
    particles_->add(particle);
  }

  //-> Step2. Initialize the speed_ of each particle to 0
  for (int i = 0; i < swarmSize_; i++) {
    speed_[i] = new double[problem_->getNumberOfVariables()];
    for (int j = 0; j < problem_->getNumberOfVariables(); j++) {
      speed_[i][j] = 0.0;
    }
  }

  // Step4 and 5
  for (int i = 0; i < particles_->size(); i++) {
    Solution * particle = new Solution(particles_->get(i));
    bool isAdded = leaders_->add(particle);
    if (isAdded == false) {
      delete particle;
    }
  }

  //-> Step 6. Initialize the memory of each particle
  for (int i = 0; i < particles_->size(); i++) {
    Solution * particle = new Solution(particles_->get(i));
    best_[i] = particle;
  }

  //Crowding the leaders_
  distance_->crowdingDistanceAssignment(leaders_, problem_->getNumberOfObjectives());

  //-> Step 7. Iterations ..
  while (iteration_ < maxIterations_) {
//    try {
//      //Compute the speed_
//      computeSpeed(iteration_, maxIterations_);
//    } catch (IOException ex) {
//      Logger.getLogger(SMPSO.class.getName()).log(Level.SEVERE, null, ex);
//    }
    computeSpeed(iteration_, maxIterations_);

    //Compute the new positions for the particles_
    computeNewPositions();

    //Mutate the particles_
    mopsoMutation(iteration_, maxIterations_);

    //Evaluate the new particles_ in new positions
    for (int i = 0; i < particles_->size(); i++) {
      Solution * particle = particles_->get(i);
      problem_->evaluate(particle);
      problem_->evaluateConstraints(particle);
    }

    //Update the archive
    for (int i = 0; i < particles_->size(); i++) {
      Solution * particle = new Solution(particles_->get(i));
      bool isAdded = leaders_->add(particle);
      if (isAdded == false) {
        delete particle;
      }
    }

    //Update the memory of this particle
    for (int i = 0; i < particles_->size(); i++) {
      int flag = dominance_->compare(particles_->get(i), best_[i]);
      if (flag != 1) { // the new particle is best_ than the older remembered
        Solution * particle = new Solution(particles_->get(i));
        delete best_[i];
        best_[i] = particle;
      }
    }

    //Assign crowding distance to the leaders_
    distance_->crowdingDistanceAssignment(leaders_,
      problem_->getNumberOfObjectives());
    iteration_++;
  }

  // Build the solution set result
  SolutionSet * result = new SolutionSet(leaders_->size());
  for (int i=0;i<leaders_->size();i++) {
    result->add(new Solution(leaders_->get(i)));
  }

  // Free memory
  deleteParams();

  return result;
} // execute
