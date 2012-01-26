/**
 * @file Operator.cpp
 * @author Juan J. Durillo
 * @author Antonio J. Nebro
 * @author Esteban López
 * @date 23 November 2011
**/

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


//int main() {
//	Operator unOperador;
//	int value = 15;
//	int *ptr = &value;
//	unOperador.setParameter("Edad",ptr);
//	
//	cout << "la edad es: " << *(int *)unOperador.getParameter("Edad") << endl;
//}
