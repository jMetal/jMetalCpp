//  Fitness.cpp
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


#include <Fitness.h>


/**
 * Constructor
 * Creates a new instance of a Fitness object
 */
Fitness::Fitness() {
  utils_ = new MetricsUtil();
} // Fitness


/**
 * Destructor
 */
Fitness::~Fitness() {
  delete utils_;
} // ~Fitness


/**
 * Returns the fitness indicator.
 * @param b. True Pareto front
 * @param a. Solution front
 * @return the value of the epsilon indicator
 */
void Fitness::fitness(vector <vector<double> > a, string file) {
  std::fstream out(file.c_str(), std::ios::out | std::ios::app);
  for (int i=0; i<a.size(); i++) {
    for (int j=0; j<a[i].size(); j++) {
      if (j!=0) {
        out << " ";
      }
      out << a[i][j];
    }
    out << endl;

  }
  out.close();
}

