/*
 * @file NSGAII.cpp
 * @author Esteban López
 * @date 25 November 2011
 */

#include <NSGAII.h>


/*
 * This class implements the NSGA-II algorithm.
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
NSGAII::NSGAII(Problem *problem) : Algorithm(problem) {

  //problem_ = problem; // MODIFIED BY AJNEBRO
  cout << "Inicializado por segunda vez..." << endl;

} // NSGAII


/*
 * Runs the NSGA-II algorithm.
 * @return a <code>SolutionSet</code> that is a set of non dominated solutions
 * as a result of the algorithm execution
 */
SolutionSet * NSGAII::execute() {

  int populationSize;
  int maxEvaluations;
  int evaluations;

  // TODO: QualityIndicator indicators; // QualityIndicator object
  int requiredEvaluations; // Use in the example of use of the
                           // indicators object (see below)

  SolutionSet * population;
  SolutionSet * offspringPopulation;
  SolutionSet * unionSolution;

  Operator * mutationOperator;
  Operator * crossoverOperator;
  Operator * selectionOperator;

  Distance * distance = new Distance();

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

  requiredEvaluations = 0;

  //Read the operators
  mutationOperator = operators_["mutation"];
  crossoverOperator = operators_["crossover"];
  selectionOperator = operators_["selection"];

  cout << "Comienza la inicializacion de la poblacion con tamaño " << populationSize << endl;

  // Create the initial solutionSet
  Solution * newSolution;
  for (int i = 0; i < populationSize; i++) {
//    cout << "Poblacion num. " << i << endl;
    newSolution = new Solution(problem_);
//    cout << "Solution inicializada" << endl;
    problem_->evaluate(newSolution);
//    cout << "Solution evaluada" << endl;
    problem_->evaluateConstraints(newSolution);
//    cout << "Solution constantes evaluadas" << endl;
    evaluations++;
    population->add(newSolution);
//    cout << "Solution añadida a la poblacion" << endl;
  } //for

  cout << "NSGAII: Poblacion inicializada con size = " << population->size() << endl;

  cout << "NSGAII: Maximo de evaluaciones: " << maxEvaluations << endl;

  // Generations
  while (evaluations < maxEvaluations) {

    cout << "NSGAII: Eval n. " << evaluations << endl;

    // Create the offSpring solutionSet
    offspringPopulation = new SolutionSet(populationSize);
    Solution ** parents = new Solution*[2];

//    cout << "NSGAII: Comenzamos a operar..." << endl;

    for (int i = 0; i < (populationSize / 2); i++) {
      if (evaluations < maxEvaluations) {
        //obtain parents
        parents[0] = (Solution *) (selectionOperator->execute(population));
        parents[1] = (Solution *) (selectionOperator->execute(population));
//        cout << "NSGAII: AggregativeValue de parents[0] = " << parents[0]->getAggregativeValue() << endl;
//        cout << "NSGAII: AggregativeValue de parents[1] = " << parents[1]->getAggregativeValue() << endl;
//        cout << "Ya tenemos los padres..." << endl;
        Solution ** offSpring = (Solution **) (crossoverOperator->execute(parents));
//        cout << "Hallado offspring..." << endl;
        mutationOperator->execute(offSpring[0]);
        mutationOperator->execute(offSpring[1]);
//        cout << "Ejecutada mutacion..." << endl;
        problem_->evaluate(offSpring[0]);
        problem_->evaluateConstraints(offSpring[0]);
        problem_->evaluate(offSpring[1]);
        problem_->evaluateConstraints(offSpring[1]);
        offspringPopulation->add(offSpring[0]);
        offspringPopulation->add(offSpring[1]);
        evaluations += 2;
        delete[] offSpring;
      } // if
    } // for

    delete[] parents;

//    cout << "NSGAII: Eval2 n. " << evaluations << endl;
//    cout << "NSGAII: Poblacion con size = " << population->size() << endl;
//    cout << "NSGAII: offspringPopulation con size = " << offspringPopulation->size() << endl;

    // Create the solutionSet union of solutionSet and offSpring
    unionSolution = population->join(offspringPopulation);
    delete offspringPopulation;

//    cout << "NSGAII: unionSolution con size = " << unionSolution->size() << endl;
//    cout << "NSGAII: Ejecutada unión..." << endl;

    // Ranking the union
    Ranking * ranking = new Ranking(unionSolution);

//    cout << "NSGAII: Inicializado ranking con tamaño = " << ranking->getNumberOfSubfronts() << endl;

    int remain = populationSize;
    int index = 0;
    SolutionSet * front = NULL;
    for (int i=0;i<population->size();i++) {
      delete population->get(i);
    }
    population->clear();

    // Obtain the next front
    front = ranking->getSubfront(index);

//    cout << "NSGAII: Obtenido frente de pareto con tamaño " << front->size() << endl;
//    cout << "NSGAII: remain = " << remain << endl;

    while ((remain > 0) && (remain >= front->size())) {
      //Assign crowding distance to individuals
      distance->crowdingDistanceAssignment(front, problem_->getNumberOfObjectives());

//      cout << "NSGAII: distance calculada... " << endl;

      //Add the individuals of this front
      for (int k = 0; k < front->size(); k++) {
        population->add(new Solution(front->get(k)));
//        cout << "NSGAII: Añadido frente(" << k << ") a la poblacion con tamaño " << population->size() << endl;
      } // for

      //Decrement remain
      remain = remain - front->size();

//      cout << "NSGAII: remain = " << remain << endl;

      //Obtain the next front
      index++;
      if (remain > 0) {
//        cout << "NSGAII: index = " << index << endl;
        front = ranking->getSubfront(index);
//        cout << "NSGAII: Obtenido frente de pareto con tamaño " << front->size() << endl;
      } // if
    } // while

    // Remain is less than front(index).size, insert only the best one
    if (remain > 0) {  // front contains individuals to insert
      distance->crowdingDistanceAssignment(front, problem_->getNumberOfObjectives());
      Comparator * c = new CrowdingComparator();
      front->sort(c);
      delete c;
      for (int k = 0; k < remain; k++) {
        population->add(new Solution(front->get(k)));
      } // for

      remain = 0;
    } // if

    delete ranking;
    delete unionSolution;

    // This piece of code shows how to use the indicator object into the code
    // of NSGA-II. In particular, it finds the number of evaluations required
    // by the algorithm to obtain a Pareto front with a hypervolume higher
    // than the hypervolume of the true Pareto front.
// TODO:
//    if ((indicators != NULL) &&
//      (requiredEvaluations == 0)) {
//      double HV = indicators.getHypervolume(population);
//      if (HV >= (0.98 * indicators.getTrueParetoFrontHypervolume())) {
//        requiredEvaluations = evaluations;
//      } // if
//    } // if

  } // while

  delete distance;

  // Return as output parameter the required evaluations
  // TODO:
  //setOutputParameter("evaluations", requiredEvaluations);

  // Return the first non-dominated front
  Ranking * ranking = new Ranking(population);
  SolutionSet * result = new SolutionSet(ranking->getSubfront(0)->size());
  for (int i=0;i<ranking->getSubfront(0)->size();i++) {
    result->add(new Solution(ranking->getSubfront(0)->get(i)));
  }
  delete ranking;
  delete population;

  return result;

} // execute
