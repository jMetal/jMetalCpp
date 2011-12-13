/**
 * @file Binary.h
 * @author Esteban López
 * @version 1.0
 * @date 30 November 2011
 */


#ifndef Binary_h
#define Binary_h

#include <Variable.h>
#include <bitset>
#include <vector>
#include <PseudoRandom.h>
#include <stdlib.h>

/**
 * This class implements a generic binary string variable.It can be used as
 * a base class other binary string based classes (e.g., binary coded integer
 * or real variables).
 */
class Binary : public Variable {

public:
	Binary();
	Binary(int numberOfBits);
	Binary(Binary * variable);
	~Binary() ;
	void decode();
	Variable * deepCopy();
	int getNumberOfBits();
	bool getIth(int bit);
	void setIth(int bit, bool value);
	void flip(int bit) ;
	int hammingDistance(Binary * other);
	string toString();

	double getValue();
	void setValue(double value);
	double getLowerBound();
	double getUpperBound();

protected:
	vector<bool> * bits_;
	int numberOfBits_;
};

#endif
