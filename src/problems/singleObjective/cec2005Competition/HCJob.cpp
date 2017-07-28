//  HCJob.cpp
//
//  Authors:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//       Antonio J. Nebro <antonio@lcc.uma.es>
//
//  Copyright (c) 2014 Antonio J. Nebro
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


#include <HCJob.h>
#include "JMetalHeader.h"

/**
 * Constructor.
 */
HCJob::HCJob(int numFunc)
{
    sigma = snew double[numFunc];
    biases = snew double[numFunc];
    lambda = snew double[numFunc];
} // HCJob

/**
 * Destructor
 */
HCJob::~HCJob()
{
    delete [] sigma;
    delete [] biases;
    delete [] lambda;
}
