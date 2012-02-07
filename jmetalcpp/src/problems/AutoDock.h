//  AutoDock.h
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

#ifndef AUTODOCK_H_
#define AUTODOCK_H_

#include <math.h>
#include <pthread.h>
#include <Problem.h>
#include <RealSolutionType.h>
#include <Solution.h>


class AutoDock : public Problem {

public:
  double *fx_ ; // Function values
  double *x_  ; // Decision variables

  pthread_mutex_t * mutex1_, * mutex2_ ;

  AutoDock(string solutionType,
           int numberOfVariables,
           pthread_mutex_t *mutex1,
           pthread_mutex_t *mutex2,
           double *,
           double *) ;
  void evaluate(Solution *solution);
};

#endif /* AUTODOCK_H_ */
