//  SolutionSet.cpp
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


#include <SolutionSet.h>


/**
 * Constructor.
 * Creates an unbounded solution set.
 */
SolutionSet::SolutionSet () {
  capacity_ = 0;
} // SolutionSet


/**
 * Creates a empty solutionSet with a maximum capacity.
 * @param maximumSize Maximum size.
 */
SolutionSet::SolutionSet (int maximumSize) {
  capacity_ = maximumSize;
} // SolutionSet


/**
 * Destructor
 */
SolutionSet::~SolutionSet() {
  for (int i = 0; i < solutionsList_.size(); i++) {
    delete solutionsList_[i];
  }
} // ~SolutionSet


/**
 * Inserts a new solution into the SolutionSet.
 * @param solution The <code>Solution</code> to store
 * @return True If the <code>Solution</code> has been inserted, false
 * otherwise.
 */
bool SolutionSet::add(Solution * solution) {
  if (solutionsList_.size() >= capacity_) {
    cout << "Error in class SolutionSet the maximum capacity of the set has been reached" << endl;
    exit(-1);
  }
  solutionsList_.push_back(solution);
  return true;
} // add


/**
 * Inserts a new solution into the SolutionSet in a specific position.
 * @param index The position where to store the solution
 * @param solution The <code>Solution</code> to store
 * @return True If the <code>Solution</code> has been inserted, false
 * otherwise.
 */
bool SolutionSet::add(int index, Solution * solution) {
  solutionsList_.insert(solutionsList_.begin()+index, solution);
  return true;
}

/**
 * Returns the ith solution in the set.
 * @param i Position of the solution to obtain.
 * @return The <code>Solution</code> at the position i.
 * @throws IndexOutOfBoundsException.
 */
Solution * SolutionSet::get(int i) {
  if (i < 0 || i >= solutionsList_.size()) {
    cout << "Error in class SolutionSet trying to access to an element out of range" << endl;
    exit(-1);
  }
  return solutionsList_[i];
} // get


/**
 * Returns the maximum capacity of the solution set
 * @return The maximum capacity of the solution set
 */
int SolutionSet::getMaxSize() {
  return capacity_;
} // getMaxSize


/**
 * Sorts a SolutionSet using a <code>Comparator</code>.
 * @param comparator <code>Comparator</code> used to sort.
 */
void SolutionSet::sort(Comparator * comparator){
  if (comparator == NULL) {
    cout << "Error. No criterium for compare exist" << endl;
    exit(-1);
  } // if
  for (int i = 0; i < solutionsList_.size(); i++) {
    for (int j = i+1; j < solutionsList_.size(); j++) {
      if ((comparator->compare(solutionsList_[i],solutionsList_[j]))==1) {
        Solution *tmp = solutionsList_[i];
        solutionsList_[i] = solutionsList_[j];
        solutionsList_[j] = tmp;
      }
    }
  } // At this point the solution set will be sorted
} // sort


/**
 * Returns the index of the best Solution using a <code>Comparator</code>.
 * If there are more than one occurrences, only the index of the first one is returned
 * @param comparator <code>Comparator</code> used to compare solutions.
 * @return The index of the best Solution attending to the comparator or
 * <code>-1<code> if the SolutionSet is empty
 */
int SolutionSet::indexBest(Comparator *comparator) {
  if (solutionsList_.empty()) {
    return -1;
  }
  int index = 0;
  Solution * bestKnown = solutionsList_[0];
  Solution * candidateSolution;
  int flag;
  for (int i = 1; i < solutionsList_.size(); i++) {
    candidateSolution = solutionsList_[i];
    flag = comparator->compare(bestKnown, candidateSolution);
    //cout << "flag: " << flag << endl;
    if (flag == 1) {
      index = i;
      bestKnown = candidateSolution;
    }
  }
  return index;
} // indexBest


/**
 * Returns the best Solution using a <code>Comparator</code>.
 * If there are more than one occurrences, only the first one is returned
 * @param comparator <code>Comparator</code> used to compare solutions.
 * @return The best Solution attending to the comparator or <code>null<code>
 * if the SolutionSet is empty
 */
Solution * SolutionSet::best(Comparator * comparator){
  int indexBest = this->indexBest(comparator);
  if (indexBest < 0) {
    return NULL;
  } else {
    return solutionsList_[indexBest];
  }
} // best


/**
 * Returns the index of the worst Solution using a <code>Comparator</code>.
 * If there are more than one occurrences, only the index of the first one is returned
 * @param comparator <code>Comparator</code> used to compare solutions.
 * @return The index of the worst Solution attending to the comparator or
 * <code>-1<code> if the SolutionSet is empty
 */
int SolutionSet::indexWorst(Comparator * comparator){
  if (solutionsList_.empty()) {
    return -1;
  }
  int index = 0;
  Solution * worstKnown = solutionsList_[0];
  Solution * candidateSolution;
  int flag;
  for (int i = 1; i < solutionsList_.size(); i++) {
    candidateSolution = solutionsList_[i];
    flag = comparator->compare(worstKnown, candidateSolution);
    if (flag == -1) {
      index = i;
      worstKnown = candidateSolution;
    }
  }
  return index;
} // indexWorst


