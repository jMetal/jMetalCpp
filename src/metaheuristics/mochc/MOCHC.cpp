//  MOCHC.cpp
//  //
//  //  Author:
//  //       Juanjo
//  //
//  //  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
//  //
//  //  This program is free software: you can redistribute it and/or modify
//  //  it under the terms of the GNU Lesser General Public License as published by
//  //  the Free Software Foundation, either version 3 of the License, or
//  //  (at your option) any later version.
//  //
//  //  This program is distributed in the hope that it will be useful,
//  //  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  //  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  //  GNU Lesser General Public License for more details.
//  //
//  //  You should have received a copy of the GNU Lesser General Public License
//  //  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include <MOCHC.h>

bool MOCHC::equalsIndividuals(Solution & s1, Solution & s2) {
	
	for (int var = 0; var < s1.getNumberOfVariables(); var++) {
		Binary *b1, *b2;
		b1 = (Binary *)s1.getDecisionVariables()[var];
		b2 = (Binary *)s2.getDecisionVariables()[var];
		bool found = true;
		for (int bit = 0; bit < b1->getNumberOfBits(); bit++) {		
			if (b1->getIth(bit)!=b2->getIth(bit)) {
				return false;
			}
		}
	}					
					
	return true;
}

bool MOCHC::exist(Solution & s1, SolutionSet & set2) {
	for (int i = 0; i < set2.size(); i++) {
		if (equalsIndividuals(s1,*set2.get(i)))
			return true;
	}
	return false;
}


bool MOCHC::equals(SolutionSet & set1, SolutionSet & set2) {

	if (set1.size() != set2.size())
		return false;

	for (int i = 0; i < set1.size(); i++) {
		if (!exist(*set1.get(i),set2))
			return false;
	}
	return true;
} // returns the equal


int MOCHC::hammingDistance(Solution & sol1, Solution & sol2) {
	int distance = 0;
	for (int i = 0; i < problem_->getNumberOfVariables(); i++) {
		Binary *varFrom1, *varFrom2;
		varFrom1 = (Binary *)sol1.getDecisionVariables()[i];
		varFrom2 = (Binary *)sol2.getDecisionVariables()[i];
		distance += varFrom1->hammingDistance(varFrom2);			
	}
	return distance;
}


SolutionSet *MOCHC::rankingAndCrowdingSelection(SolutionSet * pop, int size) {


    SolutionSet *result = new SolutionSet(size);
    // Ranking the union
    Ranking * ranking = new Ranking(pop);    
    Distance * distance = new Distance();
    int remain = size;
    int index = 0;
    SolutionSet * front = NULL;

    // Obtain the next front
    front = ranking->getSubfront(index);

    while ((remain > 0) && (remain >= front->size())) {
      //Assign crowding distance to individuals
      distance->crowdingDistanceAssignment(front, problem_->getNumberOfObjectives());

      //Add the individuals of this front
      for (int k = 0; k < front->size(); k++) {
        result->add(new Solution(front->get(k)));
      } // for

      //Decrement remain
      remain = remain - front->size();

      //Obtain the next front
      index++;
      if (remain > 0) {
        front = ranking->getSubfront(index);
      } // if
      
    } // while

    // Remain is less than front(index).size, insert only the best one
    if (remain > 0) {  // front contains individuals to insert
      distance->crowdingDistanceAssignment(front, problem_->getNumberOfObjectives());
      Comparator * c = new CrowdingComparator();
      front->sort(c);
      delete c;
      for (int k = 0; k < remain; k++) {
        result->add(new Solution(front->get(k)));
      } // for

      remain = 0;
    } // if

    delete ranking;
    delete distance;

    return result;	
}


