//  MOEAD.cpp
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


#include <MOEAD.h>


/*
 * This class implements the MOEA/D algorithm.
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
MOEAD::MOEAD(Problem *problem) : Algorithm(problem) {
  functionType_ = "_TCHE1";
} // MOEAD


SolutionSet * MOEAD::execute() {
  int maxEvaluations;
  
  evaluations_ = 0;
  maxEvaluations = *(int *) getInputParameter("maxEvaluations");
  populationSize_ = *(int *) getInputParameter("populationSize");
  dataDirectory_ = * (string *) getInputParameter("dataDirectory");
  
  population_ = new SolutionSet(populationSize_);
  //indArray_ = new Solution*[problem_->getNumberOfObjectives()];
  
  T_ = 20;
  delta_ = 0.9;
  nr_ = 2;
/*
  T_ = * (int *) (0.1 * populationSize_);
  delta_ = 0.9;
  nr_ = * (int *) (0.01 * populationSize_);
*/
  neighborhood_ = new int*[populationSize_];
  
  z_ = new double[problem_->getNumberOfObjectives()];
  //lambda_ = new Vector(problem_->getNumberOfObjectives()) ;
  lambda_ = new double*[populationSize_];
  
  crossover_ = operators_["crossover"];  // default: DE crossover
  mutation_ = operators_["mutation"];  // default: polynomial mutation
  
  // STEP 1. Initialization
  // STEP 1.1. Compute euclidean distances between weight vectors and find T
  initUniformWeight();
  //for (int i = 0; i < 300; i++)
  // 	cout << lambda_[i][0] << " " << lambda_[i][1] << endl ;
  
  initNeighborhood();
  
  // STEP 1.2. Initialize population
  initPopulation();
  
  // STEP 1.3. Initialize z_
  initIdealPoint();
  
  // STEP 2. Update
  do {
    int * permutation = new int[populationSize_];
    UtilsMOEAD::randomPermutation(permutation, populationSize_);
    for (int i = 0; i < populationSize_; i++) {
      int n = permutation[i]; // or int n = i;
      //int n = i ; // or int n = i;
      int type;
      double rnd = PseudoRandom::randDouble();
      
      // STEP 2.1. Mating selection based on probability
      if (rnd < delta_) // if (rnd < realb)
      {
        type = 1;   // neighborhood
      } else {
        type = 2;   // whole population
      }
      vector<int> p;
      matingSelection(p, n, 2, type);
      
      // STEP 2.2. Reproduction
      Solution * child;
      Solution ** parents = new Solution*[3];
      
      parents[0] = population_->get(p[0]);
      parents[1] = population_->get(p[1]);
      parents[2] = population_->get(n);
      
      // Apply DE crossover
      void ** object = new void*[2];
      object[0] = population_->get(n);
      object[1] = parents;
      child = (Solution *) (crossover_->execute(object));
      delete[] object;
      delete[] parents;
      
      // Apply mutation
      mutation_->execute(child);
      
      // Evaluation
      problem_->evaluate(child);
      
      evaluations_++;
      
      // STEP 2.3. Repair. Not necessary
      
      // STEP 2.4. Update z_
      updateReference(child);
      
      // STEP 2.5. Update of solutions
      updateProblem(child, n, type);
    } // for
    
    delete[] permutation;
    
  } while (evaluations_ < maxEvaluations);
  
  // Free memory
  deleteParams();
  
  return population_;
} // execute


/**
 * initUniformWeight
 */
void MOEAD::initUniformWeight() {
  if ((problem_->getNumberOfObjectives() == 2) && (populationSize_ <= 300)) {
    for (int n = 0; n < populationSize_; n++) {
      lambda_[n] = new double[problem_->getNumberOfObjectives()];
      double a = 1.0 * n / (populationSize_ - 1);
      lambda_[n][0] = a;
      lambda_[n][1] = 1 - a;
    } // for
  } // if
  else {
    ostringstream os;
    os << dataDirectory_ + "/" << "W" << problem_->getNumberOfObjectives() << "D_"
        << populationSize_ << ".dat";
    string dataFileName;
    dataFileName = os.str();
    
    // Open the file
    std::ifstream in(dataFileName.c_str());
    if( !in ) {
      cout << "initUniformWeight: failed when reading from file: : " <<
          dataFileName << endl;
      exit(-1);
    } // if

    //int numberOfObjectives = 0;
    int i = 0;
    int j = 0;
    string aux;
    while (getline(in, aux)) {
      istringstream iss(aux);
      j = 0;
      // TODO: Check if number of tokens per line is equal to number of
      //       objectives
      lambda_[i] = new double[problem_->getNumberOfObjectives()];
      while (iss) {
        string token;
        iss >> token;
        if (token.compare("")!=0) {
          double value = atof(token.c_str());
          lambda_[i][j] = value;
          //cout << "lambda[" << i << "," << j << "] = " << value << endl;
          j++;
        } // if
      } // while
      i++;
    } // while
    in.close();
  } // else
} // initUniformWeight


/**
 * initNeighborhood
 */
