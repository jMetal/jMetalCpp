/**
  * @file BinaryTournament2.cpp
  * @author Juan J. Durillo
  * @author Antonio J. Nebro
  * @author Esteban López
  * @date 01 December 2011
**/


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
	dominance_ = new DominanceComparator();
  if (dominance_ == NULL) {
  	cout << "BinaryTournament::BinaryTournament: error creating comparator" ;
  	cout << endl ;
    exit(-1) ;
  }
}

  
/**
* Performs the operation
* @param object Object representing a SolutionSet
* @return the selected solution
*/
void * BinaryTournament2::execute(void * object) {

	SolutionSet * population = (SolutionSet *)object;

//	cout << "Poblacion con tamaño: " << population->size() << endl;
//	for (int i=0; i<population->size(); i++) {
//		cout << "pop[" << i << "] = " << population->get(i)->getAggregativeValue() << endl;
//	}


  if (index_ == 0) //Create the permutation
  {
  	PermutationUtility * permutationUtility = new PermutationUtility();
    a_= permutationUtility->intPermutation(population->size());
  }

//	for (int i=0; i<population->size(); i++) {
//		cout << "a_[" << i << "] = " << a_[i] << endl;
//	}
	//cout << "BinaryTournament2: valor de index = " << index_ << endl;
	//cout << "BinaryTournament2: population->size() = " << population->size() << endl;

  Solution * solution1;
  Solution * solution2;
  solution1 = population->get(a_[index_]);
  solution2 = population->get(a_[index_+1]);

  index_ = (index_ + 2) % population->size();

  //cout << "BinaryTournament2: new valor de index = " << index_ << endl;

  int flag = dominance_->compare(solution1,solution2);
  //cout << "BinaryTournament2: CrowdingDistance de solution1 = " << solution1->getCrowdingDistance() << endl;
  //cout << "BinaryTournament2: CrowdingDistance de solution2 = " << solution2->getCrowdingDistance() << endl;
  //cout << "BinaryTournament2: El valor de flag es " << flag << endl;
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
