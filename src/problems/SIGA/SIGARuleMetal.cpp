#include "SIGARuleMetal.h"

SIGARuleMetal::SIGARuleMetal(std::function<void(Solution*)> callback, string solutionType, int numberOfVariables, int numberOfObjectives)
{
	numberOfVariables_ = numberOfVariables;
	numberOfObjectives_ = numberOfObjectives;
	numberOfConstraints_ = 0;
	callback_ = callback;
	problemName_ = "SIGARule";

	lowerLimit_ = snew double[numberOfVariables_];//(double *)malloc(sizeof(double)*numberOfVariables);
	if (lowerLimit_ == nullptr)
	{
		cout << "Impossible to reserve memory for storing the variable lower limits" << endl;
		exit(-1);
	}

	upperLimit_ = snew double[numberOfVariables_];//(double *)malloc(sizeof(double)*numberOfVariables);
	if (upperLimit_ == nullptr)
	{
		cout << "Impossible to reserve memory for storing the variable lower limits" << endl;
		exit(-1);
	}

	for (int i = 0; i < numberOfVariables_; i++)
	{
		lowerLimit_[i] = 0.0;
		upperLimit_[i] = 1.0;
	}

	if (solutionType.compare("BinaryReal") == 0)
		solutionType_ = snew BinaryRealSolutionType(this);
	else if (solutionType.compare("Real") == 0)
	{
		solutionType_ = snew RealSolutionType(this);
		//cout << "Tipo seleccionado Real" << endl;
	}
	else if (solutionType.compare("ArrayReal") == 0)
		solutionType_ = snew ArrayRealSolutionType(this);
	else
	{
		cout << "Error: solution type " << solutionType << " invalid" << endl;
		exit(-1);
	}
}

void SIGARuleMetal::evaluate(Solution * solution)
{
	callback_(solution);
}

SIGARuleMetal::~SIGARuleMetal()
{
	delete[] lowerLimit_;
	delete[] upperLimit_;
	delete solutionType_;
}
