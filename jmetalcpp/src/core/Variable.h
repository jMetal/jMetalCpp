/**
 * @file Variable.cpp
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 28 November 2011
**/

#ifndef __VARIABLE__
#define __VARIABLE__

#include <typeinfo>
#include <string>
#include <iostream>

using namespace std ;

/**
 * This is an abstract class for storing the variables composing a solution.  
 * Some examples of variables can be Real, Binary, etc. There is no guarantee
 * that those variables are implemented on the current version of this project
 */
class Variable {

public:
    virtual Variable * deepCopy() = 0;
    virtual double getValue() = 0;
    virtual void setValue(double value) = 0;
    virtual double getLowerBound() = 0;
    virtual double getUpperBound() = 0;
    void setLowerBound(double bound);
    void setUpperBound(double bound);
    //void setVariableType(VariableType_ variableType);
    string getVariableType();
    virtual string toString() = 0 ;

}; // Variable

#endif
