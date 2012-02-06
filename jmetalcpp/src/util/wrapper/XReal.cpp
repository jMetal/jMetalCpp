/**
  * @file XReal.cpp
  * @author Esteban López
  * @date 30 November 2011
**/


#include <XReal.h>


/**
 * Constructor
 */
XReal::XReal() {
} // Constructor


/**
 * Constructor
 * @param solution
 */
XReal::XReal(Solution * solution) {
  type_ = solution->getType();
  solution_ = solution;
//	cout << "Tipo de XReal: " << typeid(type_).name() << " : " << endl;
//	cout << "Tipo de XReal: " << typeid(*type_).name() << " : " << endl;
//	cout << "Tipo de XReal: " << typeid(realSolutionType).name() << " : " <<  endl;
//	cout << "Tipo de XReal: " << typeid(RealSolutionType).name() << " : " <<  endl;
}


/**
 * Gets value of a variable
 * @param index Index of the variable
 * @return The value of the variable
 * @throws JMException
 */
double XReal::getValue(int index) {
  if ((typeid(*type_) == typeid(RealSolutionType)) ||
      (typeid(*type_) == typeid(BinarySolutionType))){
    return solution_->getDecisionVariables()[index]->getValue();
  }
  else if (typeid(*type_) == typeid(ArrayRealSolutionType)) {
    return ((ArrayReal*)(solution_->getDecisionVariables()[0]))->array_[index];
  }
  else {
    cout << "ERROR GRAVE: solution type "
        << typeid(*type_).name() << " invalid" << endl;
  }
  return 0.0;
} // getValue


/**
 * Sets the value of a variable
 * @param index Index of the variable
 * @param value Value to be assigned
 * @throws JMException
 */
void XReal::setValue(int index, double value) {
  if (typeid(*type_) == typeid(RealSolutionType))
    solution_->getDecisionVariables()[index]->setValue(value);
  else if (typeid(*type_) == typeid(ArrayRealSolutionType))
    ((ArrayReal*)(solution_->getDecisionVariables()[0]))->array_[index]=value;
  else {
    cout << "ERROR GRAVE: solution type "
        << typeid(*type_).name() << "+ invalid" << endl;
  }
} // setValue


/**
 * Gets the lower bound of a variable
 * @param index Index of the variable
 * @return The lower bound of the variable
 * @throws JMException
 */
double XReal::getLowerBound(int index) {
  if ((typeid(*type_) == typeid(RealSolutionType)) ||
      (typeid(*type_) == typeid(BinarySolutionType)))
    return solution_->getDecisionVariables()[index]->getLowerBound();
  else if (typeid(*type_) == typeid(ArrayRealSolutionType))
    return ((ArrayReal*)(solution_->getDecisionVariables()[0]))->getLowerBound(index);
  else {
    cout << "ERROR GRAVE: solution type "
        << typeid(*type_).name() << "+ invalid" << endl;
  }
  return 0.0;
} // getLowerBound


/**
 * Gets the upper bound of a variable
 * @param index Index of the variable
 * @return The upper bound of the variable
 * @throws JMException
 */
double XReal::getUpperBound(int index) {
  if ((typeid(*type_) == typeid(RealSolutionType)) ||
      (typeid(*type_) == typeid(BinarySolutionType)))
    return solution_->getDecisionVariables()[index]->getUpperBound();
  else if (typeid(*type_) == typeid(ArrayRealSolutionType))
    return ((ArrayReal*)(solution_->getDecisionVariables()[0]))->getUpperBound(index);
  else {
    cout << "ERROR GRAVE: solution type "
        << typeid(*type_).name() << "+ invalid" << endl;
  }
  return 0.0;
} // getUpperBound


/**
 * Returns the number of variables of the solution
 * @return
 */
int XReal::getNumberOfDecisionVariables() {
  if ((typeid(*type_) == typeid(RealSolutionType)) ||
      (typeid(*type_) == typeid(BinarySolutionType)))
    //return solution_->getDecisionVariables().length ;
    return solution_->getNumberOfVariables();
  else if (typeid(*type_) == typeid(ArrayRealSolutionType))
    return ((ArrayReal*)(solution_->getDecisionVariables()[0]))->getLength() ;
  else {
    cout << "ERROR GRAVE: solution type "
        << typeid(*type_).name() << "+ invalid" << endl;
  }
  return 0 ;
} // getNumberOfDecisionVariables


/**
 * Returns the number of variables of the solution
 * @return
 */
int XReal::size() {
  if ((typeid(*type_) == typeid(RealSolutionType)) ||
      (typeid(*type_) == typeid(BinarySolutionType)))
    //return solution_->getDecisionVariables().length;
    return solution_->getNumberOfVariables();
  else if (typeid(*type_) == typeid(ArrayRealSolutionType))
    return ((ArrayReal*)(solution_->getDecisionVariables()[0]))->getLength();
  else {
    cout << "ERROR GRAVE: solution type "
        << typeid(*type_).name() << "+ invalid" << endl;
  }
  return 0 ;
} // size
