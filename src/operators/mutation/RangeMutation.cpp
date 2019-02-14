#include "RangeMutation.h"

RangeMutation::RangeMutation(MapOfStringFunct parameters): Mutation(parameters)
{
	if (parameters["probability"] != nullptr)
	{
		mutationProbability_ = *(double *)parameters["probability"];
	}
	if (parameters["perturbation"] != nullptr)
	{
		perturbation_ = *(double *)parameters["perturbation"];
	}
	if (parameters["zone_index"] != nullptr)
	{
		zoneIndex_ = *(MatrixOfShort *)parameters["zone_index"];
	}
}

void RangeMutation::doMutation(double probability, Solution * solution)
{
	XReal * x = new XReal(solution);
	for (auto row : zoneIndex_)
	{
		for (auto col: row)
		{
			if (PseudoRandom::randDouble() < probability)
			{
				double tmp = doPertubation(x, col);
				x->setValue(col, tmp);
			}
		}
	}
	delete x;
}

double RangeMutation::doPertubation(XReal* array, short col)
{
	double rand = PseudoRandom::randDouble();
	double tmp = (rand - 0.5) * perturbation_;
	tmp += array->getValue(col);
	double minMaxRange = ((array->getUpperBound(col) - array->getLowerBound(col)) / 2.0);
	if (tmp < array->getLowerBound(col))
	{
		//tmp = array->getLowerBound(col);
		tmp = array->getLowerBound(col) + minMaxRange;
		if (perturbation_ > 0.0 
			&& perturbation_ < 1.0) 
		{
			double prand = PseudoRandom::randDouble() * perturbation_;
			tmp = array->getLowerBound(col) + minMaxRange * prand;
		}
	}
	else if (tmp > array->getUpperBound(col))
	{
		//tmp = array->getUpperBound(col);
		tmp = array->getUpperBound(col) - minMaxRange;
		if (perturbation_ > 0.0
			&& perturbation_ < 1.0)
		{
			double prand = PseudoRandom::randDouble() * perturbation_;
			tmp = array->getUpperBound(col) - minMaxRange * prand;
		}
	}
	return tmp;
}

void * RangeMutation::execute(void * object)
{
	Solution *solution = (Solution *)object;
	doMutation(mutationProbability_, solution);
	return solution;
}
