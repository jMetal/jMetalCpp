//  autodock.cpp
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
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

#include <iostream>
#include <Problem.h>
#include <Solution.h>
#include <SBXCrossover.h>
#include <PolynomialMutation.h>
#include <BinaryTournament2.h>
#include <AutoDock.h>
#include <gGA.h>
//#include <DE.h>
#include <time.h>

const int EVALS=20 ;
//AutoDock * problem ;
pthread_mutex_t mutex1, mutex2 ;
const int numberOfVariables = 10 ;
double x[numberOfVariables] ;
double fx[1] ;

//Problem   * problem   ; // The problem to solve
//Algorithm * algorithm ; // The algorithm to use
//Operator  * crossover ; // Crossover operator
//Operator  * mutation  ; // Mutation operator
//Operator  * selection ; // Selection operator


void * jmetal(void *param) {

  Problem   * problem   ; // The problem to solve
  Algorithm * algorithm ; // The algorithm to use
  Operator  * crossover ; // Crossover operator
  Operator  * mutation  ; // Mutation operator
  Operator  * selection ; // Selection operator

  clock_t t_ini, t_fin;

  problem   = new AutoDock("Real",numberOfVariables, &mutex1, &mutex2, x, fx);
  cout << "El numero de objetivos es " << problem->getNumberOfObjectives() << endl;

  //Algorithm *alg = new gGA(problem,100,EVALS);
  //Algorithm *alg = new DE(problem,100,EVALS);

  algorithm = new gGA(problem);

  cout << "Algoritmo gGA inicializado." << endl;

  // Algorithm parameters
  int populationSizeValue = 10;
  //int *populationSizePtr = &populationSizeValue;
  int maxEvaluationsValue = EVALS;
  //int *maxEvaluationsPtr = &maxEvaluationsValue;
  algorithm->setInputParameter("populationSize",&populationSizeValue);
  algorithm->setInputParameter("maxEvaluations",&maxEvaluationsValue);
//  int populationSizeValue = 100;
//  int *populationSizePtr = &populationSizeValue;
//  int maxEvaluationsValue = EVALS;
//  int *maxEvaluationsPtr = &maxEvaluationsValue;
//  algorithm->setInputParameter("populationSize",populationSizePtr);
//  algorithm->setInputParameter("maxEvaluations",maxEvaluationsPtr);

  cout << "1..." << endl;
  cout << *(int*)algorithm->getInputParameter("maxEvaluations") << endl;

  algorithm->execute();
//map<string, void *> parameters;
//cout << parameters.size() << endl;
//cout << parameters.max_size() << endl;

  cout << "FINISHING GA" << endl ;

  delete algorithm;
  delete problem;
//
//
////  delete populationSizePtr;
////  delete maxEvaluationsPtr;
//
////  // Mutation and Crossover for Real codification
////  map<string, void *> parameters;
////  double probabilityValue1 = 0.9;
////  double *probabilityPtr1 = &probabilityValue1;
////  double distributionIndexValue1 = 20.0;
////  double *distributionIndexPtr1 = &distributionIndexValue1;
////  parameters["probability"] =  probabilityPtr1 ;
////  parameters["distributionIndex"] = distributionIndexPtr1 ;
//////  crossover = new SBXCrossover(parameters);
////
//////  cout << *(double *)parameters["probability"] << endl;
//////  cout << *(double *)parameters["distributionIndex"] << endl;
////
////  delete probabilityPtr1;
////  delete distributionIndexPtr1;
//
//
//
//  cout << "2..." << endl;
////
////  //parameters.clear();
//  cout << "2a..." << endl;
////  double probabilityValue2 = 1.0/problem->getNumberOfVariables();
//  cout << "2b..." << endl;
////  double *probabilityPtr2 = &probabilityValue2;
//  cout << "2c..." << endl;
////  double distributionIndexValue2 = 20.0;
//  cout << "2d..." << endl;
////  double *distributionIndexPtr2 = &distributionIndexValue2;
//  cout << "2e..." << endl;
////  parameters["probability"] = probabilityPtr2;
//  cout << "2f..." << endl;
////  parameters["distributionIndex"] = distributionIndexPtr2 ;
//////  mutation = new PolynomialMutation(parameters);
////
////  cout << "3..." << endl;
////
////  // Selection Operator
////  //parameters.clear();
//////  selection = new BinaryTournament2(parameters) ;
////
////  cout << "Adding operators..." << endl;
////
////  // Add the operators to the algorithm
//////  algorithm->addOperator("crossover",crossover);
//////  algorithm->addOperator("mutation",mutation);
//////  algorithm->addOperator("selection",selection);
////
////  // Execute the Algorithm
////  t_ini = clock();
//////  SolutionSet * population = algorithm->execute();
////  t_fin = clock();
////  double secs = (double) (t_fin - t_ini);
////
////  // Result messages
////  cout << "Total execution time: " << secs << "s" << endl;
//////  cout << "Variables values have been writen to file VAR" << endl;
//////  population->printVariablesToFile("VAR");
//////  cout << "Objectives values have been writen to file FUN" << endl;
//////  population->printObjectivesToFile("FUN");
//
//  cout << "-------- JMETAL TERMINADO -------" << endl ;
  pthread_exit(0) ;
}

