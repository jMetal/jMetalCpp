/**
 * @file AutoDock.h
 * @author Antonio J. Nebro
 * @author Juan J. Durillo
 * @author Esteban López
 * @version 1.0
 * @date 10 January 2012
 */

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
