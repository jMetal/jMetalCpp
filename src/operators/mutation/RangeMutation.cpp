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
	for (int var = 0; var < solution->getNumberOfVariables(); ++var)
	{
		if (PseudoRandom::randDouble() < probability)
		{
			double rand = PseudoRandom::randDouble();
			double tmp = (rand - 0.5) * perturbation_;

			tmp += x->getValue(var);
			if (tmp < x->getLowerBound(var))
			{
				tmp = x->getLowerBound(var);
			}
			else if (tmp > x->getUpperBound(var))
			{
				tmp = x->getUpperBound(var);
			}
			x->setValue(var, tmp);
		} // if
	} // for

	delete x;
}

void * RangeMutation::execute(void *)
{
	return nullptr;
}
