//  LZ09_F3.cpp
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
//
//  Copyright (c) 2011 Antonio J. Nebro
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

#include <LZ09_F3.h>

/**
 * Constructor
 */
LZ09_F3::LZ09_F3(string solutionType, int ptype, int dtype, int ltype) {
  numberOfVariables_  = 30;
  numberOfObjectives_ = 2;
  numberOfConstraints_= 0;
  problemName_        = "LZ09_F3";

	 LZ09_  = new LZ09(numberOfVariables_,
			               numberOfObjectives_,
			               ptype,
			               dtype,
			               ltype) ;

		lowerLimit_ = new double[numberOfVariables_];
		if (lowerLimit_ == NULL) {
			cout << "LZ09_F3::LZ09_F3: Error reserving memory for storing the "
					<< "variable lower limits" << endl;
			exit(-1);
		}

		upperLimit_ = new double[numberOfVariables_];
		if (upperLimit_ == NULL) {
			cout << "LZ09_F3::LZ09_F3: Error reserving  memory for storing the "
					<< "variable lower limits" << endl;
			exit(-1);
		}

		lowerLimit_[0] = 0.0;
		upperLimit_[0] = 1.0;
		for (int i = 1; i < numberOfVariables_; i++) {
			lowerLimit_[i] = -1.0;
			upperLimit_[i] = 1.0;
		}

		if (solutionType.compare("BinaryReal") == 0)
			solutionType_ = new BinaryRealSolutionType(this) ;
		else if (solutionType.compare("Real") == 0) {
			solutionType_ = new RealSolutionType(this) ;
		}
		else if (solutionType.compare("ArrayReal") == 0)
			solutionType_ = new ArrayRealSolutionType(this) ;
		else {
			cout << "LZ09_F3::LZ09_F3: solution type " << solutionType << " invalid" << endl;
			exit(-1) ;
		}

      fx_ = new double[numberOfObjectives_] ;
      x_ = new double[numberOfVariables_];
} // LZ09_F3::LZ09_F3

/**
 * Destructor
 */
LZ09_F3::~LZ09_F3 () {
  delete [] lowerLimit_ ;
  delete [] upperLimit_ ;
  delete solutionType_ ;
  delete LZ09_ ;
}

void LZ09_F3::evaluate(Solution * solution) {
  XReal * vars = new XReal(solution);

  vector<double> * x = new vector<double>(numberOfVariables_) ;
  vector<double> * y = new vector<double>(numberOfObjectives_);

  for (int i = 0; i < numberOfVariables_; i++) {
  	x->at(i) = vars->getValue(i);
  } // for
  for (int i = 0; i < numberOfObjectives_; i++) {
    y->at(i) = 0.0 ;
  } // for

  LZ09_->objective(x, y) ;

  for (int i = 0; i < numberOfObjectives_; i++)
    solution->setObjective(i, y->at(i));
  
  delete x;
  delete y;
  delete vars;
}
