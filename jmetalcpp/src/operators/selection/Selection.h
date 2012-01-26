/**
  * @file Selection.h
  * @author Juan J. Durillo
  * @author Antonio J. Nebro
  * @author Esteban López
  * @date 01 December 2011
**/

#ifndef __SELECTION__
#define __SELECTION__

#include <Operator.h>

/**
  * @class Selection
  * @brief This class is aimed at representing a Selection operator
**/
class Selection : public Operator {

public:
	Selection (map<string, void *> parameters);
	virtual ~Selection() = 0;
};

#endif