SolutionSet *MOCHC::execute() {
	
  int populationSize;
  int iterations;
  int maxEvaluations;
  int convergenceValue;
  int minimumDistance;
  int evaluations;

  double preservedPopulation;
  double initialConvergenceCount;
  bool condition = false;
  SolutionSet *solutionSet, *offSpringPopulation, *newPopulation; 

  Comparator * crowdingComparator = new CrowdingComparator();

  SolutionSet * population;
  SolutionSet * offspringPopulation;
  SolutionSet * unionSolution;

  Operator * cataclysmicMutation;
  Operator * crossover;
  Operator * parentSelection;


  //Read the parameters
  populationSize = *(int *) getInputParameter("populationSize");
  maxEvaluations = *(int *) getInputParameter("maxEvaluations");
  convergenceValue = *(int *) getInputParameter("convergenceValue");
  initialConvergenceCount = *(double *)getInputParameter("initialConvergenceCount");
  preservedPopulation = *(double *)getInputParameter("preservedPopulation");
  

  //Read the operators
  cataclysmicMutation = operators_["mutation"];
  crossover	      = operators_["crossover"];
  parentSelection     = operators_["parentSelection"];
  
  iterations  = 0;
  evaluations = 0;

  // calculating the maximum problem sizes .... 
  Solution * sol = new Solution(problem_);
  int size = 0;
  for (int var = 0; var < problem_->getNumberOfVariables(); var++) {
	Binary *binaryVar;
        binaryVar  = (Binary *)sol->getDecisionVariables()[var];
	size += binaryVar->getNumberOfBits();
  } 
  minimumDistance = (int) std::floor(initialConvergenceCount*size);
  std::cout << minimumDistance << std::endl;
  std::cout << convergenceValue << std::endl;

  // Create the initial solutionSet
  Solution * newSolution;
  population = new SolutionSet(populationSize);
  for (int i = 0; i < populationSize; i++) {
    newSolution = new Solution(problem_);
    problem_->evaluate(newSolution);
    problem_->evaluateConstraints(newSolution);
    evaluations++;
    population->add(newSolution);
  } //for


  while (!condition) {
	offSpringPopulation = new SolutionSet(populationSize);
 	Solution **parents = new Solution*[2];
	
	for (int i = 0; i < population->size()/2; i++) {
  		parents[0] = (Solution *) (parentSelection->execute(population));
		parents[1] = (Solution *) (parentSelection->execute(population));

		if (hammingDistance(*parents[0],*parents[1])>= minimumDistance) {
		   Solution ** offSpring = (Solution **) (crossover->execute(parents));
		   problem_->evaluate(offSpring[0]);
		   problem_->evaluateConstraints(offSpring[0]);
	           problem_->evaluate(offSpring[1]);
		   problem_->evaluateConstraints(offSpring[1]);
		   evaluations+=2;
		   offSpringPopulation->add(offSpring[0]);
		   offSpringPopulation->add(offSpring[1]);
		}		
	}  
	SolutionSet *join = population->join(offSpringPopulation);
 	delete offSpringPopulation;

	newPopulation = rankingAndCrowdingSelection(join,populationSize);
	delete join;
        if (equals(*population,*newPopulation)) {
		std::cout << "populations are equals" << std::endl;
		minimumDistance--;
	}   

	if (minimumDistance <= -convergenceValue) {
		minimumDistance = (int) (1.0/size * (1-1.0/size) * size);
		int preserve = (int) std::floor(preservedPopulation*populationSize);
		newPopulation->clear(); //do the new in c++ really hurts me(juanjo)
		population->sort(crowdingComparator);
		for (int i = 0; i < preserve; i++) {
			newPopulation->add(new Solution(population->get(i)));
		}
		for (int i = preserve; i < populationSize; i++) {
			Solution * solution = new Solution(population->get(i));
			cataclysmicMutation->execute(solution);
			problem_->evaluate(solution);
			problem_->evaluateConstraints(solution);	
			newPopulation->add(solution);
		}
		
	}

	iterations++;
	delete population;
	population = newPopulation;
	if (evaluations >= maxEvaluations) {
		condition = true;		
	}
  }

  return population;

}
