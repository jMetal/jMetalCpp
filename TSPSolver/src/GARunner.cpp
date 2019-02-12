/*
 * GARunner.cpp
 *
 *  Created on: 5 Nov 2018
 *      Author: Emad Alharbi
 */

#include "GARunner.h"
#include <clipper/clipper-ccp4.h>
//namespace GARunner {

GARunner::GARunner(Problem * probelm , int population , int Evaluations , double crossoverProbability, double distributionIndexValue1 , double mutationProbability, double distributionIndexValue2, std::string crossovertype, std::string mutationtype , std::string selectiontype) {
	// TODO Auto-generated constructor stub
	std::cout << "GARunner "<<std::endl;
	ProbelmToSolve=probelm;
	algorithm = new gGA(ProbelmToSolve);

	ProbelmToSolve=probelm;
	populationSizeValue=population;
	maxEvaluationsValue=Evaluations;

	map<string, void *> parameters;

	 parameters["probability"] =  &crossoverProbability ;
	 parameters["distributionIndex"] = &distributionIndexValue1 ;
	 std::cout << crossover << std::endl;
	 crossover=  crossoverType(crossovertype,parameters);
	 std::cout << crossover << std::endl;
	 parameters.clear();

	 parameters["probability"] = &mutationProbability;
	 parameters["distributionIndex"] = &distributionIndexValue2 ;
	 mutation= mutationType(mutationtype,parameters);

	 parameters.clear();


	// selection = new BinaryTournament2(parameters);

	 selection= selectionType(selectiontype,parameters);

	 std::cout << " populationSizeValue " << populationSizeValue << std::endl;
	 std::cout << " maxEvaluationsValue " << maxEvaluationsValue << std::endl;

}

Operator * GARunner::crossoverType(std::string type , map<string, void *> parameters){

	if(type=="SBXCrossover"){
		//std::cout << type <<std::endl;
	return  new SBXCrossover(parameters);
	}
	if(type=="DifferentialEvolutionCrossover"){
		//std::cout << type <<std::endl;
		return new DifferentialEvolutionCrossover(parameters);
	}
	if(type=="HUXCrossover"){
		//std::cout << type <<std::endl;
		return new HUXCrossover(parameters);
	}
	if(type=="SinglePointCrossover"){
		//std::cout << type <<std::endl;
		return new SinglePointCrossover(parameters);
	}

	if(type=="PositionBasedCrossover"){
			//std::cout << type <<std::endl;
			return new PositionBasedCrossover(parameters);
		}

	if(type=="OrderCrossover"){
				//std::cout << type <<std::endl;
				return new OrderCrossover(parameters);
			}

	return new SBXCrossover(parameters); // Default
}

Operator * GARunner::mutationType(std::string type , map<string, void *> parameters){

	if(type=="BitFlipMutation"){
		//std::cout << type <<std::endl;
	return  new BitFlipMutation(parameters);
	}
	if(type=="NonUniformMutation"){
		//std::cout << type <<std::endl;
		return new NonUniformMutation(parameters);
	}
	if(type=="PolynomialMutation"){
		//std::cout << type <<std::endl;
		return new PolynomialMutation(parameters);
	}
	if(type=="UniformMutation"){
		//std::cout << type <<std::endl;
		return new UniformMutation(parameters);
	}

	if(type=="InsertionMutation"){
			//std::cout << type <<std::endl;
			return new InsertionMutation(parameters);
		}

	if(type=="InversionMutation"){
		//std::cout << type <<std::endl;
		return new InversionMutation(parameters);
	}

	return new BitFlipMutation(parameters); // Default
}

Operator * GARunner::selectionType(std::string type , map<string, void *> parameters){

	if(type=="BestSolutionSelection"){
		//std::cout << type <<std::endl;
	return  new BestSolutionSelection(parameters);
	}
	if(type=="BinaryTournament"){
		//std::cout << type <<std::endl;
		return new BinaryTournament(parameters);
	}
	if(type=="BinaryTournament2"){
		//std::cout << type <<std::endl;
		return new BinaryTournament2(parameters);
	}
	if(type=="DifferentialEvolutionSelection"){
		//std::cout << type <<std::endl;
		return new DifferentialEvolutionSelection(parameters);
	}
	if(type=="RandomSelection"){
		//std::cout << type <<std::endl;
		return new RandomSelection(parameters);
	}
	if(type=="WorstSolutionSelection"){
		//std::cout << type <<std::endl;
		return new WorstSolutionSelection(parameters);
	}

	return new BinaryTournament(parameters); // Default
}

