//  BarrosF1F5.cpp
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

#include "BarrosF1F5.h"

/**
 * Class constructor
 */
BarrosF1F5::BarrosF1F5(std::string solutionType)
{
    numberOfVariables_   = 2;
    numberOfObjectives_  = 2;
    numberOfConstraints_ = 0;
    problemName_         = "BarrosF1F5";

    lowerLimit_ = snew double[numberOfVariables_];
    if (lowerLimit_ == nullptr)
    {
        std::cout << "BarrosF1F5::BarrosF1F5. Error reserving memory for storing the array of lower limits" << std::endl;
    } // if

    upperLimit_ = snew double[numberOfVariables_];
    if (upperLimit_ == nullptr)
    {
        std::cout << "BarrosF1F5::BarrosF1F5. Error reserving memory for storing the array of upper limits" << std::endl;
        exit(-1) ;
    } // if

    for (int i = 0; i < numberOfVariables_; i++)
    {
        lowerLimit_[i] = 0.0;
        upperLimit_[i] = 1.0;
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
} // BarrosF1F5


/**
 * Destructor
 */
BarrosF1F5::~BarrosF1F5()
{
    delete [] lowerLimit_ ;
    delete [] upperLimit_ ;
    delete solutionType_ ;
} // ~BarrosF1F5


/**
  * Evaluates a solution
  */
void BarrosF1F5::evaluate(Solution *solution)
{
	VectorOfDouble fx(numberOfObjectives_);
	VectorOfDouble x(numberOfVariables_);
    Variable **variables = solution->getDecisionVariables();
    for (int i = 0; i < numberOfVariables_; i++)
    {
        x[i] = variables[i]->getValue() ;
    }
    fx[0] = x[0];
    double alpha = 2.0;
    double q = 4.0;
    double value1 = 1.0 + 10.0 * x[1];
    double value2 = x[0] / value1;
    double value3 = 1.0 - pow(value2, alpha);
	double value4 = -(value2 * sin(2.0 * PI * q * x[0]));
	double value5 = value3 - value4;
    fx[1] = value1 * value5;
    solution->setObjective(0, fx[0]);
    solution->setObjective(1, fx[1]);
} // evaluate

