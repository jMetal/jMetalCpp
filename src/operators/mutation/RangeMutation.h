//  UniformMutation.h
//
//  Author:
//       Sérgio Vieira <sergiosvieira@gmail.com>
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

#ifndef __RANGE_MUTATION__
#define __RANGE_MUTATION__

#include <Mutation.h>
#include <Solution.h>
#include <PseudoRandom.h>
#include <XReal.h>

/**
* This class implements a uniform mutation operator.
*/
class RangeMutation : public Mutation
{
protected:
	/**
	* Stores the value used in a range mutation operator.
	*/
	double perturbation_ = 0.0;
	double mutationProbability_ = 0.0;
	MatrixOfShort zoneIndex_;
	/**
	* Performs the operation.
	* @param probability Mutation probability
	* @param solution The solution to mutate
	* @throws JMException
	*/
	void doMutation(double probability, Solution *solution);
public:
	/**
	* Constructor.
	* Creates a new range mutation operator instance.
	*/
	RangeMutation(MapOfStringFunct parameters);

	/**
	* Executes the operation
	* @param object An object containing the solution to mutate
	*/
	void *execute(void *);

}; // Range Mutation

#endif
