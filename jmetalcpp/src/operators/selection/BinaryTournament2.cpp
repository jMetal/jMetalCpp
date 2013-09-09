//  BinaryTournament2.cpp
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


#include <BinaryTournament2.h>


/**
 * @class BinaryTournament2
 * @brief This class implements a binary tournament selection operator
**/


/**
 * Constructor
 * Creates a new instance of the Binary tournament operator (Deb's
 * NSGA-II implementation version)
 */
BinaryTournament2::BinaryTournament2(map<string, void *> parameters)
: Selection(parameters) {
  index_ = 0;
  a_ = new int[1]; // Initialized as dummy
  dominance_ = new DominanceComparator();
  if (dominance_ == NULL) {
    cout << "BinaryTournament::BinaryTournament: error creating comparator" ;
    cout << endl ;
    exit(-1) ;
  }
}


/**
 * Destructor
 */
BinaryTournament2::~BinaryTournament2() {
  delete dominance_;
  delete [] a_;
} // ~BinaryTournament2

  
/**
* Performs the operation
* @param object Object representing a SolutionSet
* @return the selected solution
*/
void * BinaryTournament2::execute(void * object) {

  SolutionSet * population = (SolutionSet *)object;

  if (index_ == 0) //Create the permutation
  {
    PermutationUtility * permutationUtility = new PermutationUtility();
    delete [] a_;
    a_= permutationUtility->intPermutation(population->size());
    delete permutationUtility;
  }

  Solution * solution1;
  Solution * solution2;
  solution1 = population->get(a_[index_]);
  solution2 = population->get(a_[index_+1]);

  index_ = (index_ + 2) % population->size();

  int flag = dominance_->compare(solution1,solution2);
  if (flag == -1)
    return solution1;
  else if (flag == 1)
    return solution2;
  else if (solution1->getCrowdingDistance() > solution2->getCrowdingDistance())
    return solution1;
  else if (solution2->getCrowdingDistance() > solution1->getCrowdingDistance())
    return solution2;
  else
    if (PseudoRandom::randDouble()<0.5)
      return solution1;
    else
      return solution2;

} // execute 
