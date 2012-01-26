/**
 * @file Operator.h
 * @author Juan J. Durillo
 * @author Antonio J. Nebro
 * @author Esteban López
 * @date 23 November 2011
**/

#ifndef __OPERATOR__
#define __OPERATOR__

#include <map>
#include <string>
#include <iostream>

using namespace std;

/**
 * Stores the current operator parameters.
 * It is defined as a Map of pairs <<code>String</code>, <code>Object</code>>,
 * and it allow objects to be accessed by their names, which  are specified
 * by the string.
**/
class Operator {

protected:
    map<string,void *> parameters_;
    
public:
  Operator ();
  Operator (map<string, void*> parameters);
  virtual ~Operator() = 0;
	virtual void *execute(void *) = 0;
	void setParameter(string name, void *value);
	void *getParameter(string name);

}; // Operator

#endif
