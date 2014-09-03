//  PSO.cpp
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


#include <PSO.h>


/**
 * Class implementing a single-objective PSO algorithm
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
PSO::PSO(Problem *problem) : Algorithm(problem) {

  r1Max_ = 1.0;
  r1Min_ = 0.0;
  r2Max_ = 1.0;
  r2Min_ = 0.0;
  C1Max_ = 1.5;
  C1Min_ = 1.5;
  C2Max_ = 1.5;
  C2Min_ = 1.5;
  WMax_ = 0.9;
  WMin_ = 0.9;
  ChVel1_ = 1.0;
  ChVel2_ = 1.0;

  comparator_ = new ObjectiveComparator(0); // Single objective comparator
  map<string, void *> parameters; // Operator parameters

  parameters["comparator"] = comparator_;
  findBestSolution_ = new BestSolutionSelection(parameters);

  evaluations_ = 0;

} // PSO


/**
 * Initialize all parameter of the algorithm
 */
void PSO::initParams() {
  particlesSize_ = *(int *) getInputParameter("swarmSize");
  maxIterations_ = *(int *) getInputParameter("maxIterations");

  polynomialMutation_ = operators_["mutation"];

  iteration_ = 0;

  success_ = false;

  particles_ = new SolutionSet(particlesSize_);
  localBest_ = new Solution*[particlesSize_];

  // Create the speed_ vector
  speed_ = new double*[particlesSize_];

  deltaMax_ = new double[problem_->getNumberOfVariables()];
  deltaMin_ = new double[problem_->getNumberOfVariables()];
  for (int i = 0; i < problem_->getNumberOfVariables(); i++) {
    deltaMax_[i] = (problem_->getUpperLimit(i) -
      problem_->getLowerLimit(i)) / 2.0;
    deltaMin_[i] = -deltaMax_[i];
  } // for
} // initParams


/**
 * Initialize all parameter of the algorithm
 */
void PSO::deleteParams() {

  for (int i = 0; i < particlesSize_; i++) {
    delete [] speed_[i];
  }
  delete [] speed_;
  delete [] deltaMax_;
  delete [] deltaMin_;
  for (int i = 0; i < particles_->size(); i++) {
    delete localBest_[i];
  }
  delete [] localBest_;
  delete globalBest_;
  delete particles_;
  delete findBestSolution_;
  delete comparator_;

} // deleteParams


// Adaptive inertia
double PSO::inertiaWeight(int iter, int miter, double wmax, double wmin) {
  //return wmax;
  return wmax - (((wmax-wmin)*(double)iter)/(double)miter);
} // inertiaWeight


// constriction coefficient (M. Clerc)
double PSO::constrictionCoefficient(double c1, double c2) {
  double rho = c1 + c2;
  //rho = 1.0 ;
  if (rho <= 4) {
    return 1.0;
  } else {
    return 2 / fabs((2 - rho - sqrt(pow(rho, 2.0) - 4.0 * rho)));
  }
} // constrictionCoefficient


// velocity bounds
double PSO::velocityConstriction(double v, double * deltaMax,
                                    double * deltaMin, int variableIndex,
                                    int particleIndex) {

  return v;
  /*
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
  */
} // velocityConstriction


/**
 * Update the speed of each particle
 */
void PSO::computeSpeed(int iter, int miter) {
  double r1, r2;
  //double W ;
  double C1, C2;
  double wmax, wmin, deltaMax, deltaMin;
  XReal * bestGlobal;

  bestGlobal = new XReal(globalBest_) ;

  for (int i = 0; i < particlesSize_; i++) {
    XReal * particle = new XReal(particles_->get(i)) ;
    XReal * bestParticle = new XReal(localBest_[i]) ;

    //int bestIndividual = findBestSolution_->execute(particles_) ;

    r1 = PseudoRandom::randDouble(r1Min_, r1Max_);
    r2 = PseudoRandom::randDouble(r2Min_, r2Max_);
    //C1 = PseudoRandom::randDouble(C1Min_, C1Max_);
    //C2 = PseudoRandom::randDouble(C2Min_, C2Max_);
    C1 = 2.05;
    C2 = 2.05;
    //W =  PseudoRandom.randDouble(WMin_, WMax_);

    wmax = WMax_;
    wmin = WMin_;
    
    for (int var = 0; var < particle->size(); var++) {
      //Computing the velocity of this particle
      speed_[i][var] = constrictionCoefficient(C1, C2) *
        (speed_[i][var] +
        C1 * r1 * (bestParticle->getValue(var) - particle->getValue(var)) +
        C2 * r2 * (bestGlobal->getValue(var) - particle->getValue(var)));
    }

    /*
    for (int var = 0; var < particle->size(); var++) {
      //Computing the velocity of this particle
      speed_[i][var] = inertiaWeight(iter, miter, wmax, wmin) * speed_[i][var] +
        C1 * r1 * (bestParticle->getValue(var) - particle->getValue(var)) +
        C2 * r2 * (bestGlobal->getValue(var) - particle->getValue(var)) ;
    }
    */

    delete particle;
    delete bestParticle;

  }

  delete bestGlobal;

} // computeSpeed


