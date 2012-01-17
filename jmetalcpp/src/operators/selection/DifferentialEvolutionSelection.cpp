/**
  * @file DifferentialEvolutionSelection.cpp
  * @author Esteban López
  * @date 16 January 2012
**/


#include <DifferentialEvolutionSelection.h>


/**
 * @class DifferentialEvolutionSelection
 * @brief Class implementing the selection operator used in DE: three different solutions
 * are returned from a population.
**/


/**
 * Constructor
 */
DifferentialEvolutionSelection::DifferentialEvolutionSelection(map<string, void *> parameters)
: Selection(parameters) {}


/**
 * Executes the operation
 * @param object An object containing the population and the position (index)
 *               of the current individual
 * @return An object containing the three selected parents
 */
void * DifferentialEvolutionSelection::execute(void * object) {

  // cout << "DifferentialEvolutionSelection starting..." << endl;

  void ** parameters = (void **)object ;
  SolutionSet * population = (SolutionSet *) parameters[0];
  int index = *(int *) parameters[1] ;

  // cout << population->get(0)->getRank() << endl;
  // cout << population->size() << endl;
  // cout << index << endl;

  Solution ** parents = new Solution*[3];
  int r1, r2, r3;

  if (population->size() < 4) {
    cerr << "DifferentialEvolutionSelection: the population has less than four solutions" << endl;
    exit(-1);
  }

  do {
    r1 = PseudoRandom::randInt(0,population->size()-1);
    //cout << "r1=" << r1 << endl;
  } while ( r1==index );
  do {
    r2 = PseudoRandom::randInt(0,population->size()-1);
    //cout << "r2=" << r2 << endl;
  } while ( r2==index || r2==r1 );
  do {
    r3 = PseudoRandom::randInt(0,population->size()-1);
    //cout << "r3=" << r3 << endl;
  } while( r3==index || r3==r1 || r3==r2 );

  parents[0] = population->get(r1);
  parents[1] = population->get(r2);
  parents[2] = population->get(r3);

  return parents ;

} // execute
