/**
 * @file BinaryReal.h
 * @author Esteban López
 * @version 1.0
 * @date 30 November 2011
 */


#ifndef Binary_Real_h
#define Binary_Real_h

#include <Variable.h>
#include <Binary.h>
#include <PseudoRandom.h>
#include <math.h>

/**
 * This class extends the Binary class to represent a Real variable encoded by
 * a binary string
 */
class BinaryReal : public Binary {

public:

  static const int DEFAULT_PRECISION;

  BinaryReal();
  BinaryReal(int numberOfBits, double lowerBound, double upperBound);
  BinaryReal(BinaryReal * variable);

  void decode();
  double getValue();
  void setValue(double value);
  Variable * deepCopy();
  double getLowerBound();
  double getUpperBound();
  void setLowerBound(double bound);
  void setUpperBound(double bound);
  string toString();

private:
    double value_;
    double lowerBound_ ;
    double upperBound_ ;
    
}; // BinaryReal

#endif
