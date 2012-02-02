/*
 * PAES_main.cpp
 *
 *  Created on: 25/01/2012
 *      Author: Cristian
 */

#include <Problem.h>
#include <Algorithm.h>
#include <Operator.h>
#include <Solution.h>
#include <Kursawe.h>
#include <DTLZ1.h>
#include <Fonseca.h>
#include <RealSolutionType.h>
#include <PolynomialMutation.h>
#include <iostream>
#include <paes.h>
#include <time.h>

int main() {

	clock_t t_ini, t_fin;
	Problem   * problem   ; // The problem to solve
	Algorithm * algorithm ; // The algorithm to use
    Operator  * mutation  ; // Mutation operator

    //problem = new Kursawe("Real", 3);
    //problem = new ZDT6("Real");
	problem = new DTLZ1("Real", 7, 2);
	//problem = new DTLZ1("Real");
	//problem = new DTLZ3("Real", 12, 2);
	//problem = new DTLZ4("Real", 12, 2);
    //cout << "El número de objetivos es " << problem->getNumberOfObjectives() << endl;

    //QualityIndicator indicators ; // Object to get quality indicators

    algorithm = new paes(problem);


// Algorithm parameters
	int archiveSizeValue = 100;
	int *archiveSizePtr = &archiveSizeValue;
	int biSectionsValue = 5;
	int *biSectionsPtr = &biSectionsValue;
	int maxEvaluationsValue = 25000;
	int *maxEvaluationsPtr = &maxEvaluationsValue;

   algorithm->setInputParameter("archiveSize",archiveSizePtr);
   algorithm->setInputParameter("biSections",biSectionsPtr);
   algorithm->setInputParameter("maxEvaluations",maxEvaluationsPtr);

   // Mutation (Real variables)
   map<string, void *> parameters; // Operator parameters
   parameters.clear();
   double probabilityValue1 = 1.0/problem->getNumberOfVariables();
   double *probabilityPtr1 = &probabilityValue1;
   double distributionIndexValue1 = 20.0;
   double *distributionIndexPtr1 = &distributionIndexValue1;
   parameters["probability"] =  probabilityPtr1 ;
   parameters["distributionIndex"] = distributionIndexPtr1 ;
   mutation = new PolynomialMutation(parameters);

   // Mutation (BinaryReal variables)
   //mutation = MutationFactory.getMutationOperator("BitFlipMutation");
   //mutation.setParameter("probability",0.1);

   algorithm->addOperator("mutation",mutation);

   // Checking parameters
   //cout << "PolynomialMutation:" << endl;
   //cout << *(double *) algorithm->getOperator("mutation")->getParameter("probability") << endl;
   //cout << *(double *) algorithm->getOperator("mutation")->getParameter("distributionIndex") << endl;


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


 /*
  if (indicators != null) {
	logger_.info("Quality indicators") ;
	logger_.info("Hypervolume: " + indicators.getHypervolume(population)) ;
	logger_.info("GD         : " + indicators.getGD(population)) ;
	logger_.info("IGD        : " + indicators.getIGD(population)) ;
	logger_.info("Spread     : " + indicators.getSpread(population)) ;
	logger_.info("Epsilon    : " + indicators.getEpsilon(population)) ;
  } // if
  */


  // return 10;
} // main




