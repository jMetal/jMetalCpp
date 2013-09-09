//  Variabble.cpp
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
//       Juan J. Durillo <durillo@lcc.uma.es>
//       Esteban López-Camacho <esteban@lcc.uma.es>
//
//  Copyright (c) 2011 Antonio J. Nebro, Juan J. Durillo
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
//  cout << "Class " << typeid(this).name() << " does not implement " <<
//      "method getValue" << endl;
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
//  cout << "Class " << typeid(this).name() << " does not implement " <<
//        "method setValue" << endl;
//} // setValue


/**
 * Gets the lower bound value of a variable. As not all
 * objects belonging to a subclass of <code>Variable</code> have a lower bound,
 * a call to this method is considered a fatal error by default,
 * and the program is terminated.
 * Those classes requiring this method must redefine it.
 */
//double Variable::getLowerBound() {
//  cout << "Class " << typeid(this).name() << " does not implement " <<
//        "method getLowerBound" << endl;
//} // getLowerBound


/**
 * Gets the upper bound value of a variable. As not all
 * objects belonging to a subclass of <code>Variable</code> have an upper
 * bound, a call to this method is considered a fatal error by default, and the
 * program is terminated. Those classes requiring this method must redefine it.
 */
//double Variable::getUpperBound() {
//  cout << "Class " << typeid(this).name() << " does not implement " <<
//        "method getUpperBound" << endl;
//} // getUpperBound


/**
 * Destructor
 */
Variable::~Variable() { /* do nothing */ }


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
