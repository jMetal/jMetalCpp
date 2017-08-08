//  BarrosF5F3.cpp
//
//  Authors:
//	Sérgio Vieira <sergiosvieira@gmail.com>
//
//  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "problems/SIGA/BarrosF5F3.h"

/**
 * Class constructor
 */
BarrosF5F3::BarrosF5F3(std::string solutionType)
{
    numberOfVariables_   = 2;
    numberOfObjectives_  = 2;
    numberOfConstraints_ = 0;
    problemName_         = "BarrosF5F3";

    lowerLimit_ = snew double[numberOfVariables_];
    if (lowerLimit_ == nullptr)
    {
        std::cout << "BarrosF5F3::BarrosF5F3. Error reserving memory for storing the array of lower limits" << std::endl;
    } // if

    upperLimit_ = snew double[numberOfVariables_];
    if (upperLimit_ == nullptr)
    {
        std::cout << "BarrosF5F3::BarrosF5F3. Error reserving memory for storing the array of upper limits" << std::endl;
        exit(-1) ;
    } // if

    for (int i = 0; i < numberOfVariables_; i++)
    {
        lowerLimit_[i] = -10.0;
        upperLimit_[i] =  20.0;
    } // for

    if (solutionType.compare("BinaryReal") == 0)
    {
        //std::cout << "Selected solution type: BinaryReal" << std::endl;
        solutionType_ = snew BinaryRealSolutionType(this) ;
    }
    else if (solutionType.compare("Real") == 0)
    {
        solutionType_ = snew RealSolutionType(this) ;
        //std::cout << "Selected solution type: Real" << std::endl;
    }
    else if (solutionType.compare("ArrayReal") == 0)
    {
        solutionType_ = snew ArrayRealSolutionType(this) ;
    }
    else
    {
        std::cout << "Error: solution type " << solutionType << " invalid" << std::endl;
        exit(-1) ;
    }
} // BarrosF5F3


/**
 * Destructor
 */
BarrosF5F3::~BarrosF5F3()
{
    delete [] lowerLimit_ ;
    delete [] upperLimit_ ;
    delete solutionType_ ;
} // ~BarrosF5F3


/**
  * Evaluates a solution
  */
void BarrosF5F3::evaluate(Solution *solution)
{
	VectorOfDouble fx(numberOfObjectives_);
	VectorOfDouble x(numberOfVariables_);
	Variable **variables = solution->getDecisionVariables();
	for (int i = 0; i < numberOfVariables_; i++)
	{
		x[i] = variables[i]->getValue();
	}
	double alpha = 2.0;
	double q = 4.0;
	double value1 = 1.0 + 10.0 * x[1];
	double value2 = x[0] / value1;
	double value3 = 1.0 - pow(value2, alpha);
	double value4 = -(value2 * sin(2.0 * PI * q * x[0]));
	double value5 = value3 - value4;
	fx[0] = value1 * value5;
	double a = std::exp(-pow((x[1] - 0.2) / 0.004, 2.0));
	double b = std::exp(-pow((x[1] - 0.6) / 0.4, 2.0));
	fx[1] = (2.0 - a - 0.8 * b) / x[0];
	solution->setObjective(0, fx[0]);
	solution->setObjective(1, fx[1]);

} // evaluate

