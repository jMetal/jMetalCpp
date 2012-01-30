/*
 * @file gGA.cpp
 * @author Antonio J. Nebro
 * @date 25 November 2011
 */

#include <gGA.h>

/*
 * This class implements the NSGA-II algorithm.
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
gGA::gGA(Problem *problem) : Algorithm(problem) {
} // gGA


/*
 * Runs the NSGA-II algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet * gGA::execute() {

	int populationSize;
	int maxEvaluations;
	int evaluations;

	SolutionSet * population;
	SolutionSet * offspringPopulation;

	Operator * mutationOperator;
	Operator * crossoverOperator;
	Operator * selectionOperator;

	Comparator * comparator = new ObjectiveComparator(0) ;

	//Read the parameters
	populationSize = *(int *) getInputParameter("populationSize");
	maxEvaluations = *(int *) getInputParameter("maxEvaluations");
	// TODO: indicators = (QualityIndicator) getInputParameter("indicators");
	cout << "populationSize = " << populationSize << endl;
	cout << "maxEvaluations = " << maxEvaluations << endl;

	//Initialize the variables
	population = new SolutionSet(populationSize);
	evaluations = 0;

	cout << "Poblacion inicializada con maxsize = " << population->getMaxSize() << endl;
	cout << "Poblacion inicializada con size = " << population->size() << endl;
	cout << "Problema: " << problem_->getName() << endl;

	//Read the operators
	mutationOperator = operators_["mutation"];
	crossoverOperator = operators_["crossover"];
	selectionOperator = operators_["selection"];

	cout << "Comienza la inicializacion de la poblacion con size " << populationSize << endl;

	// Create the initial solutionSet
	Solution * newSolution;
	for (int i = 0; i < populationSize; i++) {
		newSolution = new Solution(problem_);
		problem_->evaluate(newSolution);
		problem_->evaluateConstraints(newSolution);
		evaluations++;
		population->add(newSolution);
	} //for

	cout << "gGA: Poblacion inicializada con size = " << population->size() << endl;
	cout << "gGA: Maximo de evaluaciones: " << maxEvaluations << endl;

	// Generations
	while (evaluations < maxEvaluations) {
		cout << "Evals: " << evaluations << ". Fitness: "
				<< population->best(comparator)->getObjective(0)<< endl;

		// Create the offSpring solutionSet
		offspringPopulation = new SolutionSet(populationSize);
		Solution ** parents = new Solution*[2];

		for (int i = 0; i < (populationSize / 2); i++) {
			if (evaluations < maxEvaluations) {
				cout << "GA main loop. i = " << i << endl ;
				//obtain parents
				cout << "GA Selection 1" << endl ;
				parents[0] = (Solution *) (selectionOperator->execute(population));
				cout << "GA Selection 2" << endl ;
				parents[1] = (Solution *) (selectionOperator->execute(population));
				cout << "GA Crossover" << endl ;
				Solution ** offSpring = (Solution **) (crossoverOperator->execute(parents));
				cout << "GA Mutation 1" << endl ;
				mutationOperator->execute(offSpring[0]);
				cout << "GA Mutation 2" << endl ;
				mutationOperator->execute(offSpring[1]);
				cout << "GA evaluate 1" << endl ;
				problem_->evaluate(offSpring[0]);
				problem_->evaluateConstraints(offSpring[0]);
				cout << "GA evaluate 2" << endl ;
				problem_->evaluate(offSpring[1]);
				problem_->evaluateConstraints(offSpring[1]);

				offspringPopulation->add(offSpring[0]);
				offspringPopulation->add(offSpring[1]);
				evaluations += 2;
				delete[] offSpring;
			} // if
		} // for
		delete[] parents;
		
		/*
		for (int i = 0; i < (populationSize / 2); i++) {
			if (evaluations < maxEvaluations) {
				//obtain parents
				parents[0] = (Solution *) (selectionOperator->execute(population));
				parents[1] = (Solution *) (selectionOperator->execute(population));
				Solution ** offSpring = (Solution **) (crossoverOperator->execute(parents));
				cout << "CROSSOVER" << endl ;

				cout << "P0: " << ((Binary *)(parents[0]->getDecisionVariables()[0]))->toString()
						<< " " << parents[0]->getObjective(0) << endl ;
				cout << "P1: " << ((Binary *)(parents[1]->getDecisionVariables()[0]))->toString()
						<< " " << parents[1]->getObjective(0) << endl ;

				cout << "Of0: " << ((Binary *)(offSpring[0]->getDecisionVariables()[0]))->toString()
						<< " " << offSpring[0]->getObjective(0) << endl ;
				cout << "Of1: " << ((Binary *)(offSpring[1]->getDecisionVariables()[0]))->toString()
						<< " " << offSpring[1]->getObjective(0) << endl ;

				mutationOperator->execute(offSpring[0]);
				mutationOperator->execute(offSpring[1]);
				cout << "MUTATION" << endl ;
				problem_->evaluate(offSpring[0]);
				problem_->evaluateConstraints(offSpring[0]);
				problem_->evaluate(offSpring[1]);
				problem_->evaluateConstraints(offSpring[1]);

				cout << "P0 : " << ((Binary *)(parents[0]->getDecisionVariables()[0]))->toString()
						<< " " << parents[0]->getObjective(0) << endl ;
				cout << "P1 : " << ((Binary *)(parents[1]->getDecisionVariables()[0]))->toString()
						<< " " << parents[1]->getObjective(0) << endl ;
				cout << "Of0: " << ((Binary *)(offSpring[0]->getDecisionVariables()[0]))->toString()
						<< " " << offSpring[0]->getObjective(0) << endl ;
				cout << "Of1: " << ((Binary *)(offSpring[1]->getDecisionVariables()[0]))->toString()
						<< " " << offSpring[1]->getObjective(0) << endl ;
//exit(0) ;
				offspringPopulation->add(offSpring[0]);
				offspringPopulation->add(offSpring[1]);
				evaluations += 2;

				//exit(0) ;

			} // if
		} // for
    */
		population->sort(comparator) ;
		offspringPopulation->sort(comparator) ;

		delete offspringPopulation->get(offspringPopulation->size()-1);
		delete offspringPopulation->get(offspringPopulation->size()-2);
		offspringPopulation->replace(offspringPopulation->size()-1, new Solution(population->get(0))) ;
		offspringPopulation->replace(offspringPopulation->size()-2, new Solution(population->get(1))) ;

		for (int i=0;i<population->size();i++) {
      delete population->get(i);
    }
		population->clear() ;
		
		for (int i = 0; i < populationSize; i++)
			population->add(offspringPopulation->get(i)) ;
		offspringPopulation->clear() ;
		delete offspringPopulation;
	}

	delete comparator;

  SolutionSet * resultPopulation  = new SolutionSet(1) ;
  resultPopulation->add(new Solution(population->get(0))) ;
  delete population;

  return resultPopulation ;
} // execute
