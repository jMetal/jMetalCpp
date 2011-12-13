/*
 * SinglePointCrossover.cpp
 *
 *  Created on: 13/12/2011
 *      Author: antonio
 */

#include <SinglePointCrossover.h>
#include <SinglePointCrossover.h>

/**
  * @class SinglePointCrossover
  * @brief This class is aimed at representing a SinglePointCrossover operator
**/

/**
 * Constructor
 * Create a new SBX crossover operator whit a default
 * index given by <code>DEFAULT_INDEX_CROSSOVER</code>
 */
SinglePointCrossover::SinglePointCrossover(map<string, void *> parameters)
: Crossover(parameters) {
	crossoverProbability_ = 0.0 ;
	//TODO: crossoverProbability_ = NULL;
	if (parameters["probability"] != NULL)
		crossoverProbability_ = *(double *)parameters["probability"];
} // SinglePointCrossover


/**
* Perform the crossover operation.
* @param probability Crossover probability
* @param parent1 The first parent
* @param parent2 The second parent
* @return An array containing the two offsprings
**/
Solution ** SinglePointCrossover::doCrossover(double probability, Solution *parent1, Solution *parent2) {

  Solution** offSpring = new Solution*[2];

  if (offSpring == NULL) {
  	cout << "Error grave: Impossible reserve memory for allocating new solutions when performing SinglePointCrossover " << endl;
  	exit(-1);
  }

  offSpring[0] = new Solution(parent1);
  offSpring[1] = new Solution(parent2);

  if (PseudoRandom::randDouble() < probability) {
      //1. Compute the total number of bits
      int totalNumberOfBits = 0;
      for (int i = 0; i < parent1->getProblem()->getNumberOfVariables(); i++) {
        totalNumberOfBits +=
        ((Binary *)(parent1->getDecisionVariables()[0]))->getNumberOfBits() ;
      }

      //2. Calcule the point to make the crossover
      int crossoverPoint = PseudoRandom::randInt(0, totalNumberOfBits - 1);

      //3. Compute the variable containing the crossoverPoint bit
      int variable = 0;
      int acountBits =
          ((Binary *)(parent1->getDecisionVariables()[variable]))->getNumberOfBits() ;

      while (acountBits < (crossoverPoint + 1)) {
        variable++;
        acountBits +=
            ((Binary *)(parent1->getDecisionVariables()[variable]))->getNumberOfBits() ;
      }

      //4. Compute the bit into the variable selected
      int diff = acountBits - crossoverPoint;
      int intoVariableCrossoverPoint =
           ((Binary *)(parent1->getDecisionVariables()[variable]))->getNumberOfBits() - diff;


      //5. Make the crossover into the the gene;
      Variable* offSpring1, * offSpring2;
      Binary * of1, *of2 ;
      offSpring1 =
         ((parent1->getDecisionVariables()[variable]))->deepCopy();

      offSpring2 =
         ((parent2->getDecisionVariables()[variable]))->deepCopy();
      of1 = (Binary *)offSpring1 ;
      of2 = (Binary *)offSpring2 ;

      for (int i = intoVariableCrossoverPoint;
              i < of1->getNumberOfBits();
              i++) {
//        boolean swap = offSpring1.bits_.get(i);
//        offSpring1.bits_.set(i, offSpring2.bits_.get(i));
//        offSpring2.bits_.set(i, swap);
      }
/*
      offSpring[0].getDecisionVariables()[variable] = offSpring1;
      offSpring[1].getDecisionVariables()[variable] = offSpring2;

      //6. Apply the crossover to the other variables
      for (int i = 0; i < variable; i++) {
        offSpring[0].getDecisionVariables()[i] =
                parent2.getDecisionVariables()[i].deepCopy();

        offSpring[1].getDecisionVariables()[i] =
                parent1.getDecisionVariables()[i].deepCopy();

      }

      //7. Decode the results
      for (int i = 0; i < offSpring[0].getDecisionVariables().length; i++) {
        ((Binary) offSpring[0].getDecisionVariables()[i]).decode();
        ((Binary) offSpring[1].getDecisionVariables()[i]).decode();
      }
    } // Binary or BinaryReal



  /*



  int i;
  double rand;
  double y1, y2, yL, yu;
  double c1, c2;
  double alpha, beta, betaq;
  double valueX1,valueX2;
  XReal * x1 = new XReal(parent1) ;
	XReal * x2 = new XReal(parent2) ;
	XReal * offs1 = new XReal(offSpring[0]) ;
	XReal * offs2 = new XReal(offSpring[1]) ;

  int numberOfVariables = x1->getNumberOfDecisionVariables();

  if (PseudoRandom::randDouble() <= probability){
    for (i=0; i<numberOfVariables; i++){
      valueX1 = x1->getValue(i);
      valueX2 = x2->getValue(i);
      //cout << "Values : " << valueX1 << " " << valueX2 << endl;
      if (PseudoRandom::randDouble()<=0.5 ){
        if (fabs(valueX1- valueX2) > EPS){

          if (valueX1 < valueX2){
            y1 = valueX1;
            y2 = valueX2;
          } else {
            y1 = valueX2;
            y2 = valueX1;
          } // if

          yL = x1->getLowerBound(i);
          yu = x1->getUpperBound(i);

          //cout << yL << " " << yu << endl;
          rand = PseudoRandom::randDouble();

          beta = 1.0 + (2.0*(y1-yL)/(y2-y1));
          alpha = 2.0 - pow(beta,-(distributionIndex_+1.0));

          //cout << "alpha y beta " << alpha << " " << beta << endl;

          if (rand <= (1.0/alpha)){
            betaq = pow ((rand*alpha),(1.0/(distributionIndex_+1.0)));
          } else {
            betaq = pow ((1.0/(2.0 - rand*alpha)),(1.0/(distributionIndex_+1.0)));
          } // if

          c1 = 0.5*((y1+y2)-betaq*(y2-y1));
          beta = 1.0 + (2.0*(yu-y2)/(y2-y1));
          alpha = 2.0 - pow(beta,-(distributionIndex_+1.0));

          if (rand <= (1.0/alpha)){
            betaq = pow ((rand*alpha),(1.0/(distributionIndex_+1.0)));
          } else {
            betaq = pow ((1.0/(2.0 - rand*alpha)),(1.0/(distributionIndex_+1.0)));
          } // if

          c2 = 0.5*((y1+y2)+betaq*(y2-y1));

          if (c1<yL)
            c1=yL;

          if (c2<yL)
            c2=yL;

          if (c1>yu)
            c1=yu;

          if (c2>yu)
            c2=yu;

          //cout << "nuevo valor " << c2 << endl;

          if (PseudoRandom::randDouble()<=0.5) {
            offs1->setValue(i,c2);
            offs2->setValue(i,c1);
          } else {
            offs1->setValue(i,c1);
            offs2->setValue(i,c2);
          } // if
        } else {
          offs1->setValue(i,valueX1);
          offs2->setValue(i,valueX2);
        } // if
      } else {
      	offs1->setValue(i,valueX2);
      	offs2->setValue(i,valueX1);
      } // if
    } // if
  } // if
*/
   return offSpring;
} // doCrossover


/**
* Executes the operation
* @param object An object containing an array of two parents
* @return An object containing the offSprings
*/
void * SinglePointCrossover::execute(void *object) {
  Solution ** parents = (Solution **) object;
  // TODO: Comprobar la longitud de parents
  // TODO: Chequear el tipo de parents

  Solution ** offSpring = (Solution **)doCrossover(crossoverProbability_, parents[0], parents[1]);

  return offSpring;
} // execute

