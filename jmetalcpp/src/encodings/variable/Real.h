/**
 * @file Real.h
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 30 November 2011
 */

#ifndef Real_h
#define Real_h

#include <Variable.h>
#include <PseudoRandom.h>
#include <sstream>

/**
 * This class implements a Real value decision variable
 */
class Real : public Variable {

public:
  Real();
  Real(double lowerBound, double upperBound);
  Real(Variable * variable);
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
