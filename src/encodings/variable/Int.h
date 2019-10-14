/*
 * InsertionMutation.h
 *
 *  Created on: 9 Feb 2019
 *      Author: Emad Alharbi
 *      University of York,UK
 */
#ifndef Int_h
#define Int_h

#include "Variable.h"
#include "PseudoRandom.h"
#include <sstream>

/**
 * This class implements a Int value decision variable
 */
class Int : public Variable {

public:

	Int();
	Int(double lowerBound, double upperBound);
	Int(Variable * variable);
  ~Int();

  double getValue();
  void setValue(double value);
  Variable * deepCopy();
  double getLowerBound();
  double getUpperBound();
  void setLowerBound(double bound);
  void setUpperBound(double bound);
  string toString() ;

private:
  double value_;
  double lowerBound_ ;
  double upperBound_ ;
};

#endif
