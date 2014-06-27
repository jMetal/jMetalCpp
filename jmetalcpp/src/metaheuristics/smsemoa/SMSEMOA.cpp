//  SMSEMOA.cpp
//
//  Author:
//       Cristian Zambrano V. <cristian_uteq@hotmail.com>
//
//  Copyright (c) 2013 Antonio J. Nebro, Juan J. Durillo
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


#include <SMSEMOA.h>

/*
 * This class implements the SMS-EMOA algorithm.
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
SMSEMOA::SMSEMOA(Problem *problem) : Algorithm(problem) {
  utils_ = new MetricsUtil();
  hv_ = new Hypervolume();
} // SMSEMOA

/**
 * Destructor
 */
SMSEMOA::~SMSEMOA() {
  delete utils_;
  delete hv_;
} // ~SMSEMOA


/**
* Runs the SMS-EMOA algorithm.
* @return a <code>SolutionSet</code> that is a set of non dominated solutions
* as a result of the algorithm execution
*/
SolutionSet * SMSEMOA::execute() {
  int populationSize;
  int maxEvaluations;
  int evaluations;
  double offset = 100.0;

  QualityIndicator * indicators; // QualityIndicator object
  int requiredEvaluations; // Use in the example of use of the indicators object (see below)

  SolutionSet * population;
  SolutionSet * offspringPopulation;
  SolutionSet * unionSolution;

  Operator * mutationOperator;
  Operator * crossoverOperator;
  Operator * selectionOperator;

  //Read the parameters
  populationSize = *(int *) getInputParameter("populationSize");
  maxEvaluations = *(int *) getInputParameter("maxEvaluations");
  offset = *(double *) getInputParameter("offset");

  //indicators = (QualityIndicator*) getInputParameter("indicators");

  //Initialize the variables
  population = new SolutionSet(populationSize);
  evaluations = 0;

  requiredEvaluations = 0;

  //Read the operators
  crossoverOperator = operators_["crossover"];
  mutationOperator = operators_["mutation"];
  selectionOperator = operators_["selection"];

  // Create the initial solutionSet
  Solution * newSolution;
  for (int i = 0; i < populationSize; i++) {
    newSolution = new Solution(problem_);
    problem_->evaluate(newSolution);
    problem_->evaluateConstraints(newSolution);
    evaluations++;
    population->add(newSolution);
  } //for

  Solution ** parents;
  Solution ** offSpring;

  // Generations ...
  while (evaluations < maxEvaluations) {

    // Create the offSpring solutionSet
    offspringPopulation = new SolutionSet(1);
    
    /*Selection Operator must return two individuals*/
    parents = (Solution **) (selectionOperator->execute(population));
    
    offSpring = (Solution **) (crossoverOperator->execute(parents));
    
    mutationOperator->execute(offSpring[0]);
    
    problem_->evaluate(offSpring[0]);
    problem_->evaluateConstraints(offSpring[0]);
    
    // insert child into the offspring population
    offspringPopulation->add(offSpring[0]);
    
    evaluations++;
    
    //cout << "Evaluations " << evaluations << endl;
    
    delete offSpring[1];
    delete[] offSpring;
    delete[] parents;
    
    // Create the solutionSet union of solutionSet and offSpring
    unionSolution = population->join(offspringPopulation);
    delete offspringPopulation;
    
    // Ranking the union (non-dominated sorting)
    Ranking * ranking = new Ranking(unionSolution);
    
    // ensure crowding distance values are up to date
    // (may be important for parent selection)
    for (int j = 0; j < population->size(); j++){
      population->get(j)->setCrowdingDistance(0.0);
    }
    
    //cout << "front 0 size: " << ranking->getSubfront(0)->size()  << endl ;
    
    SolutionSet *lastFront = ranking->getSubfront(ranking->getNumberOfSubfronts() - 1);
    if (lastFront->size() > 1) {
      
      vector <vector<double> > frontValues = lastFront->writeObjectivesToMatrix();
      int numberOfObjectives = problem_->getNumberOfObjectives();
      
      // STEP 1. Obtain the maximum and minimum values of the Pareto front
      vector<double> maximumValues = utils_->getMaximumValues(unionSolution->writeObjectivesToMatrix(), numberOfObjectives);
      vector<double> minimumValues = utils_->getMinimumValues(unionSolution->writeObjectivesToMatrix(), numberOfObjectives);
      
      // STEP 2. Get the normalized front
      vector <vector<double> > normalizedFront = utils_->getNormalizedFront(frontValues, maximumValues, minimumValues);
      
      // compute offsets for reference point in normalized space
      vector<double> offsets;
      for (int i = 0; i < maximumValues.size(); i++) {
        offsets.push_back(offset / (maximumValues[i] - minimumValues[i]));
      }
      
      // STEP 3. Inverse the pareto front. This is needed because the original
      //metric by Zitzler is for maximization problems
      vector <vector<double> > invertedFront = utils_->invertedFront(normalizedFront);
      // shift away from origin, so that boundary points also get a contribution > 0
      for (int i = 0; i < invertedFront.size();i++) {
        for (int j = 0; j < invertedFront[i].size(); j++) {
          invertedFront[i][j] = invertedFront[i][j] + offsets[j];
        }
      }
      
      // calculate contributions and sort
      vector<double> contributions = hvContributions(invertedFront);
      for (int i = 0; i < contributions.size(); i++) {
        // contribution values are used analogously to crowding distance
        lastFront->get(i)->setCrowdingDistance(contributions[i]);
      }
      
      CrowdingDistanceComparator *cd = new CrowdingDistanceComparator();
			lastFront->sort(cd);
			delete cd;
    
    }
    
    // all but the worst are carried over to the survivor population
    SolutionSet *front = NULL;
    for (int i=0;i<population->size();i++) {
      delete population->get(i);
    }
    population->clear();
    
    for (int i = 0; i < ranking->getNumberOfSubfronts() - 1; i++) {
      front = ranking->getSubfront(i);
      for (int j = 0; j < front->size(); j++)
        population->add(new Solution(front->get(j)));
    }
    for (int i = 0; i < lastFront->size() - 1; i++)
      population->add(new Solution(lastFront->get(i)));
    
    delete ranking;
    delete unionSolution;
    
    // This piece of code shows how to use the indicator object into the code
    // of SMS-EMOA. In particular, it finds the number of evaluations required
    // by the algorithm to obtain a Pareto front with a hypervolume higher
    // than the hypervolume of the true Pareto front.
    /*if (indicators != NULL && requiredEvaluations == 0) {
      double HV = indicators->getHypervolume(population);
      if (HV >= (0.98 * indicators->getTrueParetoFrontHypervolume())) {
        requiredEvaluations = evaluations;
      } // if
    } // if */
    
  } //WHILE
  
  // Return the first non-dominated front
  Ranking *ranking = new Ranking(population);
  SolutionSet * result = new SolutionSet(ranking->getSubfront(0)->size());
  for (int i=0;i<ranking->getSubfront(0)->size();i++) {
    result->add(new Solution(ranking->getSubfront(0)->get(i)));
  }
  delete ranking;
  delete population;
  
  return result;
}

