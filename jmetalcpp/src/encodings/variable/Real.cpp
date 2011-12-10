/**
 * @file Real.cpp
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 30 November 2011
 */

#include <Real.h>


/** 
  * Empty constructor. 
  * It will only initialize all the variables.
 **/
Real::Real() {
	value_ = 0.0;
} // Real


/**
 * Lower and Upper bounds based constructor.
 * It will initialize the upper and lower bounds of the 
 * variable and it will initialize its value to a random
 * value between those upper and lower bound values.
 **/
Real::Real(double lowerBound, double upperBound) {
	value_ = PseudoRandom::randDouble(lowerBound, upperBound);
  lowerBound_ = lowerBound;
  upperBound_ = upperBound;
} // Real


/**
 * Constructor
 */
Real::Real(Variable * variable) {
	lowerBound_ = variable->getLowerBound();
	upperBound_ = variable->getUpperBound();
	value_      = variable->getValue();
} // Real


/**
 * Gets the value of the <code>Real</code> variable.
 * @return the value.
 */
double Real::getValue() {
	return value_;
} // getValue


/**
 * Sets the value of the variable.
 * @param value The value.
 */
void Real::setValue(double value) {
	value_ = value;
} // setValue


/**
 * Returns a exact copy of the <code>Real</code> variable
 * @return the copy
 */
Variable *Real::deepCopy() {
	return new Real(this);
} // deepCopy


/**
 * Gets the lower bound of the variable.
 * @return the lower bound.
 */
double Real::getLowerBound() {
	return lowerBound_;
} // getLowerBound


/**
 * Gets the upper bound of the variable.
 * @return the upper bound.
 */
double Real::getUpperBound() {
	return upperBound_;
} // getUpperBound


/**
 * Sets the lower bound of the variable.
 * @param lowerBound The lower bound.
 */
void Real::setLowerBound(double bound) {
	lowerBound_ = bound;
} // setLowerBound


/**
 * Sets the upper bound of the variable.
 * @param upperBound The upper bound.
 */
void Real::setUpperBound(double bound) {
	upperBound_ = bound;
} // setUpperBound