void MOEAD::initNeighborhood() {
  double * x = new double[populationSize_];
  int * idx = new int[populationSize_];
  
  for (int i = 0; i < populationSize_; i++) {
    // calculate the distances based on weight vectors
    for (int j = 0; j < populationSize_; j++) {
      x[j] = UtilsMOEAD::distVector(lambda_[i], lambda_[j],
              problem_->getNumberOfObjectives());
      //x[j] = dist_vector(population[i].namda,population[j].namda);
      idx[j] = j;
      // cout << "x[" << j << "]: " << x[j] << ". idx[" << j << "]: " <<
      //    idx[j] << endl ;
    } // for
    
    // find 'niche' nearest neighboring subproblems
    UtilsMOEAD::minFastSort(x, idx, populationSize_, T_);
    //minfastsort(x,idx,population.size(),niche);
    
    neighborhood_[i] = new int[T_];
    for (int k = 0; k < T_; k++) {
      neighborhood_[i][k] = idx[k];
      //cout << "neg[ << i << "," << k << "]: " << neighborhood_[i][k] << endl;
    }
  } // for
  
  delete[] x;
  delete[] idx;
  
} // initNeighborhood


/**
 * initPopulation
 */
void MOEAD::initPopulation() {
  for (int i = 0; i < populationSize_; i++) {
    Solution * newSolution = new Solution(problem_);

    problem_->evaluate(newSolution);
    evaluations_++;
    population_->add(newSolution);
  } // for
} // initPopulation


/**
 * initIdealPoint
 */
void MOEAD::initIdealPoint() {
  for (int i = 0; i < problem_->getNumberOfObjectives(); i++) {
    z_[i] = 1.0e+30;
    //indArray_[i] = new Solution(problem_);
    //problem_->evaluate(indArray_[i]);
    //evaluations_++;
  } // for
  
  for (int i = 0; i < populationSize_; i++) {
    updateReference(population_->get(i));
  } // for
} // initIdealPoint


/**
 * matingSelection
 */
void MOEAD::matingSelection(vector<int> &list, int cid, int size, int type) {
  
  // list : the set of the indexes of selected mating parents
  // cid  : the id of current subproblem
  // size : the number of selected mating parents
  // type : 1 - neighborhood; otherwise - whole population
  int ss;
  int r;
  int p;
  
  //ss = neighborhood_[cid].length;
  ss = T_;
  while (list.size() < size) {
    if (type == 1) {
      r = PseudoRandom::randInt(0, ss - 1);
      p = neighborhood_[cid][r];
      //p = population[cid].table[r];
    } else {
      p = PseudoRandom::randInt(0, populationSize_ - 1);
    }
    bool flag = true;
    for (int i = 0; i < list.size(); i++) {
      if (list[i] == p) // p is in the list
      {
        flag = false;
        break;
      }
    }
    
    //if (flag) list.push_back(p);
    if (flag) {
      list.push_back(p);
    }
  }
} // matingSelection


/**
 * 
 * @param individual
 */
void MOEAD::updateReference(Solution * individual) {
  for (int n = 0; n < problem_->getNumberOfObjectives(); n++) {
    if (individual->getObjective(n) < z_[n]) {
      z_[n] = individual->getObjective(n);
      //indArray_[n] = individual;
    }
  }
} // updateReference


/**
 * @param individual
 * @param id
 * @param type
 */
void MOEAD::updateProblem(Solution * indiv, int id, int type) {
  // indiv: child solution
  // id: the id of current subproblem
  // type: update solutions in neighborhood (1) or whole population (otherwise)
  int size;
  int time;
  
  time = 0;
  
  if (type == 1) {
    //size = neighborhood_[id].length;
    size = T_;
  } else {
    //size = population_.size();
    size = populationSize_;
  }
  int * perm = new int[size];
  
  UtilsMOEAD::randomPermutation(perm, size);
  
  for (int i = 0; i < size; i++) {
    
    int k;
    
    if (type == 1) {
      k = neighborhood_[id][perm[i]];
    } else {
      k = perm[i];      // calculate the values of objective function regarding
                        // the current subproblem
    }
    
    double f1, f2;
    
    f1 = fitnessFunction(population_->get(k), lambda_[k]);
    f2 = fitnessFunction(indiv, lambda_[k]);
    
    if (f2 < f1) {
      delete population_->get(k);
      population_->replace(k, new Solution(indiv));
      //population[k].indiv = indiv;
      time++;
    }
    // the maximal number of solutions updated is not allowed to exceed 'limit'
    if (time >= nr_) {
      delete indiv;
      delete[] perm;
      return;
    }
  }

  delete indiv;
  delete[] perm;
  
} // updateProblem


/**
 * fitnessFunction
 */
double MOEAD::fitnessFunction(Solution * individual, double * lambda) {
  double fitness;
  fitness = 0.0;
  
  if (functionType_.compare("_TCHE1")==0) {
    double maxFun = -1.0e+30;
    
    for (int n = 0; n < problem_->getNumberOfObjectives(); n++) {
      double diff = fabs(individual->getObjective(n) - z_[n]);
      
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
  } // if
  else {
    cout << "MOEAD.fitnessFunction: unknown type " << functionType_ << endl;
    exit (EXIT_FAILURE);
  }
  return fitness;
} // fitnessEvaluation


void MOEAD::deleteParams() {
  delete[] z_;
  for (int n = 0; n < populationSize_; n++) {
    delete[] lambda_[n];
  } // for
  delete[] lambda_;
  for (int i = 0; i < populationSize_; i++) {
    delete[] neighborhood_[i];
  }
  delete[] neighborhood_;
} //deleteParams
