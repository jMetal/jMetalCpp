/**
 * @file ArrayReal.h
 * @author Esteban López
 * @version 1.0
 * @date 30 November 2011
 */


#ifndef Array_Real_h
#define Array_Real_h

#include <Variable.h>
#include <Problem.h>
#include <PseudoRandom.h>

/**
 * Class implementing a decision variable representing an array of real values.
 * The real values of the array have their own bounds.
 */
class ArrayReal : public Variable {

public:

  double * array_;
  Problem * problem_;
  int size_;

  ArrayReal();
  ArrayReal(int size, Problem * problem);
  ArrayReal(ArrayReal * arrayReal);

  Variable * deepCopy();
  int getLength();
  double getValue(int index);
  void setValue(int index, double value);
  double getLowerBound(int index);
  double getUpperBound(int index);
  string toString();

  void setValue(double value);
  double getValue();
  double getLowerBound();
  double getUpperBound();
};

#endif
