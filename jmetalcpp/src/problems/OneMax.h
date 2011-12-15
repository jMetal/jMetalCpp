/*
 * OneMax.h
 *
 *  Created on: 12/12/2011
 *      Author: antonio
 */

#ifndef __ONEMAX_H__
#define __ONEMAX_H__

#include <Problem.h>
#include <BinarySolutionType.h>
#include <Solution.h>

class OneMax : public Problem {
public:
	OneMax(int numberOfBits, int numberOfStrings = 1);
  void evaluate(Solution *solution);

	virtual ~OneMax();
};

#endif /* __ONEMAX_H__ */
