//  AutoDock.cpp
//
//  Author:
//       Antonio J. Nebro <antonio@lcc.uma.es>
//       Esteban López <esteban@lcc.uma.es>
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


#include <AutoDock.h>


AutoDock::AutoDock(string solutionType,
                   int numberOfVariables,
                   pthread_mutex_t *mutex1,
                   pthread_mutex_t *mutex2,
                   double *x,
                   double *fx):x_(x),fx_(fx),mutex1_(mutex1), mutex2_(mutex2) {
  numberOfVariables_   = numberOfVariables;
  numberOfObjectives_  = 1;
  numberOfConstraints_ = 0;

  lowerLimit_ = new double[numberOfVariables_];
  if (lowerLimit_ == NULL) {
    cout << "AutoDock::AutoDock. Error reserving memory for storing the array of lower limits" << endl;
  } // if

  upperLimit_ = new double[numberOfVariables_];
  if (upperLimit_ == NULL) {
    cout << "AutoDock::AutoDock. Error reserving memory for storing the array of upper limits" << endl;
    exit(-1) ;
  } // if

/*
  for (int i = 0; i < numberOfVariables_; i++) {
    lowerLimit_[i] = -5.12;
    upperLimit_[i] =  5.12;
  } // for
*/

  cout << "Inicializando limites..." << endl;

  lowerLimit_[0] = 3.262;
  upperLimit_[0] = 33.262;
  lowerLimit_[0+numberOfVariables_/2] = 3.262;
  upperLimit_[0+numberOfVariables_/2] = 33.262;
  lowerLimit_[1] = 11.863;
  upperLimit_[1] = 37.363;
  lowerLimit_[1+numberOfVariables_/2] = 11.863;
  upperLimit_[1+numberOfVariables_/2] = 37.363;
  lowerLimit_[2] = -16.677;
  upperLimit_[2] = 11.073;
  lowerLimit_[2+numberOfVariables_/2] = -16.677;
  upperLimit_[2+numberOfVariables_/2] = 11.073;
  for (int i=3; i<8; i++) {
    lowerLimit_[i] = -1.0;
    upperLimit_[i] = 1.0;
    lowerLimit_[i+numberOfVariables_/2] = -1.0;
    upperLimit_[i+numberOfVariables_/2] = 1.0;
  }
  for (int i=8; i<numberOfVariables_/2; i++) {
    // TODO: Límites provisionales
    lowerLimit_[i] = -3.1418;
    upperLimit_[i] = 3.1418;
    lowerLimit_[i+numberOfVariables_/2] = -3.1418;
    upperLimit_[i+numberOfVariables_/2] = 3.1418;
  }

  // TODO: Solution type initialization
  solutionType_ = new RealSolutionType(this);

  int result = pthread_mutex_lock(mutex2_) ;
  if (result != 0) {
    cout << "AUTODOCK: ERROR BLOQUEANDO EL MUTEX2" << endl;
    //perror("AUTODOCK: ERROR BLOQUEANDO EL MUTEX2");
    exit(-1) ;
  }
  else {
    cout << "AUTODOCK: MUTEX2 BLOQUEADO FT" << endl ;
  }

}


void AutoDock::evaluate(Solution *solution) {
  Variable **variables = solution->getDecisionVariables();

  for (int i = 0; i < numberOfVariables_; i++) {
    x_[i] = variables[i]->getValue() ;
    //cout << "x_[" << i << "] = " << x_[i] << ";" << endl;
  }
  //cin.ignore();
//  x_[0]= 26.421495183869922;
//  x_[1]= 15.817008882635584;
//  x_[2]= 2.7737425091576977;
//  x_[3]=0.3414163335482513;
//  x_[4]=0.5063600914954243;
//  x_[5]=0.2970021921994954;
//  x_[6]=0.6149151275125038;
//  x_[7]=-0.16355034934768697;
//  x_[8]=2.865493880628601;
//  x_[9]=-0.6173975082480535;
//  x_[10]=-0.4818767140163316;
//  x_[11]=0.16049089858482368;
//  x_[12]= 1.056437336267306;
//  x_[13]=0.015329088557012526;
//  x_[14]=-1.4000887366765846;
//  x_[15]= 1.6596746294246933;
//  x_[16]=-1.0741873186535957;
//  x_[17]=-1.3978469481400129;
//  x_[18]=1.9376208419878727;
//    x_[19]= 28.351587535761357;
//    x_[20]= 17.518257903960787;
//    x_[21]= -6.88365498570189;
//    x_[22]=0.08539952896275327;
//    x_[23]=0.76988466450948;
//    x_[24]=0.4941460401479435;
//    x_[25]=-0.6471649599294873;
//    x_[26]=0.303606430020769;
//    x_[27]= 1.1491931713931238;
//    x_[28]=-2.311660133230805;
//    x_[29]=-2.7620920752401084;
//    x_[30]=1.3964269478429174;
//    x_[31]=0.15602042334084434;
//    x_[32]=-0.06366316182273477;
//    x_[33]= 0.48214017985171465;
//    x_[34]= 0.06924393332024542;
//    x_[35]=2.6817912076892316;
//    x_[36]=0.33246265410490167;
//    x_[37]=1.2350751786285818;

  int result = pthread_mutex_unlock(mutex1_) ;
  if (result != 0) {
    cerr << "AUTODOCK: ERROR DESBLOQUEANDO EN EL MUTEX" << endl;
    exit(-1) ;
  }
  //else
  //  cout << "AUTODOCK: MUTEX1 DESBLOQUEADO" << endl ;

  result = pthread_mutex_lock(mutex2_) ;
  if (result != 0) {
    cerr << "AUTODOCK: ERROR BLOQUEANDO EL MUTEX2" << endl;
    exit(-1) ;
  }
  //else
  //  cout << "AUTODOCK: MUTEX2 BLOQUEADO" << endl ;

  /*
  double sum = 0.0;
  for (int var = 0; var < numberOfVariables_; var++) {
    sum += pow(x_[var], 2.0);
  }

  fx_[0] = sum ;
  */

  solution->setObjective(0,fx_[0]);

}