/**
 * Update the position of each particle
 */
void PSO::computeNewPositions() {
  for (int i = 0; i < particlesSize_; i++) {
    //Variable ** particle = particles_->get(i)->getDecisionVariables();
    XReal * particle = new XReal(particles_->get(i)) ;
    //particle->move(speed_[i]);
    for (int var = 0; var < particle->size(); var++) {
      particle->setValue(var, particle->getValue(var) +  speed_[i][var]) ;

      if (particle->getValue(var) < problem_->getLowerLimit(var)) {
        particle->setValue(var, problem_->getLowerLimit(var));
        speed_[i][var] = speed_[i][var] * ChVel1_; //
      }
      if (particle->getValue(var) > problem_->getUpperLimit(var)) {
        particle->setValue(var, problem_->getUpperLimit(var));
        speed_[i][var] = speed_[i][var] * ChVel2_; //
      }

    }
    delete particle;
  }
} // computeNewPositions


/**
 * Apply a mutation operator to some particles in the swarm
 */
void PSO::mopsoMutation(int actualIteration, int totalIterations) {
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
 * Runs of the PSO algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet * PSO::execute() {

  initParams();

  success_ = false;
  globalBest_ =  NULL;

  //->Step 1 (and 3) Create the initial population and evaluate
  for (int i = 0; i < particlesSize_; i++) {
    Solution * particle = new Solution(problem_);
    problem_->evaluate(particle);
    evaluations_ ++;
    particles_->add(particle);
    if ((globalBest_ == NULL) || (particle->getObjective(0) < globalBest_->getObjective(0))) {
      if (globalBest_!= NULL) {
        delete globalBest_;
      }
      globalBest_ = new Solution(particle);
    }
  }

  //-> Step2. Initialize the speed_ of each particle to 0
  for (int i = 0; i < particlesSize_; i++) {
    speed_[i] = new double[problem_->getNumberOfVariables()];
    for (int j = 0; j < problem_->getNumberOfVariables(); j++) {
    speed_[i][j] = 0.0;
    }
  }

  //-> Step 6. Initialize the memory of each particle
  for (int i = 0; i < particles_->size(); i++) {
    Solution * particle = new Solution(particles_->get(i));
    localBest_[i] = particle;
  }

  //-> Step 7. Iterations ..
  while (iteration_ < maxIterations_) {
    int * bestIndividualPtr = (int*)findBestSolution_->execute(particles_);
    int bestIndividual = *bestIndividualPtr;
    delete bestIndividualPtr;
    computeSpeed(iteration_, maxIterations_);

    //Compute the new positions for the particles_
    computeNewPositions();

    //Mutate the particles_
    //mopsoMutation(iteration_, maxIterations_);

    //Evaluate the new particles_ in new positions
    for (int i = 0; i < particles_->size(); i++) {
      Solution * particle = particles_->get(i);
      problem_->evaluate(particle);
      evaluations_ ++;
    }

    //Actualize the memory of this particle
    for (int i = 0; i < particles_->size(); i++) {
     //int flag = comparator_.compare(particles_.get(i), localBest_[i]);
     //if (flag < 0) { // the new particle is best_ than the older remember
     if ((particles_->get(i)->getObjective(0) < localBest_[i]->getObjective(0))) {
       Solution * particle = new Solution(particles_->get(i));
       delete localBest_[i];
       localBest_[i] = particle;
     } // if
     if ((particles_->get(i)->getObjective(0) < globalBest_->getObjective(0))) {
       Solution * particle = new Solution(particles_->get(i));
       delete globalBest_;
       globalBest_ = particle;
     } // if

    }
    iteration_++;
  }

  // Return a population with the best individual
  SolutionSet * resultPopulation = new SolutionSet(1);
  int * bestIndexPtr = (int *)findBestSolution_->execute(particles_);
  int bestIndex = *bestIndexPtr;
  delete bestIndexPtr;
  Solution * s = particles_->get(bestIndex);
  resultPopulation->add(new Solution(s));

  // Free memory
  deleteParams();

  return resultPopulation;
} // execute
