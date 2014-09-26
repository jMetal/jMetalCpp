//  Statistics.cpp
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


#include <Statistics.h>


/**
 * Calculates the median of a vector considering the positions indicated by
 * the parameters first and last
 * @param vector
 * @param first index of first position to consider in the vector
 * @param last index of last position to consider in the vector
 * @return The median
 */
double Statistics::calculateMedian(vector<double> vector_, int first, int last) {
  double median = 0.0;

  int size = last - first + 1;
  // cout << "size: " << size << "first: " << first << " last: " << last << endl;

  if (size % 2 != 0) {
    median = vector_[first + size / 2];
  } else {
    median = (vector_[first + size / 2 - 1] + vector_[first + size / 2]) / 2.0;
  }

  return median;
} // calculatemedian


/**
 * Calculates the interquartile range (IQR) of a vector of doubles
 * @param vector
 * @return The IQR
 */
double Statistics::calculateIQR(vector<double> vector_) {
  double q3 = 0.0;
  double q1 = 0.0;

  if (vector_.size() > 1) { // == 1 implies IQR = 0
    if (vector_.size() % 2 != 0) {
      q3 = calculateMedian(vector_, vector_.size() / 2 + 1, vector_.size() - 1);
      q1 = calculateMedian(vector_, 0, vector_.size() / 2 - 1);
      //cout << "Q1: [" << 0 << ", " << (vector.size()/2 - 1) << "] = " << q1 << endl;
      //cout << "Q3: [" << (vector.size()/2+1) << ", " << (vector.size()-1) << "]= " << q3 << endl;
    } else {
      q3 = calculateMedian(vector_, vector_.size() / 2, vector_.size() - 1);
      q1 = calculateMedian(vector_, 0, vector_.size() / 2 - 1);
      //cout << "Q1: [" << 0 << ", " << (vector.size()/2 - 1) << "] = " << q1 << endl;
      //cout << "Q3: [" << (vector.size()/2) << ", " << (vector.size()-1) << "]= " << q3 << endl;
    } // else
  } // if

  return q3 - q1;
} // calculateIQR