/**
   Este codigo main simula el comportamiento de autodock para crear una hebra que ejecute un algoritmo de jMetal, de forma que el problema sea evaluado por el propio autodock
 */
int main(int argc, char ** argv) {
  //jmetal(NULL) ;
  pthread_t jmetalThread ;
  int result ;

  cout << "Comenzando AutoDock..." << endl;

  result = pthread_mutex_init(&mutex1, NULL) ;
  if (result != 0) {
    perror("ERROR INICIALIZANDO EL MUTEX1");
    exit(-1) ;
  }
  else
    cout << "------- MUTEX1 OK ------" << endl ;
  result = pthread_mutex_init(&mutex2, NULL) ;
  if (result != 0) {
    perror("ERROR INICIALIZANDO EL MUTEX2");
    exit(-1) ;
  }
  else
    cout << "------- MUTEX2 OK ------" << endl ;
  result = pthread_mutex_lock(&mutex1) ;
  if (result != 0) {
    perror("MAIN: ERROR ESPERANDO EN EL MUTEX1");
    exit(-1) ;
  }
  else
    cout << "MAIN: MUTEX1 BLOQUEADO FT" << endl ;


  result = pthread_create(&jmetalThread, NULL, jmetal, NULL) ;
  if (result != 0) {
    perror("ERROR CREANDO EL THREAD");
    exit(-1) ;
  }

  for (int i = 0; i < (EVALS) ; i++) {
    result = pthread_mutex_lock(&mutex1) ;
    if (result != 0) {
      perror("MAIN: ERROR ESPERANDO EN EL MUTEX1");
      exit(-1) ;
    }
    else
      cout << "MAIN: MUTEX1 BLOQUEADO" << endl ;

    ///// FUNCION A EVALUAR
    cout << "Comenzamos a evaluar..." << endl;
    double sum = 0.0;
    for (int var = 0; var < 10; var++) {
      sum += pow(x[var], 2.0);
    }
    fx[0] = sum ;
    /////

    cout << "::::::::::: EVALS: " << i << " :::::::::::::" << endl ;

    int result = pthread_mutex_unlock(&mutex2) ;
    if (result != 0) {
      perror("MAIN: ERROR DESBLOQUEANDO MUTEX2");
      exit(-1) ;
    }
    //else
    //  cout << "MAIN: MUTEX2 DESBLOQUEADO" << endl ;
  }



  cout  << "------- ESPERANDO A JMETAL --------" << endl ;

  result = pthread_join(jmetalThread, NULL) ;
  if (result != 0) {
    perror("ERROR AL HACER JOIN");
    exit(-1) ;
  }




  cout << "-------- PROGRAMA TERMINADO --------" << endl ;

}
