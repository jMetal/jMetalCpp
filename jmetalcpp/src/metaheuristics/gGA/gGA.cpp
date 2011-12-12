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
	cout << "Inicializado por segunda vez..." << endl;

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
/*
	// Generations
	while (evaluations < maxEvaluations) {

		cout << "gGA: Eval n. " << evaluations << endl;

		// Create the offSpring solutionSet
		offspringPopulation = new SolutionSet(populationSize);
		Solution ** parents = new Solution*[2];

		cout << "gGA: Comenzamos a operar..." << endl;

		for (int i = 0; i < (populationSize / 2); i++) {
			if (evaluations < maxEvaluations) {
				//obtain parents
				parents[0] = (Solution *) (selectionOperator->execute(population));
				parents[1] = (Solution *) (selectionOperator->execute(population));
			  cout << "gGA: AggregativeValue de parents[0] = " << parents[0]->getAggregativeValue() << endl;
			  cout << "gGA: AggregativeValue de parents[1] = " << parents[1]->getAggregativeValue() << endl;
				cout << "Ya tenemos los padres..." << endl;
				Solution ** offSpring = (Solution **) (crossoverOperator->execute(parents));
				cout << "Hallado offspring..." << endl;
				mutationOperator->execute(offSpring[0]);
				mutationOperator->execute(offSpring[1]);
				cout << "Ejecutada mutacion..." << endl;
				problem_->evaluate(offSpring[0]);
				problem_->evaluateConstraints(offSpring[0]);
				problem_->evaluate(offSpring[1]);
				problem_->evaluateConstraints(offSpring[1]);
				offspringPopulation->add(offSpring[0]);
				offspringPopulation->add(offSpring[1]);
				evaluations += 2;
			} // if
		} // for

		cout << "gGA: Eval2 n. " << evaluations << endl;
		cout << "gGA: Poblacion con size = " << population->size() << endl;
		cout << "gGA: offspringPopulation con size = " << offspringPopulation->size() << endl;

		// Create the solutionSet union of solutionSet and offSpring
		unionSolution = population->join(offspringPopulation);

		cout << "gGA: unionSolution con size = " << unionSolution->size() << endl;
		cout << "gGA: Ejecutada unión..." << endl;

		// Ranking the union
		Ranking * ranking = new Ranking(unionSolution);

		cout << "gGA: Inicializado ranking con tamaño = " << ranking->getNumberOfSubfronts() << endl;

		int remain = populationSize;
		int index = 0;
		SolutionSet * front = NULL;
		population->clear();

		// Obtain the next front
		front = ranking->getSubfront(index);

		cout << "gGA: Obtenido frente de pareto con tamaño " << front->size() << endl;
		cout << "gGA: remain = " << remain << endl;

		while ((remain > 0) && (remain >= front->size())) {
			//Assign crowding distance to individuals
			distance->crowdingDistanceAssignment(front, problem_->getNumberOfObjectives());

			cout << "gGA: distance calculada... " << endl;

			//Add the individuals of this front
			for (int k = 0; k < front->size(); k++) {
				population->add(front->get(k));
				cout << "gGA: Añadido frente(" << k << ") a la poblacion con tamaño " << population->size() << endl;
			} // for

			//Decrement remain
			remain = remain - front->size();

			cout << "gGA: remain = " << remain << endl;

			//Obtain the next front
			index++;
			if (remain > 0) {
				cout << "gGA: index = " << index << endl;
				front = ranking->getSubfront(index);
				cout << "gGA: Obtenido frente de pareto con tamaño " << front->size() << endl;
			} // if
		} // while

		// Remain is less than front(index).size, insert only the best one
		if (remain > 0) {  // front contains individuals to insert
			distance->crowdingDistanceAssignment(front, problem_->getNumberOfObjectives());
			front->sort(new CrowdingComparator());
			for (int k = 0; k < remain; k++) {
				population->add(front->get(k));
			} // for

			remain = 0;
		} // if

		// This piece of code shows how to use the indicator object into the code
		// of NSGA-II. In particular, it finds the number of evaluations required
		// by the algorithm to obtain a Pareto front with a hypervolume higher
		// than the hypervolume of the true Pareto front.
// TODO:
//		if ((indicators != NULL) &&
//			(requiredEvaluations == 0)) {
//			double HV = indicators.getHypervolume(population);
//			if (HV >= (0.98 * indicators.getTrueParetoFrontHypervolume())) {
//				requiredEvaluations = evaluations;
//			} // if
//		} // if
	} // while

	// Return as output parmeter the required evaluations
	// TODO:
	//setOutputParameter("evaluations", requiredEvaluations);

	// Return the first non-dominated front
	Ranking * ranking = new Ranking(population);
	return ranking->getSubfront(0);
*/
  SolutionSet * resultPopulation  = new SolutionSet(1) ;
  resultPopulation->add(population->get(0)) ;

  return resultPopulation ;
} // execute
