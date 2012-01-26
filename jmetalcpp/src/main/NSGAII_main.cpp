/**
 * @file NSGAII_main.cpp
 * @author Esteban López
 * @date 02 December 2011
**/


#include <Problem.h>
#include <Solution.h>
#include <Kursawe.h>
#include <ZDT1.h>
#include <ZDT2.h>
#include <ZDT3.h>
#include <ZDT4.h>
#include <ZDT6.h>
#include <DTLZ1.h>
#include <DTLZ2.h>
#include <DTLZ3.h>
#include <DTLZ4.h>
#include <Fonseca.h>
#include <Schaffer.h>
#include <RealSolutionType.h>
#include <SBXCrossover.h>
#include <PolynomialMutation.h>
#include <BinaryTournament2.h>
#include <iostream>
#include <NSGAII.h>
#include <time.h>


/**
 * Class implementing the NSGA-II algorithm.
 * This implementation of NSGA-II makes use of a QualityIndicator object
 *  to obtained the convergence speed of the algorithm. This version is used
 *  in the paper:
 *     A.J. Nebro, J.J. Durillo, C.A. Coello Coello, F. Luna, E. Alba
 *     "A Study of Convergence Speed in Multi-Objective Metaheuristics."
 *     To be presented in: PPSN'08. Dortmund. September 2008.
 *
 *   Besides the classic NSGA-II, a steady-state version (ssNSGAII) is also
 *   included (See: J.J. Durillo, A.J. Nebro, F. Luna and E. Alba
 *                  "On the Effect of the Steady-State Selection Scheme in
 *                  Multi-Objective Genetic Algorithms"
 *                  5th International Conference, EMO 2009, pp: 183-197.
 *                  April 2009)
 */
int main(int argc, char ** argv) {

	clock_t t_ini, t_fin;

  Problem   * problem   ; // The problem to solve
  Algorithm * algorithm ; // The algorithm to use
  Operator  * crossover ; // Crossover operator
  Operator  * mutation  ; // Mutation operator
  Operator  * selection ; // Selection operator

	//problem = new ZDT6("Real");
	//problem = new DTLZ1("Real", 7, 2);
//	problem = new DTLZ1("Real");
	//problem = new DTLZ3("Real", 12, 2);
	//problem = new DTLZ4("Real", 12, 2);

	//problem   = new Schaffer("Real");
	//problem   = new ZDT1("Real", 30);
	problem = new Kursawe("Real");
	cout << "El numero de objetivos es " << problem->getNumberOfObjectives() << endl;

	//HashMap  parameters ; // Operator parameters

	//QualityIndicator indicators ; // Object to get quality indicators
	//indicators = null ;

	algorithm = new NSGAII(problem);
	//algorithm = new ssNSGAII(problem);

	cout << "Algoritmo NGSAII inicializado." << endl;

	// Algorithm parameters
	int populationSizeValue = 100;
	int maxEvaluationsValue = 25000;
	algorithm->setInputParameter("populationSize",&populationSizeValue);
	algorithm->setInputParameter("maxEvaluations",&maxEvaluationsValue);

	// Mutation and Crossover for Real codification
	map<string, void *> parameters;
	double probabilityValue1 = 0.9;
	double distributionIndexValue1 = 20.0;
	parameters["probability"] =  &probabilityValue1;
	parameters["distributionIndex"] = &distributionIndexValue1;
	crossover = new SBXCrossover(parameters);

	parameters.clear();
	double probabilityValue2 = 1.0/problem->getNumberOfVariables();
	double distributionIndexValue2 = 20.0;
	parameters["probability"] = &probabilityValue2;
	parameters["distributionIndex"] = &distributionIndexValue2;
	mutation = new PolynomialMutation(parameters);

	// Selection Operator
	parameters.clear();
	selection = new BinaryTournament2(parameters) ;

	cout << "Adding operators..." << endl;

	// Add the operators to the algorithm
	algorithm->addOperator("crossover",crossover);
	algorithm->addOperator("mutation",mutation);
	algorithm->addOperator("selection",selection);

	// Checking parameters
	cout << "SBXCrossover:" << endl;
	cout << *(double *) algorithm->getOperator("crossover")->getParameter("probability") << endl;
	cout << *(double *) algorithm->getOperator("crossover")->getParameter("distributionIndex") << endl;
	cout << "PolynomialMutation:" << endl;
	cout << *(double *) algorithm->getOperator("mutation")->getParameter("probability") << endl;
	cout << *(double *) algorithm->getOperator("mutation")->getParameter("distributionIndex") << endl;
	cout << "BinaryTournament2:" << endl;
	//cout << algorithm->getOperator("selection")->getParameter("probability") << endl;
	//cout << algorithm->getOperator("selection")->getParameter("distributionIndex") << endl;

	// Add the indicator object to the algorithm
	//algorithm->setInputParameter("indicators", indicators) ;

	// Execute the Algorithm

	t_ini = clock();
	SolutionSet * population = algorithm->execute();
	t_fin = clock();
	double secs = (double) (t_fin - t_ini);

	// Result messages
	cout << "Total execution time: " << secs << "s" << endl;
	cout << "Variables values have been writen to file VAR" << endl;
	population->printVariablesToFile("VAR");
	cout << "Objectives values have been writen to file FUN" << endl;
	population->printObjectivesToFile("FUN");

	delete selection;
	delete mutation;
	delete crossover;
	delete population;
	delete algorithm;

//	if (indicators != null) {
//		logger_.info("Quality indicators") ;
//		logger_.info("Hypervolume: " + indicators.getHypervolume(population)) ;
//		logger_.info("GD         : " + indicators.getGD(population)) ;
//		logger_.info("IGD        : " + indicators.getIGD(population)) ;
//		logger_.info("Spread     : " + indicators.getSpread(population)) ;
//		logger_.info("Epsilon    : " + indicators.getEpsilon(population)) ;
//
//		int evaluations = ((Integer)algorithm.getOutputParameter("evaluations")).intValue();
//		logger_.info("Speed      : " + evaluations + " evaluations") ;
//	} // if
	//cout << "El primer objetivo es: " << solution->getObjective(0) << " el segundo objetivo es: " << solution->getObjective(1) << endl;
	
} // main
