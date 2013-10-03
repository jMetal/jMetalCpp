//  CMAParameters.cpp
//
//  Author:
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


#include <CMAParameters.h>


/**
 * Constructor
 */
CMAParameters::CMAParameters(int N, int lambda) {
  mucov = -1;
	ccov = -1;
  setDefaults(N, lambda);
} // CMAParameters

void CMAParameters::setDefaults(int N, int lambda) {
//  // parameters that can be zero were initialized to -1
//		if (supplemented > 0)
//			error("defaults cannot be supplemented twice");
//		if (N == 0)
//			error("dimension must be greater than zero");
//
//		supplemented = 1;
//		locked = 1;
  chiN = sqrt(N) * (1.0 - 1.0 / (4.0 * N) + 1.0 / (21.0 * N * N));

  // set parameters to their default if they were not set before
//  if (lambda <= 0) {
  lambda = (int) (4.0 + 3.0 * log(N));
//  }

//  if (mu <= 0) {
  mu = (int) floor(lambda/2.);
//  }
  
//  if (weights == null) {
  setWeights(mu);
//  } else if (weights.length == 0) {
//    setWeights(mu, recombinationType);
//  }
  
//  if (cs <= 0) {
  cs = (mueff+2) / (N+mueff+3);
//  }
	
//  if (damps <= 0) {
  damps =
          (1 + 2 * fmax(0, sqrt((mueff - 1.) / (N + 1.)) - 1))
          * fmax(0.3, 1 -                         /* modification for short runs */
          N / (1e-6
//          +fmin(opts.stopMaxIter,
//          opts.stopMaxFunEvals/lambda)
          ))
          + cs ;                                    /* minor increment */
//  }
  
//  if (cc <= 0) {
  cc = 4.0 / (N + 4.0);
//  }
  
  if (mucov < 0) {
    mucov = mueff;
  }
  
  if (ccov < 0) { // TODO: setting should depend on gendiagonalcov
    ccov = 2.0 / (N + 1.41) / (N + 1.41) / mucov
            + (1 - (1.0 / mucov))
            * fmin(1, (2 * mueff - 1) / (mueff + (N + 2) * (N + 2)));
    ccovsep = fmin(1, ccov * (N + 1.5) / 3.0);
  }
  
//  // check everything
//  String s = check();
//		if (s == null)
//			;
//		else if (s.equals(""))
//			;
//		else
//			error(s); // if any prior setting does not work
}

/**
 * Setter for recombination weights
 *
 * @param mu is the number of parents, number of weights > 0 
 */
void CMAParameters::setWeights(int mu) {
  double * w = new double[mu];
//		if (recombinationType == RecombinationType.equal)
//			for (int i = 0; i < mu; ++i) 
//				w[i] = 1;
//		else if (recombinationType == RecombinationType.linear)
//			for (int i = 0; i < mu; ++i) 
//				w[i] = mu - i;
//		else // default, seems as enums can be null
  for (int i = 0; i < mu; i++) {
    w[i] = (log(mu + 1) - log(i + 1));
  } 	
  setWeights(w, mu);
}

/** normalizes recombination weights vector and sets mueff **/
void CMAParameters::setWeights(double * w, int weightsLength) {
//		assert locked == 0;
  double sum = 0;
	for (int i = 0; i < weightsLength; i++) {
    sum += w[i];
  }
  for (int i = 0; i < weightsLength; i++) {
    w[i] /= sum;
  }
  weights = w;
  // setMu(weights.length);
  double sum1 = 0;
  double sum2 = 0;
  for (int i = 0; i < mu; i++) {
    sum1 += w[i];
    sum2 += w[i] * w[i];
  }
  mueff = sum1 * sum1 / sum2;
}

int CMAParameters::getMu() {
  return mu;
}

double * CMAParameters::getWeights() {
  return weights;
}

double CMAParameters::getMucov() {
  return mucov;
}

double CMAParameters::getCcov(bool flgdiag) {
  if (flgdiag) return ccovsep;
  return ccov;
}

double CMAParameters::getCcov() {
  return ccov;
}

double CMAParameters::getMueff() {
  return mueff;
}

double CMAParameters::getDamps() {
  return damps;
}

double CMAParameters::getCc() {
  return cc;
}

double CMAParameters::getCs() {
  return cs;
}
  
double CMAParameters::getChiN() {
  return chiN;
}
