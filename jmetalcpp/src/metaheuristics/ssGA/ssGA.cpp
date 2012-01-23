/*
 * @file ssGA.cpp
 * @author Esteban López
 * @date 20 January 2012
 */


#include <ssGA.h>


/**
 * Class implementing a steady-state genetic algorithm
 */


/**
 * Constructor
 * Create a new SSGA instance.
 * @param problem Problem to solve
 */
ssGA::ssGA(Problem *problem) : Algorithm(problem) {
} // ssGA


/*
 * Execute the SSGA algorithm
 */
SolutionSet * ssGA::execute() {

  int populationSize;
  int maxEvaluations;
  int evaluations;

  SolutionSet * population;

  Operator * mutationOperator;
  Operator * crossoverOperator;
  Operator * selectionOperator;

  Comparator * comparator = new ObjectiveComparator(0); // Single objective comparator

  Operator * findWorstSolution;
  map<string, void *> parameters; // Operator parameters
  parameters["comparator"] = comparator;

  findWorstSolution = new WorstSolutionSelection(parameters) ;

  //Read the parameters
  populationSize = *(int *) getInputParameter("populationSize");
  maxEvaluations = *(int *) getInputParameter("maxEvaluations");

  //Initialize the variables
  population = new SolutionSet(populationSize);
  evaluations = 0;

  //Read the operators
  mutationOperator = operators_["mutation"];
  crossoverOperator = operators_["crossover"];
  selectionOperator = operators_["selection"];

  // Create the initial population
  Solution * newIndividual;
  for (int i = 0; i < populationSize; i++) {
    newIndividual = new Solution(problem_);
    problem_->evaluate(newIndividual);
    evaluations++;
    population->add(newIndividual);
  } // for

  // main loop
  while (evaluations < maxEvaluations) {
    Solution ** parents = new Solution*[2];

    // Selection
    parents[0] = (Solution*)selectionOperator->execute(population);
    parents[1] = (Solution*)selectionOperator->execute(population);

    // Crossover
    Solution ** offspring = (Solution **) crossoverOperator->execute(parents);

    // Mutation
    mutationOperator->execute(offspring[0]);

    // Evaluation of the new individual
    problem_->evaluate(offspring[0]);

    evaluations ++;

    // Replacement: replace the last individual is the new one is better
    int worstIndividual = *(int *) findWorstSolution->execute(population);
//    system("pause");
//    cout << "Worst individual: " << worstIndividual << endl;
//    system("pause");

    if (comparator->compare(population->get(worstIndividual), offspring[0]) > 0) {
      population->remove(worstIndividual);
      population->add(offspring[0]);
    } // if
  } // while

  // Return a population with the best individual

  SolutionSet * resultPopulation  = new SolutionSet(1);
  resultPopulation->add(population->best(comparator));

  return resultPopulation;
} // execute
