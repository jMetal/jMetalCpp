//  Solution.cpp
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
//       Juan J. Durillo <durillo@lcc.uma.es>
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


#include <Solution.h>


/**
 * Constructor.
 */
Solution::Solution () {
  problem_ = NULL;
  marked_ = false;
  overallConstraintViolation_ = 0.0;
  numberOfViolatedConstraints_ = 0;
  numberOfVariables_ = 0;
  numberOfObjectives_ = 0;
  type_ = NULL;
  variable_ = NULL;
  objective_ = NULL;
  rank_ = 0;
} //Solution


/**
 * Constructor
 * @param numberOfObjectives Number of objectives of the solution
 *
 * This constructor is used mainly to read objective values from a file to
 * variables of a SolutionSet to apply quality indicators
 */
Solution::Solution (int numberOfObjectives) {
  overallConstraintViolation_ = 0.0;
  numberOfObjectives_ = numberOfObjectives;
  numberOfVariables_ = 0;
  variable_ = NULL;
  objective_ = new double[numberOfObjectives_];
  if (objective_ == NULL) {
    cout << "ERROR GRAVE: Impossible to reserve memory for storing objectives in class Solution" << endl;
    exit(-1);
  }
  rank_ = 0;
}


/**
 * Constructor.
 * @param problem The problem to solve
 * @throws ClassNotFoundException
 */
Solution::Solution (Problem *problem) {
  problem_ = problem;
  type_ = problem_->getSolutionType();
  overallConstraintViolation_ = 0.0;
  numberOfObjectives_ = problem_->getNumberOfObjectives();
  numberOfVariables_  = problem_->getNumberOfVariables();

  // creating the objective vector
  objective_ = new double[numberOfObjectives_];
   if (objective_ == NULL) {
     cout << "ERROR GRAVE: Impossible to reserve memory for storing objectives in class Solution" << endl;
     exit(-1);
   }
   // at this point objective vector has been created successfully

  // Setting initial values
  fitness_ = 0.0;
  kDistance_ = 0.0;
  crowdingDistance_ = 0.0;
  distanceToSolutionSet_ = std::numeric_limits<double>::max();
  variable_ = type_->createVariables();
  rank_ = 0;
} // Solution


/**
 * Constructor
 * @param problem The problem to solve
 */
Solution::Solution (Problem * problem, Variable ** variables) {
  problem_ = problem;
  type_ = problem->getSolutionType();
  numberOfObjectives_ = problem->getNumberOfObjectives();
  numberOfVariables_  = problem_->getNumberOfVariables();
  objective_ = new double[numberOfObjectives_] ;

  // Setting initial values
  fitness_ = 0.0;
  kDistance_ = 0.0;
  crowdingDistance_ = 0.0;
  distanceToSolutionSet_ = std::numeric_limits<double>::max();
  variable_ = variables;
  rank_ = 0;
} // Solution


/**
 * Copy constructor.
 * @param solution Solution to copy.
 */
Solution::Solution (Solution *solution) {
  problem_ = solution->problem_;
  type_ = solution->type_;
  numberOfObjectives_ = solution->getNumberOfObjectives();
  numberOfVariables_ = solution->getNumberOfVariables();

  // creating the objective vector
  objective_ = new double[numberOfObjectives_];
  if (objective_ == NULL) {
    cout << "ERROR GRAVE: Impossible to reserve memory for storing objectives in class Solution" << endl;
    exit(-1);
  }
  for (int i = 0; i< numberOfObjectives_; i++) {
      objective_[i] = solution->objective_[i];
  }

  variable_ = type_->copyVariables(solution->variable_) ;
  overallConstraintViolation_ = solution->getOverallConstraintViolation();
  numberOfViolatedConstraints_ = solution->getNumberOfViolatedConstraints();
  distanceToSolutionSet_ = solution->getDistanceToSolutionSet();
  crowdingDistance_ = solution->getCrowdingDistance();
  kDistance_ = solution->getKDistance();
  fitness_ = solution->getFitness();
  marked_ = solution->isMarked();
  rank_ = solution->getRank();
  location_ = solution->getLocation();
    
  // create the variables
  //old fashion of copying variables
  //decisionVariables_ = (Variable *)new Variable*[numberOfVariables_];
  //for (i = 0; i < numberOfVariables_; i++) {
  //    decisionVariables_[i] = another_->decisionVariables_[i].deepCopy()
  //}
  //new fashion of copying variables
  //decisionVariables_ = solutionType_->copyVariables(another->decisionVariables_);
    
} // Solution


