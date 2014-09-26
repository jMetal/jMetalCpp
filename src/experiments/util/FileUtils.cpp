//  FileUtils.cpp
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


#include <FileUtils.h>


/**
 * Checks if a path exists and if it is a file or a folder
 * Returns:
 *   -1: error
 *    0: path doesn't exist
 *    1: path is a folder
 *    2: path is a file
 */
int FileUtils::existsPath(const char* path) {
  int res = -1;
  struct stat statbuf;
  if (stat(path, &statbuf) != -1) {
    if (S_ISDIR(statbuf.st_mode)) {
     return 1;
    } else {
     return 2;
    }
  } else {
    return 0;
  }
  return res;
} // existsPath


/**
 * Creates a directory in the specified path
 */
int FileUtils::createDirectory(string path) {
  int res;
  cout << "Creating directory: " << path << endl;

  if (path.size() > 512)
    res = 1;
  else {
    for (int i = 0; i <= path.size(); i++)
      if (path[i] == '/' || i == path.size()-1) {
        string path2 = path.substr(0, i+1);

        #ifdef WINDOWS
        res = mkdir(path2.c_str());
        #else
        res = mkdir(path2.c_str() , S_IRWXU | S_IRWXG | S_IRWXO);
        #endif

      }
  }
  
  return res;
} // createDirectory
