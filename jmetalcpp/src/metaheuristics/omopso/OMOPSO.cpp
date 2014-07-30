//  OMOPSO.cpp
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


#include <OMOPSO.h>


/**
 * This class implements an asynchronous version of OMOPSO algorithm
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
OMOPSO::OMOPSO(Problem *problem) : Algorithm(problem) {
} // OMOPSO


/**
 * Initialize all parameter of the algorithm
 */
void OMOPSO::initParams() {
    
  particlesSize = *(int *) getInputParameter("swarmSize");
  archiveSize   = *(int *) getInputParameter("archiveSize");
  maxIterations = *(int *) getInputParameter("maxIterations");

  iteration = 0;

  particles     = new SolutionSet(particlesSize);
  best          = new Solution*[particlesSize];
  leaders       = new CrowdingArchive(archiveSize,problem_->getNumberOfObjectives());
  eArchive      = new NonDominatedSolutionList(new EpsilonDominanceComparator(eta));

  uniformMutation = operators_["uniformMutation"] ;
  nonUniformMutation = operators_["nonUniformMutation"] ;

  // Create the dominator for equadless and dominance
  dominance          = new DominanceComparator();
  crowdingDistanceComparator = new CrowdingDistanceComparator();
  distance           = new Distance();

  // Create the speed_ vector
  speed = new double*[particlesSize];

} // initParams


/**
 * Free all the memory reserved by the algorithm
 */
void OMOPSO::deleteParams() {
    
  for (int i = 0; i < particlesSize; i++) {
      delete [] speed[i];
  }
  delete [] speed;
  delete dominance;
  delete crowdingDistanceComparator;
  delete distance;
  delete particles;
  for (int i = 0; i < particlesSize; i++) {
      delete best[i];
  }
  delete [] best;
  delete leaders;
  delete eArchive;
    
} // deleteParams


/**
 * Update the speed of each particle
 */
void OMOPSO::computeSpeed() {

  double r1, r2, W, C1, C2;
  XReal *bestGlobal;

  for (int i = 0; i < particlesSize; i++) {
    XReal *particle     = new XReal(particles->get(i));
    XReal *bestParticle = new XReal(best[i]);

    //Select a global best for calculate the speed of particle i, bestGlobal
    Solution *one, *two;
    int pos1 = PseudoRandom::randInt(0,leaders->size()-1);
    int pos2 = PseudoRandom::randInt(0,leaders->size()-1);
    one = leaders->get(pos1);
    two = leaders->get(pos2);

    if (crowdingDistanceComparator->compare(one,two) < 1) {
      bestGlobal = new XReal(one);
    } else {
      bestGlobal = new XReal(two);
    }

    //Params for velocity equation
    r1 = PseudoRandom::randDouble();
    r2 = PseudoRandom::randDouble();
    C1 = PseudoRandom::randDouble(1.5,2.0);
    C2 = PseudoRandom::randDouble(1.5,2.0);
    W  = PseudoRandom::randDouble(0.1,0.5);

    for (int var = 0; var < particle->getNumberOfDecisionVariables(); var++) {
      //Computing the velocity of this particle
      speed[i][var] = W  * speed[i][var] +
               C1 * r1 * (bestParticle->getValue(var) -
                          particle->getValue(var)) +
               C2 * r2 * (bestGlobal->getValue(var) -
                          particle->getValue(var));
    }

    delete bestGlobal;
    delete particle;
    delete bestParticle;

  }

} // computeSpeed


/**
 * Update the position of each particle
 */
void OMOPSO::computeNewPositions() {

  for (int i = 0; i < particlesSize; i++) {
    XReal * particle = new XReal(particles->get(i));
    //particle.move(speed_[i]);
    for (int var = 0; var < particle->getNumberOfDecisionVariables(); var++) {
      particle->setValue(var, particle->getValue(var) + speed[i][var]);

      if (particle->getValue(var) < problem_->getLowerLimit(var)) {
        particle->setValue(var, problem_->getLowerLimit(var));
        speed[i][var] = speed[i][var] * -1.0;
      }
      if (particle->getValue(var) > problem_->getUpperLimit(var)){
        particle->setValue(var, problem_->getUpperLimit(var));
        speed[i][var] = speed[i][var] * -1.0;
      }
    }
    delete particle;
  }

} // computeNewPositions


/**
 * Apply a mutation operator to some particles in the swarm
 */
void OMOPSO::mopsoMutation(int actualIteration, int totalIterations) {
  // There are three groups of particles_, the ones that are mutated with
  // a non-uniform mutation operator, the ones that are mutated with a
  // uniform mutation and the one that no are mutated
  nonUniformMutation->setParameter("currentIteration", &actualIteration);

  for (int i = 0; i < particles->size();i++) {
    if (i % 3 == 0) { //particles_ mutated with a non-uniform mutation
      nonUniformMutation->execute(particles->get(i));
    } else if (i % 3 == 1) { //particles_ mutated with a uniform mutation operator
      uniformMutation->execute(particles->get(i));
    } else {} //particles_ without mutation
  }
} // mopsoMutation


/**
 * Runs of the SMPSO algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet *OMOPSO::execute() {

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
    speed[i] = new double[problem_->getNumberOfVariables()];
    for (int j = 0; j < problem_->getNumberOfVariables(); j++) {
      speed[i][j] = 0.0;
    }
  }

  // Step4 and 5
  for (int i = 0; i < particles->size(); i++){
    Solution *particle = new Solution(particles->get(i));
    if (leaders->add(particle)){
      Solution *particle2 = new Solution(particle);
      if (eArchive->add(particle2) == false) {
        delete particle2;
      }
    } else {
      delete particle;
    }
  }

  //-> Step 6. Initialize the memory of each particle
  for (int i = 0; i < particles->size(); i++){
    Solution *particle = new Solution(particles->get(i));
    best[i] = particle;
  }
    
  //Crowding the leaders_
  distance->crowdingDistanceAssignment(leaders, problem_->getNumberOfObjectives());

  //-> Step 7. Iterations ..
  while (iteration < maxIterations) {

    //Compute the speed_
    computeSpeed();

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
      if (leaders->add(particle)) {
        Solution *particle2 = new Solution(particle);
        if (eArchive->add(particle2) == false) {
          delete particle2;
        }
      } else {
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
        
    //Assign crowding distance to the leaders_
    distance->crowdingDistanceAssignment(leaders,
                                          problem_->getNumberOfObjectives());
    iteration++;
  }
    
  // Build the solution set result
  SolutionSet *result = new SolutionSet(leaders->size());
  for (int i=0;i<leaders->size();i++) {
    result->add(new Solution(leaders->get(i)));
  }
    
  // Free memory
  deleteParams();
    
  return result;
} // execute
