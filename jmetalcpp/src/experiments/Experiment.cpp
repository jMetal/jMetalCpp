//  Experiment.cpp
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


#include <Experiment.h>


/**
 * Constructor
 *
 * Contains default settings
 */
Experiment::Experiment() {}


void Experiment::checkExperimentDirectory() {
  int res = FileUtils::existsPath(experimentBaseDirectory_.c_str());
  switch (res) {
  case 0:
    cout << "Experiment directory does NOT exist. Creating" << endl;
    if (FileUtils::createDirectory(experimentBaseDirectory_) == -1) {
      cout << "Error creating directory" << endl;
      exit(-1);
    }
    break;
  case 1:
    cout << "Experiment directory exists." << endl;
    cout << "Experiment directory is a directory" << endl;
    break;
  case 2:
    cout << "Experiment directory exists." << endl;
    cout << "Experiment directory is not a directory. Deleting file and creating directory" << endl;
    if( remove(experimentBaseDirectory_.c_str()) != 0 ) {
      cout << "Error deleting file." << endl;
      exit(-1);
    } else {
      cout << "File successfully deleted." << endl;
    }
    if (FileUtils::createDirectory(experimentBaseDirectory_) == -1) {
      cout << "Error creating directory" << endl;
      exit(-1);
    }
    break;
  case -1:
    cout << "Error checking experiment directory" << endl;
    exit(-1);
  }
} // checkExperimentDirectory


void Experiment::resetFile(string file) {
  int res = FileUtils::existsPath(file.c_str());
  switch (res) {
  case 0:
    cout << "File (" << file << ") does NOT exist." << endl;
    break;
  case 1:
    cout << "File (" << file << ") exists." << endl;
    cout << "File (" << file << ") is a directory. Deleting directory." << endl;
    if( remove(file.c_str()) != 0 ) {
      cout << "Error deleting directory." << endl;
      exit(-1);
    } else {
      cout << "Directory successfully deleted." << endl;
    }
    break;
  case 2:
    cout << "File (" << file << ") exists." << endl;
    cout << "File (" << file << ") is a file. Deleting file." << endl;
    if( remove(file.c_str()) != 0 ) {
      cout << "Error deleting file." << endl;
      exit(-1);
    } else {
      cout << "File successfully deleted." << endl;
    }
    break;
  case -1:
    cout << "Error checking file (" << file << ")" << endl;
    exit(-1);
  }
} // resetFile

