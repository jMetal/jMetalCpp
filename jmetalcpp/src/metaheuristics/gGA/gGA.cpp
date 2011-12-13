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
//		cout << "Poblacion num. " << i << endl;
		newSolution = new Solution(problem_);
//		cout << "Solution inicializada" << endl;
		problem_->evaluate(newSolution);
//		cout << "Solution evaluada" << endl;
		problem_->evaluateConstraints(newSolution);
//		cout << "Solution constantes evaluadas" << endl;
		evaluations++;
		population->add(newSolution);
//		cout << "Solution añadida a la poblacion" << endl;
	} //for

	cout << "gGA: Poblacion inicializada con size = " << population->size() << endl;
	cout << "gGA: Maximo de evaluaciones: " << maxEvaluations << endl;

	// Generations
	while (evaluations < maxEvaluations) {
		cout << "gGA: Eval n. " << evaluations << endl;

		// Create the offSpring solutionSet
		offspringPopulation = new SolutionSet(populationSize);
		Solution ** parents = new Solution*[2];

		for (int i = 0; i < (populationSize / 2); i++) {
			if (evaluations < maxEvaluations) {
				//obtain parents
				parents[0] = (Solution *) (selectionOperator->execute(population));
				parents[1] = (Solution *) (selectionOperator->execute(population));
				Solution ** offSpring = (Solution **) (crossoverOperator->execute(parents));
				mutationOperator->execute(offSpring[0]);
				mutationOperator->execute(offSpring[1]);
				problem_->evaluate(offSpring[0]);
				problem_->evaluateConstraints(offSpring[0]);
				problem_->evaluate(offSpring[1]);
				problem_->evaluateConstraints(offSpring[1]);
				offspringPopulation->add(offSpring[0]);
				offspringPopulation->add(offSpring[1]);
				evaluations += 2;
			} // if
		} // for

		cout << "gGA: Eval2 n. " << evaluations << ". Best fitness: "
				<< population->get(0)->getObjective(0)<< endl;
		cout << "gGA: Eval2 n. " << evaluations << endl;

		population->sort(comparator) ;
		offspringPopulation->sort(comparator) ;

		offspringPopulation->replace(offspringPopulation->size()-1, new Solution(population->get(0))) ;
		offspringPopulation->replace(offspringPopulation->size()-2, new Solution(population->get(1))) ;

		population->clear() ;
		for (int i = 0; i < populationSize; i++)
			population->add(offspringPopulation->get(i)) ;
		offspringPopulation->clear() ;
	}

  SolutionSet * resultPopulation  = new SolutionSet(1) ;
  resultPopulation->add(population->get(0)) ;

  return resultPopulation ;
} // execute