/**
 * Returns the worst Solution using a <code>Comparator</code>.
 * If there are more than one occurrences, only the first one is returned
 * @param comparator <code>Comparator</code> used to compare solutions.
 * @return The worst Solution attending to the comparator or <code>null<code>
 * if the SolutionSet is empty
 */
Solution * SolutionSet::worst(Comparator * comparator){
  int index = indexWorst(comparator);
  if (index < 0) {
    return NULL;
  } else {
    return solutionsList_[index];
  }
} // worst


/**
 * Returns the number of solutions in the SolutionSet.
 * @return The size of the SolutionSet.
 */
int SolutionSet::size() {
  return solutionsList_.size();
} // size


/**
 * Writes the objective function values of the <code>Solution</code>
 * objects into the set in a file.
 * @param path The output file name
 */
void SolutionSet::printObjectivesToFile(string file){
  std::ofstream out(file.c_str());
  cout.setf(ios::fixed);
  for (int i = 0; i < solutionsList_.size(); i++) {
    int nObj = solutionsList_[i]->getNumberOfObjectives();
    for (int obj = 0; obj < nObj; obj++) {
      out << solutionsList_[i]->getObjective(obj) << " ";
      //cout << setprecision(15) << solutionsList_[i]->getObjective(obj) << " ";
    }
    out << endl;
    //cout << endl;
  }
  out.close();
} // printObjectivesToFile


/**
 * Writes the objective function values of the <code>Solution</code>
 * objects into the set in a file.
 * @param path The output file name
 * @param append If the objectives will be appended in case a file
 * already exists
 */
void SolutionSet::printObjectivesToFile(string file, bool append){
  if (append) {
    std::fstream out(file.c_str(), std::ios::out | std::ios::app);
    cout.setf(ios::fixed);
    for (int i = 0; i < solutionsList_.size(); i++) {
      int nObj = solutionsList_[i]->getNumberOfObjectives();
      for (int obj = 0; obj < nObj; obj++) {
        out << solutionsList_[i]->getObjective(obj) << " ";
      }
      out << endl;
    }
    out.close();
  } else {
    this->printObjectivesToFile(file);
  }
} // printObjectivesToFile


/**
 * Writes the decision variable values of the <code>Solution</code>
 * solutions objects into the set in a file.
 * @param path The output file name
 */
void SolutionSet::printVariablesToFile(string file) {
  std::ofstream out(file.c_str());
  for (int i = 0; i < solutionsList_.size(); i++) {
  	out << solutionsList_[i]->toString() << endl ;
  }
  out.close();
} // printVariablesToFile


/**
 * Writes the decision variable values of the <code>Solution</code>
 * solutions objects into the set in a file.
 * @param path The output file name
 */
void SolutionSet::printVariablesToFile(string file, bool append) {
  if (append) {
    std::fstream out(file.c_str(), std::ios::out | std::ios::app);
    for (int i = 0; i < solutionsList_.size(); i++) {
        out << solutionsList_[i]->toString() << endl ;
    }
    out.close();
  } else {
    this->printVariablesToFile(file);
  }
} // printVariablesToFile


/**
 * Empties the SolutionSet
 */
void SolutionSet::clear(){
  solutionsList_.clear();
} // clear


/**
 * Deletes the <code>Solution</code> at position i in the set.
 * @param i The position of the solution to remove.
 */
void SolutionSet::remove(int i) {
  if (i < 0 || i >= solutionsList_.size()) {
    cout << "Error in class SolutionSet trying to access to an element out of range" << endl;
    exit(-1);
  }
  solutionsList_.erase(solutionsList_.begin() + i);
} // remove


/**
 * Returns a new <code>SolutionSet</code> which is the result of the union
 * between the current solution set and the one passed as a parameter.
 * @param solutionSet SolutionSet to join with the current solutionSet.
 * @return The result of the union operation.
 */
SolutionSet * SolutionSet::join(SolutionSet *another) {
  SolutionSet *result =
      new SolutionSet(solutionsList_.size()+another->size());
  for (int i=0;i<solutionsList_.size();i++) {
    result->add(new Solution(this->get(i)));
  }
  for (int i=0;i<another->size();i++) {
    result->add(new Solution(another->get(i)));
  }
  return result;
} // join


/**
 * Replaces a solution by a new one
 * @param position The position of the solution to replace
 * @param solution The new solution
 */
void SolutionSet::replace(int position, Solution *solution) {
  if (position < 0 || position >= solutionsList_.size()) {
    cout << "Error in class SolutionSet trying to access to an element out of range" << endl;
    exit(-1);
  }
  solutionsList_[position] = solution;
} // replace


/**
 * Copies the objectives of the solution set to a matrix
 * @return A matrix containing the objectives
 */
vector <vector<double> > SolutionSet::writeObjectivesToMatrix() {
  vector <vector<double> > objectives;
  //objectives = new double[size()][get(0).numberOfObjectives()];
  for (int i = 0; i < size(); i++) {
    vector<double> list;
    for (int j = 0; j < get(0)->getNumberOfObjectives(); j++) {
      list.push_back(get(i)->getObjective(j));
    }
    objectives.push_back(list);
  }
  return objectives;
} // writeObjectivesMatrix

