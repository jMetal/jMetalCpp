/**
 * @file Variable.cpp
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 24 November 2011
 */

#include <Variable.h>
#include <cstddef>


/**
 * This is an abstract class for storing the variables composing a solution.  
 * Some examples of variables can be Real, Binary, etc. There is no guaratee
 * that those variables are implemented on the current version of this project
 */


using namespace std;


///**
// * Gets the double value representating the variable.
// * It is used in subclasses of <code>Variable</code> (i.e. <code>Real</code>
// * and <code>Int</code>).
// * As not all objects belonging to a subclass of <code>Variable</code> have a
// * double value, a call to this method it is considered a fatal error by
// * default, and the program is terminated. Those classes requiring this method
// * must redefine it.
// */
//double Variable::getValue() {
//	cout << "Class " << typeid(this).name() << " does not implement " <<
//			"method getValue" << endl;
//} // getValue
//
//
///**
// * Sets a double value to a variable in subclasses of <code>Variable</code>.
// * As not all objects belonging to a subclass of <code>Variable</code> have a
// * double value, a call to this method it is considered a fatal error by
// * default, and the program is terminated. Those classes requiring this method
// * must redefine it.
// */
//void Variable::setValue(double value) {
//	cout << "Class " << typeid(this).name() << " does not implement " <<
//				"method setValue" << endl;
//} // setValue


/**
 * Gets the lower bound value of a variable. As not all
 * objects belonging to a subclass of <code>Variable</code> have a lower bound,
 * a call to this method is considered a fatal error by default,
 * and the program is terminated.
 * Those classes requiring this method must redefine it.
 */
//double Variable::getLowerBound() {
//	cout << "Class " << typeid(this).name() << " does not implement " <<
//				"method getLowerBound" << endl;
//} // getLowerBound


/**
 * Gets the upper bound value of a variable. As not all
 * objects belonging to a subclass of <code>Variable</code> have an upper
 * bound, a call to this method is considered a fatal error by default, and the
 * program is terminated. Those classes requiring this method must redefine it.
 */
//double Variable::getUpperBound() {
//	cout << "Class " << typeid(this).name() << " does not implement " <<
//				"method getUpperBound" << endl;
//} // getUpperBound


/**
 * Sets the lower bound for a variable. As not all objects belonging to a
 * subclass of <code>Variable</code> have a lower bound, a call to this method
 * is considered a fatal error by default and the program is terminated.
 * Those classes requiring this method must to redefine it.
 */
void Variable::setLowerBound(double lowerBound) {
	cout << "Class " << typeid(this).name() << " does not implement " <<
				"method setLowerBound" << endl;
} // setLowerBound


/**
 * Sets the upper bound for a variable. As not all objects belonging to a
 * subclass of <code>Variable</code> have an upper bound, a call to this method
 * is considered a fatal error by default, and the program is terminated.
 * Those classes requiring this method must redefine it.
 */
void Variable::setUpperBound(double upperBound) {
	cout << "Class " << typeid(this).name() << " does not implement " <<
				"method setUpperBound" << endl;
} // setUpperBound


/**
 * Gets the type of the variable. The types are defined in class Problem.
 * @return The type of the variable
 */

string Variable::getVariableType() {
	return typeid(this).name() ;
} // getVariableType