SolutionSet * GARunner::RealNumbers(){

	//Problem   * problem   ; // The problem to solve
	//Algorithm * algorithm ; // The algorithm to use
	//Operator  * crossover ; // Crossover operator
	//Operator  * mutation  ; // Mutation operator
	//Operator  * selection ; // Selection operator
	//problem=ProbelmToSolve;

	//algorithm = new gGA(ProbelmToSolve);

		// Algorithm parameters
	  //int populationSizeValue = 100;
	  //int maxEvaluationsValue = 250000;
	  algorithm->setInputParameter("populationSize",&populationSizeValue);
	  algorithm->setInputParameter("maxEvaluations",&maxEvaluationsValue);

	  // Mutation and Crossover for Real codification
	 // map<string, void *> parameters;
	  //double crossoverProbability = 0.9;
	 // double distributionIndexValue1 = 20.0;
	 // parameters["probability"] =  &crossoverProbability ;
	 // parameters["distributionIndex"] = &distributionIndexValue1 ;
	 // crossover = new SBXCrossover(parameters);

	  //parameters.clear();
	  //double mutationProbability = 1.0/problem->getNumberOfVariables();
	 // double distributionIndexValue2 = 20.0;
	  //parameters["probability"] = &mutationProbability;
	 // parameters["distributionIndex"] = &distributionIndexValue2 ;
	 // mutation = new PolynomialMutation(parameters);

		// Selection Operator
		//parameters.clear();
		//selection = new BinaryTournament2(parameters) ;

		// Add the operators to the algorithm
		algorithm->addOperator("crossover",crossover);
		algorithm->addOperator("mutation",mutation);
		algorithm->addOperator("selection",selection);

		// Add the indicator object to the algorithm
		//algorithm->setInputParameter("indicators", indicators) ;


		std::cout << " algorithm->execute "<<std::endl;
		SolutionSet * population = algorithm->execute();


		// Result messages


	  return population;
	  delete crossover;
	  delete mutation;
	  delete selection;
	  delete population;
	  delete algorithm;

}
SolutionSet * GARunner::Binary(){
	   //JMetal GA
	         clock_t t_ini, t_fin;

	         //  Problem   * problem   ; // The problem to solve
	         //  Algorithm * algorithm ; // The algorithm to use

	         //  Operator  * crossover ; // Crossover operator
	         //  Operator  * mutation  ; // Mutation operator
	         //  Operator  * selection ; // Selection operator

	         //  problem=ProbelmToSolve;
	       	std::cout << "Set Problem   "<<std::endl;
	        //   algorithm = new gGA(problem);
	       	std::cout << "The Problem has been set   "<<std::endl;
	           	// Algorithm parameters
	           	//int populationSize = 100;
	           	//int maxEvaluations = 100;
	           	algorithm->setInputParameter("populationSize",&populationSizeValue);
	           	algorithm->setInputParameter("maxEvaluations",&maxEvaluationsValue);

	          // 	map<string, void *> parameters;
	        	std::cout << "hereee   "<<std::endl;
	           	// Mutation operator
	          // 	parameters.clear();
	          // 	double mutationProbability = 1.0/problem->getNumberOfBits();
	         //  	parameters["probability"] = &mutationProbability;
	         //  	mutation = new BitFlipMutation(parameters);
	           	std::cout << "hereee2   "<<std::endl;
	           	// Crossover operator
	          // 	parameters.clear();
	          // 	double crossoverProbability = 0.9;
	          // 	parameters["probability"] = &crossoverProbability;
	          // 	crossover = new SinglePointCrossover(parameters);

	           	// Selection Operator
	           	//parameters.clear();
	           //	selection = new BinaryTournament2(parameters) ;

	           	// Add the operators to the algorithm

	           	algorithm->addOperator("crossover",crossover);
	           	algorithm->addOperator("mutation",mutation);
	           	algorithm->addOperator("selection",selection);

	           	std::cout << "Executing GA  "<<std::endl;

	           	// Execute the Algorithm
	           	t_ini = clock();
	           	SolutionSet * population = algorithm->execute();
	           	t_fin = clock();
	           	double secs = (double) (t_fin - t_ini);
	           	secs = secs / CLOCKS_PER_SEC;

	           	// Result messages
	          // 	cout << "Total execution time: " << secs << "s" << endl;
	           	//cout << "Variables values have been written to file VAR" << endl;
	          // 	population->printVariablesToFile()
	          // 	cout << "Objectives values have been written to file FUN" << endl;
	           //	population->printObjectives();


	          //  Binary * variable ;

return population;

	           	  // variable = (Binary *)(population->get(0)->getDecisionVariables()[0]) ;
}

GARunner::~GARunner() {
	// TODO Auto-generated destructor stub
}

//} /* namespace Balls */
