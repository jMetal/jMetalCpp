/**
 * @file Kursawe.h
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 01 December 2011
 */

#ifndef __KURSAWE__
#define __KURSAWE__

#include <Problem.h>
#include <math.h>
#include <BinaryRealSolutionType.h>
#include <RealSolutionType.h>
#include <ArrayRealSolutionType.h>
#include <XReal.h>
#include <Solution.h>

//using namespace std;

/**
 * Class representing problem Kursawe
 */
class Kursawe : public Problem {

public:
  Kursawe(string solutionType, int numberOfVariables = 3);
  void evaluate(Solution *solution);  
};

#endif
