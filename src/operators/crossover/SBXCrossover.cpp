//  SBXCrossover.cpp
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


#include <SBXCrossover.h>

/**
  * @class SBXCrossover
  * @brief This class is aimed at representing a SBXCrossover operator
**/


const double SBXCrossover::EPS = 1.0e-14;
const double SBXCrossover::ETA_C_DEFAULT_ = 20.0;


/**
 * Constructor
 * Create a new SBX crossover operator whit a default
 * index given by <code>DEFAULT_INDEX_CROSSOVER</code>
 */
SBXCrossover::SBXCrossover(map<string, void *> parameters)
: Crossover(parameters) {
  //TODO: crossoverProbability_ = NULL;
  distributionIndex_ = ETA_C_DEFAULT_;
  if (parameters["probability"] != NULL)
    crossoverProbability_ = *(double *)parameters["probability"];
  if (parameters["distributionIndex"] != NULL)
    distributionIndex_ = *(double *)parameters["distributionIndex"];
} // SBXCrossover


/**
 * Destructor
 */
SBXCrossover::~SBXCrossover() { } // ~SBXCrossover


/**
* Perform the crossover operation. 
* @param probability Crossover probability
* @param parent1 The first parent
* @param parent2 The second parent
* @return An array containing the two offsprings
**/
Solution ** SBXCrossover::doCrossover(double probability, Solution *parent1, Solution *parent2) {
  
  Solution** offSpring = new Solution*[2];
  
  if (offSpring == NULL) {
    cout << "Error grave: Impossible reserve memory for allocating new solutions when performing SBXCrossover " << endl;
    exit(-1);
  }

//  cout << "SBXCrossover: AggregativeValue de parent1 = " << parent1->getAggregativeValue() << endl;
//  cout << "SBXCrossover: AggregativeValue de parent2 = " << parent2->getAggregativeValue() << endl;

  offSpring[0] = new Solution(parent1);
  offSpring[1] = new Solution(parent2);

//  cout << "SBXCrossover: AggregativeValue de offSpring[0] = " << offSpring[0]->getAggregativeValue() << endl;
//  cout << "SBXCrossover: AggregativeValue de offSpring[1] = " << offSpring[1]->getAggregativeValue() << endl;
                  
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

  delete x1;
  delete x2;
  delete offs1;
  delete offs2;
                                  
  return offSpring;

} // doCrossover
  
  
/**
* Executes the operation
* @param object An object containing an array of two parents
* @return An object containing the offSprings
*/
void * SBXCrossover::execute(void *object) {

//  double probability = *(double *)getParameter("probability");
    
  Solution ** parents = (Solution **) object;
  // TODO: Comprobar la longitud de parents
  // TODO: Chequear el tipo de parents

  Solution ** offSpring = (Solution **)doCrossover(crossoverProbability_, parents[0], parents[1]);
            
//  for (int i = 0; i < 2; i++) // this operator will return only 2 offpsrings
//  {
//    offSpring[i]->setCrowdingDistance(0.0);
//    offSpring[i]->setRank(0);
//  }

  return offSpring;
} // execute 