/**
 * Destructor
 */
Solution::~Solution() {
  delete[]objective_ ;
  if (variable_ != NULL)
    for (int i = 0; i < numberOfVariables_; i++)
      delete variable_[i] ;
  delete [] variable_ ;
} // ~Solution


/**
 * Sets the distance between this solution and a <code>SolutionSet</code>.
 * The value is stored in <code>distanceToSolutionSet_</code>.
 * @param distance The distance to a solutionSet.
 */
void Solution::setDistanceToSolutionSet(double distance) {
    distanceToSolutionSet_ = distance;
} // setDistanceToSolutionSet


/**
 * Gets the distance from the solution to a <code>SolutionSet</code>.
 * <b> REQUIRE </b>: this method has to be invoked after calling
 * <code>setDistanceToPopulation</code>.
 * @return the distance to a specific solutionSet.
 */
double Solution::getDistanceToSolutionSet() {
  return distanceToSolutionSet_;
} // getDistanceToSolutionSet


/**
 * Sets the distance between the solution and its k-nearest neighbor in
 * a <code>SolutionSet</code>. The value is stored in <code>kDistance_</code>.
 * @param distance The distance to the k-nearest neighbor.
 */
void Solution::setKDistance(double distance) {
  kDistance_ = distance;
} // setKDistance


/**
 * Gets the distance from the solution to his k-nearest nighbor in a
 * <code>SolutionSet</code>. Returns the value stored in
 * <code>kDistance_</code>. <b> REQUIRE </b>: this method has to be invoked
 * after calling <code>setKDistance</code>.
 * @return the distance to k-nearest neighbor.
 */
double Solution::getKDistance() {
  return kDistance_;
} // getKDistance


/**
 * Sets the crowding distance of a solution in a <code>SolutionSet</code>.
 * The value is stored in <code>crowdingDistance_</code>.
 * @param distance The crowding distance of the solution.
 */
void Solution::setCrowdingDistance(double distance) {
  crowdingDistance_ = distance;
} // setCrowdingDistance


/**
 * Gets the crowding distance of the solution into a <code>SolutionSet</code>.
 * Returns the value stored in <code>crowdingDistance_</code>.
 * <b> REQUIRE </b>: this method has to be invoked after calling
 * <code>setCrowdingDistance</code>.
 * @return the distance crowding distance of the solution.
 */
double Solution::getCrowdingDistance() {
  return crowdingDistance_;
} // getCrowdingDistance


/**
 * Sets the fitness of a solution.
 * The value is stored in <code>fitness_</code>.
 * @param fitness The fitness of the solution.
 */
void Solution::setFitness(double fitness) {
  fitness_ = fitness;
} // setFitness


/**
 * Gets the fitness of the solution.
 * Returns the value of stored in the variable <code>fitness_</code>.
 * <b> REQUIRE </b>: This method has to be invoked after calling
 * <code>setFitness()</code>.
 * @return the fitness.
 */
double Solution::getFitness() {
  return fitness_;
} // getFitness


/**
 * Sets the value of the i-th objective.
 * @param i The number identifying the objective.
 * @param value The value to be stored.
 */
void Solution::setObjective(int i, double value) {
  if (i < 0 || i >= numberOfObjectives_) {
    cout << "Solution::setObjective: objective index out of range: " << i
          << endl;
    exit(-1);
  }
  objective_[i] = value;
} // setObjective


/**
 * Returns the value of the i-th objective.
 * @param i The value of the objective.
 */
double Solution::getObjective(int i) {
  if (i < 0 || i >= numberOfObjectives_) {
    cout << "Solution::getObjective: objective index out of range: " << i
          << endl;
    exit(-1);
  }
  return objective_[i];
} // getObjective


/**
 * Returns the number of objectives.
 * @return The number of objectives.
 */
int Solution::getNumberOfObjectives() {
  return numberOfObjectives_;
} // getNumberOfObjectives


/**
 * Returns the number of decision variables of the solution.
 * @return The number of decision variables.
 */
int Solution::getNumberOfVariables() {
  return numberOfVariables_;
} // getNumberOfVariables


/**
 * Returns a string representing the solution.
 * @return The string.
 */
string Solution::toString() {
  string aux = "";
    
  for (int i = 0; i < numberOfVariables_; i++) {
    std::ostringstream stringStream;
//    stringStream << this->getDecisionVariables()[i]->getValue() ;
    stringStream << this->getDecisionVariables()[i]->toString() ;
    aux = aux + stringStream.str() + " ";
  }
  aux = aux + " | " ;
  for (int i = 0; i < numberOfObjectives_; i++) {
    std::ostringstream stringStream;
    stringStream << this->getObjective(i) ;
    // aux = aux + string(this->getDecisionVariables()[i]->getValue()) + " ";
    // aux = aux + string(0.03) + " ";
    aux = aux + stringStream.str() +  " ";
  }

  return aux;
} // toString


