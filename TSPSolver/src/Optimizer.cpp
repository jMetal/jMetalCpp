/*
 * Optimizer.cpp
 *
 *  Created on: 12 Feb 2019
 *      Author: Emad Alharbi
 */

#include "Optimizer.h"
#include "GARunner.h"
#include <JMetalInc/PseudoRandom.h>
#include "TSPProblem.h"
#include <string>
#include <map>
#include <cassert>
#include <algorithm>
Optimizer::Optimizer() {
	// TODO Auto-generated constructor stub
	// MBalls = new std::vector<MetalBall>;
}
void Optimizer::AddMBall( std::string MetalBallType,std::string MetalBallValue){
	MetalBall m ;
	m.MetalBallType=MetalBallType;
	m.MetalBallValue=MetalBallValue;
	MBalls.push_back(m);

}
std::vector<MetalBall> Optimizer::CreateBasket(){

	std::vector<std::string> MetalBallsTypes;
	for(int i=0 ;i < MBalls.size(); ++i){

		bool Found=false;
		for(int t=0; t < MetalBallsTypes.size(); ++t){
			if(MBalls[i].MetalBallType==MetalBallsTypes[t]){
				Found=true;
			}
		}
		if(Found==false)
			MetalBallsTypes.push_back(MBalls[i].MetalBallType);
	}

	std::vector<MetalBall> Basket;
	for(int t=0; t < MetalBallsTypes.size(); ++t){
		std::vector<MetalBall> Types;
		for(int i=0;i<MBalls.size(); ++i){
			if(MBalls[i].MetalBallType==MetalBallsTypes[t])
				Types.push_back(MBalls[i]);
		}
		int Random= PseudoRandom::randInt(0,Types.size()-1);
		Basket.push_back(Types[Random]);
		//std::cout << Types[Random].MetalBallType << std::endl;
		//std::cout << Types[Random].MetalBallValue << std::endl;
	}
	return Basket;
}
std::vector<std::vector<MetalBall> > Optimizer::RandomBaskets(int NumberOfBaskets){
	std::vector<std::vector<MetalBall> > Baskets;
	for(int i=0 ;i < NumberOfBaskets ; ++i){
		Baskets.push_back(CreateBasket());
	}
	return Baskets;
}
void Optimizer::Optimize(int NumberOfBasket, int NumberOfIterations){

	TSPProblem *tsp = new TSPProblem();
	 std::map<std::string, int> Repetition;
	for(int I=0 ; I < NumberOfIterations ; ++I){
		std::cout << "Iterations "<<I << std::endl ;
		std::vector<std::vector<MetalBall> > Baskets= RandomBaskets(NumberOfBasket);

		int BestBasketIndex=0;
		double BestFitness=-1;
		for(int b=0 ; b < NumberOfBasket ; ++b){
			std::cout << "Basket "<<b << std::endl ;
//std::cout << "Setting GA parameters "<<std::endl;
		    GARunner *GA= new GARunner(tsp,stoi(FindParameter(Baskets[b],"Population")),stoi(FindParameter(Baskets[b],"Evaluation")),stod(FindParameter(Baskets[b],"crossoverProbability")),0,stod(FindParameter(Baskets[b],"mutationProbability")),0,FindParameter(Baskets[b],"Crossover"),FindParameter(Baskets[b],"Mutation"),FindParameter(Baskets[b],"Selection"));
		   // std::cout << "Running GA"<<std::endl;
		    SolutionSet * population = GA->RealNumbers();
		    population->printObjectives();


		    if(BestFitness==-1){
		    	BestFitness=population->get(0)->getObjective(0);
		    	BestBasketIndex=b;
		    }
		    else{
		    	if(population->get(0)->getObjective(0) < BestFitness){
		    		BestFitness=population->get(0)->getObjective(0);
		    	    BestBasketIndex=b;
		    	}
		    }
		}

		for (int Ba=0; Ba<Baskets[BestBasketIndex].size(); ++Ba ){
			std::string Key=Baskets[BestBasketIndex][Ba].MetalBallType;
			Key.append(Baskets[BestBasketIndex][Ba].MetalBallValue);
			if (Repetition.find(Key) != Repetition.end()){

				auto it = std::find_if(std::begin(Repetition), std::end(Repetition), [&](const std::pair<std::string, int> &pair)
				{
				    return pair.first == Key;
				});

				if (it != Repetition.end()) {

				     it->second=it->second+1;

				}
			}
			else{

std::string Key=Baskets[BestBasketIndex][Ba].MetalBallType;
Key.append(Baskets[BestBasketIndex][Ba].MetalBallValue);
				Repetition.insert(std::pair<std::string, int>(Key,1));
			}
		}
	}
	std::cout << "Repetition Table : "  << "\n";
	for(auto R : Repetition)
	{
	   std::cout << R.first << " " << R.second  << "\n";
	}
}

std::string Optimizer::FindParameter (std::vector<MetalBall> Basket, std::string Parameter){

	for(int i=0 ; i < Basket.size();++i){
		if(Basket[i].MetalBallType==Parameter){
			//std::cout << "Parameter "<<Basket[i].MetalBallValue<<std::endl;
			return Basket[i].MetalBallValue;
		}
	}

	return "";
}
Optimizer::~Optimizer() {
	// TODO Auto-generated destructor stub
}

