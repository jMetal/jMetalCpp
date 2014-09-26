//  AdaptiveRandomNeighborhood.cpp
//
//  Author:
//       Esteban López-Camacho
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


#include "AdaptiveRandomNeighborhood.h"

/**
 * Class representing an adaptive random neighborhood
 */


/**
 * Constructor.
 * Defines a neighborhood of a given size.
 */
AdaptiveRandomNeighborhood::AdaptiveRandomNeighborhood(SolutionSet * solutionSet, int numberOfRandomNeighbours) {
  solutionSet_ = solutionSet;
  numberOfRandomNeighbours_ = numberOfRandomNeighbours;
  //problem_ = solutionSet_->get(0)->getProblem() ;

  //list_ = new int * [solutionSet_->size()];

  for (int i = 0; i < solutionSet_->size(); i++) {
    //list_[i] = new int []
    vector<int> list_i;
    list_i.push_back(i);
    list_.push_back(list_i);
  }

//  if(std::find(v.begin(), v.end(), x) != v.end()) {
//      /* v contains x */
//  } else {
//      /* v does not contain x */
//  }

  //cout << "list: " << list_ << endl;
  for (int i = 0; i < solutionSet_->size(); i++) {
    //list_.at(i).push_back(i);
    for (int j = 0; j < numberOfRandomNeighbours_; j++) {
      int random = PseudoRandom::randInt(0, solutionSet_->size() - 1);
      //cout << "i: " << i >> " random: " << random << " listb: " << list_at(random) << endl;
      //if (!list_.at(random).contains((Integer) i))
      if (find(list_.at(random).begin(), list_.at(random).end(), i) == list_.at(random).end()) {
        list_.at(random).push_back(i);
      }
    }
  }
  //cout <<  "L: " << list_ << endl;
  cout << "L:" << endl;
  for (int i = 0; i < list_.size(); i++) {
    cout << "\t[";
    for (int j = 0; j < list_.at(i).size(); j++) {
      cout << list_.at(i).at(j);
      if (j < list_.at(i).size()-1) {
        cout << ",";
      } else {
        cout << "]" << endl;
      }
    }
  }
}


vector<int> AdaptiveRandomNeighborhood::getNeighbors(int i) {
  if (i > list_.size()) {
    cerr << "Error in AdaptiveRandomNeighborhood.getNeighbors"
        << "the parameter " << i << " is less than " << list_.size()
        << endl;
    exit(-1);
  }
  return list_.at(i);
}


int AdaptiveRandomNeighborhood::getNumberOfRandomNeighbours() {
  return numberOfRandomNeighbours_;
}


SolutionSet * AdaptiveRandomNeighborhood::getBestFitnessSolutionInNeighborhood(Comparator * comparator) {
  SolutionSet * result = new SolutionSet();
  for (int i = 0; i < list_.size(); i++) {
    Solution * bestSolution = solutionSet_->get(list_.at(i).at(0));
    for (int j = 1; j < list_.at(i).size(); j++) {
      if (comparator->compare(bestSolution, solutionSet_->get(list_.at(i).at(j))) > 0) {
        bestSolution = solutionSet_->get(list_.at(i).at(j));
      }
    }
    result->add(bestSolution);
  }

  return result;
}


vector<vector<int>> AdaptiveRandomNeighborhood::getNeighborhood() {
  return list_;
}


void AdaptiveRandomNeighborhood::recompute() {
  list_.clear();

  for (int i = 0; i < solutionSet_->size(); i++) {
    //list_[i] = new int []
    vector<int> list_i;
    list_i.push_back(i);
    list_.push_back(list_i);
  }

  for (int i = 0; i < solutionSet_->size(); i++) {
    for (int j = 0; j < numberOfRandomNeighbours_; j++) {
      int random = PseudoRandom::randInt(0, solutionSet_->size() - 1);
      //if (!list_.at(random).contains((Integer) i))
      if (find(list_.at(random).begin(), list_.at(random).end(), i) == list_.at(random).end()) {
        list_.at(random).push_back(i);
      }
    }
  }

}


/*
public String toString() {
  String result = "";
  for (int i = 0; i < list_.size(); i++) {
    result += i + ": ";
    for (int j = 0; j < list_.get(i).size(); j++) {
      result += list_.get(i).get(j) + " ";
    }
    result += "\n";
  }

  return result;
}
*/
