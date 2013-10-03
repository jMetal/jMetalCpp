//  UtilsCMAES.cpp
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

#include <UtilsCMAES.h>

/**
 * Utilities methods to used by CMA-ES
 */


void UtilsCMAES::minFastSort(IntDouble ** x, int size) {
  
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (x[i]->getVal() > x[j]->getVal()) {
        IntDouble * temp = x[i];
        x[i] = x[j];
        x[j] = temp;
      } else if (x[i]->getVal() == x[j]->getVal()) {
        if (x[i]->getI() > x[j]->getI()) {
          IntDouble * temp = x[i];
          x[i] = x[j];
          x[j] = temp;
        } 
      } // if
    }
  } // for
  
} // minFastSort