vector<double> SMSEMOA::hvContributions(vector< vector<double> > front){
  int numberOfObjectives = problem_->getNumberOfObjectives();
  
  vector<double> contributions;
  double hv;
  
  double** frontSubset;
  
  vector< vector<double> > frontCopy;
  
  double** totalFront = new double*[front.size()];
  
  for (int i = 0; i < front.size(); i++) {
    frontCopy.push_back(vector<double>());
    totalFront[i] = new double[front[i].size()];
    for (int j = 0; j < front[i].size(); j++) {
      frontCopy[i].push_back(front[i][j]);
      totalFront[i][j] = front[i][j];
    }
  }
  
  double totalVolume = hv_->calculateHypervolume(totalFront, front.size(), numberOfObjectives);
  
  for (int i = 0; i < front.size(); i++) {
    
    vector<double> evaluatedPoint;
    for (int j = 0; j < frontCopy[i].size(); j++) {
      evaluatedPoint.push_back(frontCopy[i][j]);
    }
    frontCopy.erase(frontCopy.begin() + i);
    
    /*Makes a copy in pointer of pointer format*/
    frontSubset = new double*[frontCopy.size()];
    for (int f = 0; f < frontCopy.size(); f++) {
      frontSubset[f] = new double[frontCopy[f].size()];
      for (int c = 0; c < frontCopy[f].size(); c++) {
        frontSubset[f][c]=frontCopy[f][c];
      }  
    }
    
    // STEP4. The hypervolume
    hv = hv_->calculateHypervolume(frontSubset, frontCopy.size(), numberOfObjectives);
    contributions.push_back(totalVolume - hv);
    
    // put point back position i
    frontCopy.insert(frontCopy.begin() + i , evaluatedPoint);
    
    for( int y = 0 ; y < frontCopy.size()-1 ; y++ ) {
      delete [] frontSubset[y] ;
    }
    delete [] frontSubset;
    
  }
  
  for( int y = 0 ; y < front.size() ; y++ ) {
    delete [] totalFront[y] ;
  }
  delete [] totalFront;
  
  return contributions;

}
