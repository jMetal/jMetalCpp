/*
 * @file SMPSO.cpp
 * @author Esteban López
 * @date 13 December 2011
 */

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
    for (int j = 0; j < problem_->getNumberOfVariables(); j++) {
      speed_[i][j] = 0.0;
    }
  }


  // Step4 and 5
  for (int i = 0; i < particles_->size(); i++) {
    Solution * particle = new Solution(particles_->get(i));
    leaders_->add(particle);
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
    }

    //Actualize the archive
    for (int i = 0; i < particles_->size(); i++) {
      Solution * particle = new Solution(particles_->get(i));
      leaders_->add(particle);
    }

    //Actualize the memory of this particle
    for (int i = 0; i < particles_->size(); i++) {
      int flag = dominance_->compare(particles_->get(i), best_[i]);
      if (flag != 1) { // the new particle is best_ than the older remeber
        Solution * particle = new Solution(particles_->get(i));
        best_[i] = particle;
      }
    }

    //Assign crowding distance to the leaders_
    distance_->crowdingDistanceAssignment(leaders_,
      problem_->getNumberOfObjectives());
    iteration_++;
  }
  return leaders_;
} // execute