/**
 * Returns the decision variables of the solution.
 * @return the <code>DecisionVariables</code> object representing the decision
 * variables of the solution.
 */
Variable ** Solution::getDecisionVariables() {
  return variable_;
} // getDecisionVariables


/**
 * Sets the decision variables for the solution.
 * @param decisionVariables The <code>DecisionVariables</code> object
 * representing the decision variables of the solution.
 */
void Solution::setDecisionVariables(Variable **variables) {
  variable_ = variables ;
} // setDecisionVariables


/**
 * Indicates if the solution is marked.
 * @return true if the method <code>marked</code> has been called and, after
 * that, the method <code>unmarked</code> hasn't been called. False in other
 * case.
 */
bool Solution::isMarked() {
  return marked_;
} // isMarked


/**
 * Establishes the solution as marked.
 */
void Solution::mark() {
  marked_ = true;
} // mark


/**
 * Established the solution as unmarked.
 */
void Solution::unMark() {
  marked_ = false;
} // unMark


/**
 * Sets the rank of a solution.
 * @param value The rank of the solution.
 */
void Solution::setRank(int rank) {
  rank_ = rank ;
} // setRank


/**
 * Gets the rank of the solution.
 * <b> REQUIRE </b>: This method has to be invoked after calling
 * <code>setRank()</code>.
 * @return the rank of the solution.
 */
int Solution::getRank() {
  return rank_;
} // getRank


/**
 * Sets the overall constraints violated by the solution.
 * @param value The overall constraints violated by the solution.
 */
void Solution::setOverallConstraintViolation(double value) {
  overallConstraintViolation_ = value;
} // setOverallConstraintViolation


/**
 * Gets the overall constraint violated by the solution.
 * <b> REQUIRE </b>: This method has to be invoked after calling
 * <code>overallConstraintViolation</code>.
 * @return the overall constraint violation by the solution.
 */
double Solution::getOverallConstraintViolation() {
  return overallConstraintViolation_;
} // getOverallConstraintViolation


/**
 * Sets the number of constraints violated by the solution.
 * @param value The number of constraints violated by the solution.
 */
void Solution::setNumberOfViolatedConstraints(int number) {
  numberOfViolatedConstraints_ = number;
} // setNumberOfViolatedConstraints


/**
 * Gets the number of constraint violated by the solution.
 * <b> REQUIRE </b>: This method has to be invoked after calling
 * <code>setNumberOfViolatedConstraint</code>.
 * @return the number of constraints violated by the solution.
 */
int Solution::getNumberOfViolatedConstraints() {
  return numberOfViolatedConstraints_;
} // getNumberOfViolatedConstraints


/**
 * Sets the location of the solution into a solutionSet.
 * @param location The location of the solution.
 */
void Solution::setLocation(int location) {
  location_ = location;
} // setLocation


/**
 * Gets the location of this solution in a <code>SolutionSet</code>.
 * <b> REQUIRE </b>: This method has to be invoked after calling
 * <code>setLocation</code>.
 * @return the location of the solution into a solutionSet
 */
int Solution::getLocation() {
  return location_;
} // getLocation


/**
 * Sets the type of the variable.
 * @param type The type of the variable.
 */
void Solution::setType(SolutionType * type) {
  type_ = type;
} // setType


/**
 * Gets the type of the variable
 * @return the type of the variable
 */
SolutionType * Solution::getType() {
  return type_;
} // getType


/**
 * Returns the aggregative value of the solution
 * @return The aggregative value.
 */
double Solution::getAggregativeValue() {
  double value = 0.0;
  for (int i = 0; i < numberOfObjectives_; i++){
    value += objective_[i];
  }
  return value;
} // getAggregativeValue

/**
 * Returns the problem being solved
 * @return The problem.
 */
Problem * Solution::getProblem() {
  return problem_ ;
} // getAggregativeValue


/**
 * Returns the number of bits of the chromosome in case of using a binary
 * representation
 * @return The number of bits if the case of binary variables, 0 otherwise
 */
//int getNumberOfBits();


//Variable **Solution::getDecisionVariables() {
//  return decisionVariables_;
//}
//
//int Solution::getNumberOfVariables() {
//    return numberOfVariables_;
//}
