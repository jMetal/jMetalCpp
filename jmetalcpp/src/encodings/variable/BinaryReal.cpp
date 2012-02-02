/**
 * @file BinaryReal.cpp
 * @author Esteban López
 * @version 1.0
 * @date 30 November 2011
 */

#include <BinaryReal.h>


/**
 * Defines the default number of bits used for binary coded variables.
 */
const int BinaryReal::DEFAULT_PRECISION = 30;


/**
 * Constructor.
 */
BinaryReal::BinaryReal() : Binary() { }


/**
 * Constructor
 * @param numberOfBits Length of the binary string.
 * @param lowerBound The lower limit for the variable
 * @param upperBound The upper limit for the variable.
 */
BinaryReal::BinaryReal(int numberOfBits, double lowerBound, double upperBound)
: Binary(numberOfBits) {
	lowerBound_ = lowerBound;
	upperBound_ = upperBound;
	this->decode();
} //BinaryReal


/**
 * Copy constructor
 * @param variable The variable to copy
 */
BinaryReal::BinaryReal(BinaryReal * variable) : Binary (variable) {
	lowerBound_   = variable->lowerBound_;
	upperBound_   = variable->upperBound_;
	value_ = variable->value_;
} //BinaryReal


/**
 * Decodes the real value encoded in the binary string represented
 * by the <code>BinaryReal</code> object. The decoded value is stores in the
 * <code>value_</code> field and can be accessed by the method
 * <code>getValue</code>.
 */
void BinaryReal::decode(){
	double value = 0.0;
	for (int i = 0; i < numberOfBits_; i++) {
		if ((*bits_)[i] == true) {
			value += pow(2.0,i);
		}
	}
	value_ = value * (upperBound_ - lowerBound_) /
			(pow(2.0,numberOfBits_)-1.0);
	value_ += lowerBound_;
} //decode


/**
 * Returns the double value of the variable.
 * @return the double value.
 */
double BinaryReal::getValue() {
	return value_;
} //getValue


void BinaryReal::setValue(double value) {
	value_ = value;
}


/**
 * Creates an exact copy of a <code>BinaryReal</code> object.
 * @return The copy of the object
 */
Variable * BinaryReal::deepCopy() {
	return new BinaryReal(this);
} //deepCopy


/**
 * Returns the lower bound of the variable.
 * @return the lower bound.
 */
double BinaryReal::getLowerBound() {
	return lowerBound_;
} // getLowerBound


/**
 * Returns the upper bound of the variable.
 * @return the upper bound.
 */
double BinaryReal::getUpperBound() {
	return upperBound_;
} // getUpperBound


/**
 * Sets the lower bound of the variable.
 * @param lowerBound the lower bound.
 */
void BinaryReal::setLowerBound(double lowerBound) {
	lowerBound_ = lowerBound;
} // setLowerBound


/**
 * Sets the upper bound of the variable.
 * @param upperBound the upper bound.
 */
void BinaryReal::setUpperBound(double upperBound) {
	upperBound_ = upperBound;
} // setUpperBound


/**
 * Returns a string representing the object.
 * @return the string.
 */
string BinaryReal::toString() {
	string string_ = "";
	string_ += value_;
	return string_;
} // toString
