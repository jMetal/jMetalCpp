//#include "BarrosF1_F3.h"
#include "problems/SIGA/BarrosF1F3.h"

BarrosF1F3::BarrosF1F3(string solutionType, int numberOfVariables, int numberOfObjectives)
{
	numberOfVariables_ = numberOfVariables;
	numberOfObjectives_ = numberOfObjectives;
	numberOfConstraints_ = 0;
	problemName_ = "BarrosF1F3";

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

void BarrosF1F3::evaluate(Solution * solution)
{
	XReal * vars = snew XReal(solution);
	double x1 = vars->getValue(0);
	double x2 = vars->getValue(1);
	delete vars;
	double f1 = x1;
	double a = std::exp(-pow ( (x2 - 0.2) / 0.004, 2.0));
	double b = std::exp(-pow ( (x2 - 0.6) / 0.4, 2.0));
	double f3 = (2.0 - a - 0.8 * b) / x1;
	solution->setObjective(0, f1);
	solution->setObjective(1, f3);
}

BarrosF1F3::~BarrosF1F3()
{
	delete[] lowerLimit_;
	delete[] upperLimit_;
	delete solutionType_;
}
