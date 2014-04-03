//  StandardPSO2007.cpp
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//       Antonio J. Nebro <antonio@lcc.uma.es>
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


#include <StandardPSO2007.h>


/**
 * Class implementing a Standard PSO 2007 algorithm
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
StandardPSO2007::StandardPSO2007(Problem * problem) : Algorithm(problem) {

  W_ = 1.0/(2.0 * log(2)) ; //0.721;
  C_ = 1.0/2.0 + log(2) ; //1.193;

  comparator_ = new ObjectiveComparator(0) ; // Single objective comparator
  map<string, void *> parameters ; // Operator parameters

  parameters["comparator"] = comparator_;
  findBestSolution_ = new BestSolutionSelection(parameters) ;

  evaluations_ = 0 ;
} // StandardPSO2007


/**
 * Destructor
 */
StandardPSO2007::~StandardPSO2007() {
  delete comparator_;
  delete findBestSolution_;
} // ~StandardPSO2007


double StandardPSO2007::getW() {
  return W_;
} // getW


double StandardPSO2007::getC() {
  return C_;
} // getC


/**
 * Initialize all parameters of the algorithm
 */
void StandardPSO2007::initParams() {
  swarmSize_ = *(int *) getInputParameter("swarmSize");
  maxIterations_ = *(int *) getInputParameter("maxIterations");
  numberOfParticlesToInform_ = *(int *) getInputParameter("numberOfParticlesToInform");

  cout << "Swarm size: " << swarmSize_ << endl;

  iteration_ = 0;

  swarm_ = new SolutionSet(swarmSize_);
  localBest_ = new Solution*[swarmSize_];
  neighborhoodBest_ = new Solution*[swarmSize_];

  // Create the speed_ vector
  speed_ = new double*[swarmSize_];
} // initParams


/**
 * Delete all parameters of the algorithm
 */
void StandardPSO2007::deleteParams() {
  delete swarm_;
  delete [] localBest_;
  delete [] neighborhoodBest_;
  delete [] speed_;
} // deleteParams


Solution * StandardPSO2007::getNeighborBest(int i) {
  Solution * bestLocalBestSolution = NULL ;

  for (int index : neighborhood_->getNeighbors(i)) {
    if ((bestLocalBestSolution == NULL) || (bestLocalBestSolution->getObjective(0) > localBest_[index]->getObjective(0))) {
      bestLocalBestSolution = localBest_[index] ;
    }
  }

  return bestLocalBestSolution ;
} // getNeighborBest


void StandardPSO2007::computeSpeed() {
  double r1, r2 ;

  for (int i = 0; i < swarmSize_; i++) {

    XReal * particle = new XReal(swarm_->get(i)) ;
    XReal * localBest = new XReal(localBest_[i]) ;
    XReal * neighborhoodBest = new XReal(neighborhoodBest_[i]) ;
    //XReal * neighborhoodBest = new XReal(globalBest_) ;

    r1 = PseudoRandom::randDouble(0, C_);
    r2 = PseudoRandom::randDouble(0, C_);

    //W_ = 0.9 ;
    if (localBest_[i] != neighborhoodBest_[i]) {
      for (int var = 0; var < particle->getNumberOfDecisionVariables(); var++) {
        speed_[i][var] = W_ * speed_[i][var] +
                r1 * (localBest->getValue(var) - particle->getValue(var)) +
                r2 * (neighborhoodBest->getValue(var) - particle->getValue(var));
      }
    }
    else {
      for (int var = 0; var < particle->getNumberOfDecisionVariables(); var++) {
        speed_[i][var] = W_* speed_[i][var] +
                  r1 * (localBest->getValue(var) - particle->getValue(var)) ;
      }
    }

    delete particle;
    delete localBest;
    delete neighborhoodBest;

  }
} // computeSpeed


/**
 * Update the position of each particle
 */
void StandardPSO2007::computeNewPositions() {
  for (int i = 0; i < swarmSize_; i++) {
    //Variable[] particle = swarm_.get(i).getDecisionVariables();
    XReal * particle = new XReal(swarm_->get(i)) ;
    //particle.move(speed_[i]);
    for (int var = 0; var < particle->size(); var++) {
      particle->setValue(var, particle->getValue(var) +  speed_[i][var]) ;
      if (particle->getValue(var) < problem_->getLowerLimit(var)) {
        particle->setValue(var, problem_->getLowerLimit(var));
        speed_[i][var] = 0;
      }
      if (particle->getValue(var) > problem_->getUpperLimit(var)) {
        particle->setValue(var, problem_->getUpperLimit(var));
        speed_[i][var] = 0;
      }
    }
    delete particle;
  }
} // computeNewPositions


