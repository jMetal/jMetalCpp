//  Operator.cpp
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


#include <Operator.h>


/**
 * Constructor.
**/
Operator::Operator() {
} // Operator


/**
 * Constructor.
**/
Operator::Operator(map<string , void*> parameters) {
  parameters_ = parameters;
} // Operator


/**
 * Destructor.
 */
Operator::~Operator() { /* do nothing */ }


/**
 * Sets a new <code>Object</code> parameter to the operator.
 * @param name The parameter name.
 * @param value Object representing the parameter.
**/
void Operator::setParameter(string name, void *value) {
  parameters_[name] = value;
} // setParameter


/**
 * Returns an object representing a parameter of the <code>Operator</code>
 * @param name The parameter name.
 * @return the parameter.
**/
void * Operator::getParameter(string name) {
  return parameters_[name];
}

