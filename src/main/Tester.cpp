
//  gGA_main.cpp
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
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

#include <Problem.h>
#include <Algorithm.h>
#include <Solution.h>
#include <SBXCrossover.h>
#include <PolynomialMutation.h>
#include <BinaryTournament2.h>
#include <ProblemFactory.h>
#include <iostream>
#include <gGA.h>
#include <time.h>
#include <DifferentialEvolutionCrossover.h>
#include <DifferentialEvolutionSelection.h>

#include <InsertionMutation.h>
#include <InversionMutation.h>
#include <Sphere.h>
#include <PositionBasedCrossover.h>
int main(int argc, char ** argv) {

  // clock_t t_ini, t_fin;

  Problem   * problem   ; // The problem to solve
  Algorithm * algorithm ; // The algorithm to use
  Operator  * crossover ; // Crossover operator
  Operator  * mutation  ; // Mutation operator
  Operator  * selection ; // Selection operator



  problem= new Sphere("",5);
  Solution* temp =  new Solution(problem);
  Solution* temp1 =  new Solution(problem);
  Solution** parents = new Solution*[2];
  parents[0]= new Solution(temp);
  parents[1]= new Solution(temp1);
  std::cout << temp->toString() <<std::endl;
  std::cout << temp1->toString() <<std::endl;


  // Mutation and Crossover for Real codification
  map<string, void *> parameters;
  double mutationProbability =0.5;
  parameters["probability"] =  &mutationProbability ;
  /*
  mutation = new InsertionMutation(parameters);
  mutation->execute(temp);
  std::cout << temp->toString() <<std::endl;
  */
 // crossover = new OrderCrossover(parameters);
  //crossover->execute(offSpring);
 // Solution ** offSpring = (Solution **) (crossover->execute(parents));
  //std::cout << "done crossover "<<std::endl;
  //std::cout << offSpring[0]->toString() <<std::endl;
  //std::cout << offSpring[1]->toString() <<std::endl;

  /*
  double crossoverProbability = 0.9;
  double distributionIndexValue1 = 20.0;
  parameters["probability"] =  &crossoverProbability ;
  parameters["distributionIndex"] = &distributionIndexValue1 ;



  //crossover = new SBXCrossover(parameters);
  crossover = new OrderCrossover(parameters);



  parameters.clear();
  double mutationProbability = 1.0/problem->getNumberOfVariables();
  double distributionIndexValue2 = 20.0;
  parameters["probability"] = &mutationProbability;
  parameters["distributionIndex"] = &distributionIndexValue2 ;
  mutation = new PolynomialMutation(parameters);
  //mutation = new InsertionMutation(parameters);

	// Selection Operator
	parameters.clear();
	selection = new BinaryTournament2(parameters) ;

	// Add the operators to the algorithm



*/
  delete crossover;
  delete mutation;
  delete selection;

  delete algorithm;

} // main