/**
 * Runs of the StandardPSO2007 algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet * StandardPSO2007::execute() {
  initParams();

  // Step 1 Create the initial population and evaluate
  for (int i = 0; i < swarmSize_; i++) {
    Solution * particle = new Solution(problem_);
    problem_->evaluate(particle);
    evaluations_ ++ ;
    swarm_->add(particle);
  }

  neighborhood_ = new AdaptiveRandomNeighborhood(swarm_, numberOfParticlesToInform_) ;

  cout << "SwarmSize: " << swarmSize_ << endl;
  cout << "Swarm size: " << swarm_->size() << endl;
  cout << "list size: " << neighborhood_->getNeighborhood().size() << endl;

  //-> Step2. Initialize the speed_ of each particle
  for (int i = 0; i < swarmSize_; i++) {
    XReal * particle = new XReal(swarm_->get(i))  ;
    speed_[i] = new double[problem_->getNumberOfVariables()];
    for (int j = 0; j < problem_->getNumberOfVariables(); j++) {
      speed_[i][j] = (PseudoRandom::randDouble(particle->getLowerBound(j),particle->getUpperBound(j))
              - particle->getValue(j))/2.0 ;
    }
    delete particle;
  }

  //-> Step 6. Initialize the memory of each particle
  for (int i = 0; i < swarm_->size(); i++) {
    Solution * particle = new Solution(swarm_->get(i));
    localBest_[i] = particle;
  }

  for (int i = 0; i < swarm_->size(); i++) {
    neighborhoodBest_[i] = getNeighborBest(i) ;
  }

  //cout << "neighborhood_i " << neighborhood_->getNeighbors(0) << endl;
  cout << "[";
  for (int i = 0; i < neighborhood_->getNeighbors(0).size()-1; i++) {
    cout << neighborhood_->getNeighbors(0).at(i) << ",";
  }
  cout << neighborhood_->getNeighbors(0).back() << "]" << endl;
  for (int s :  neighborhood_->getNeighbors(0)) {
    cout << s << ": " << localBest_[s]->getObjective(0) << endl;
  }

  cout << "localBest_i " << localBest_[0]->getObjective(0) << endl;
  cout << "neighborhoodBest_i " << getNeighborBest(0)->getObjective(0) << endl;

  cout << "Swarm: " << swarm_ << endl;
  swarm_->printObjectives();
  double b = swarm_->best(comparator_)->getObjective(0) ;
  cout << "Best: " << b << endl;

  double bestFoundFitness = numeric_limits<double>::max();

  while (iteration_ < maxIterations_) {
    //Compute the speed
    computeSpeed() ;

    //Compute the new positions for the swarm
    computeNewPositions();

    //Evaluate the new swarm_ in new positions
    for (int i = 0; i < swarm_->size(); i++) {
      Solution * particle = swarm_->get(i);
      problem_->evaluate(particle);
      evaluations_ ++ ;
    }

    //Update the memory of the particles
    for (int i = 0; i < swarm_->size(); i++) {
      if ((swarm_->get(i)->getObjective(0) < localBest_[i]->getObjective(0))) {
        Solution * particle = new Solution(swarm_->get(i));
        delete localBest_[i];
        localBest_[i] = particle;
      } // if
    }
    for (int i = 0; i < swarm_->size(); i++) {
      neighborhoodBest_[i] = getNeighborBest(i) ;
    }

    iteration_++;
    //System.out.println("Swarm( " + iteration_+ "): " + swarm_) ;
    //swarm_.printObjectives();
    double bestCurrentFitness = swarm_->best(comparator_)->getObjective(0) ;
    cout << "Best: " << bestCurrentFitness << endl;

    if (bestCurrentFitness == bestFoundFitness) {
      cout << "Recomputing" << endl;
      neighborhood_->recompute();
    }

    if (bestCurrentFitness < bestFoundFitness) {
      bestFoundFitness = bestCurrentFitness ;
    }
  }

  // Return a population with the best individual
  SolutionSet * resultPopulation = new SolutionSet(1) ;
  int * bestSolutionIdx = (int *) findBestSolution_->execute(swarm_);
  resultPopulation->add(new Solution(swarm_->get(* bestSolutionIdx))) ;
  delete bestSolutionIdx;

  // Free memory
  for (int i = 0; i < swarmSize_; i++) {
    delete [] speed_[i];
  }
  for (int i = 0; i < swarm_->size(); i++) {
    delete localBest_[i];
  }
  delete neighborhood_;
  deleteParams();

  return resultPopulation ;
} // execute
