/*
 * Optimizer.h
 *
 *  Created on: 12 Feb 2019
 *      Author: Emad Alharbi
 */

#ifndef OPTIMIZER_H_
#define OPTIMIZER_H_
#include <iostream>
#include <vector>
struct MetalBall {

   std::string MetalBallValue;
   std::string MetalBallType;

};
class Optimizer {
public:
	Optimizer();
	virtual ~Optimizer();
	std::vector<MetalBall> MBalls;
	void AddMBall( std::string MetalBallType,std::string MetalBallValue);
	std::vector<MetalBall> CreateBasket();
	void Optimize(int NumberOfBasket, int NumberOfIterations);
	std::vector<std::vector<MetalBall> > RandomBaskets(int NumberOfBasket);
	std::string FindParameter (std::vector<MetalBall> Basket, std::string Parameter);
};

#endif /* OPTIMIZER_H_ */
