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

#ifndef __OPERATOR__
#define __OPERATOR__

#include "JMetalHeader.h"
#include <iostream>

/**
 * Stores the current operator parameters.
 * It is defined as a Map of pairs <<code>String</code>, <code>Object</code>>,
 * and it allow objects to be accessed by their names, which  are specified
 * by the string.
**/

using namespace JMetal;

class Operator
{

protected:
	MapOfStringFunct parameters_;

public:
    Operator ();
    Operator (MapOfStringFunct parameters);
    virtual ~Operator() = 0;
    virtual void *execute(void *) = 0;
    void setParameter(std::string name, void *value);
    void *getParameter(std::string name);

}; // Operator

#endif
