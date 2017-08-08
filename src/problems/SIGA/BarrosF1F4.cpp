#include "BarrosF1F4.h"

BarrosF1F4::BarrosF1F4(string solutionType, int numberOfVariables, int numberOfObjectives)
{
	numberOfVariables_ = numberOfVariables;
	numberOfObjectives_ = numberOfObjectives;
	numberOfConstraints_ = 0;
	problemName_ = "BarrosF1_F3";

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

void BarrosF1F4::evaluate(Solution * solution)
{
	XReal * vars = snew XReal(solution);
	double x1 = vars->getValue(0);
	double x2 = vars->getValue(1);
	delete vars;
	double f1 = x1;
	double gmin = 1.0;
	double gmax = 2.0;
	double xmin = 0.0;
	double xmax = 1.0;
	double num = x2 - xmin;
	double den = xmax - xmin;
	double g = gmin + (gmax - gmin) * pow(num / den, 0.25);
	double f4 = 1 - pow(x1 / g, 2);
	solution->setObjective(0, f1);
	solution->setObjective(1, f4);
}

BarrosF1F4::~BarrosF1F4()
{
	delete[] lowerLimit_;
	delete[] upperLimit_;
	delete solutionType_;
}
