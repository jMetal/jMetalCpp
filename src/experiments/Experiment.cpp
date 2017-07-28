//  Experiment.cpp
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//       Sérgio Vieira <sergiosvieira@gmail.com>
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


void Experiment::checkExperimentDirectory()
{
    int res = FileUtils::existsPath(experimentBaseDirectory_.c_str());
    switch (res)
    {
    case 0:
        std::cout << "Experiment directory does NOT exist. Creating" << std::endl;
        if (FileUtils::createDirectory(experimentBaseDirectory_) == -1)
        {
            std::cout << "Error creating directory" << std::endl;
            exit(-1);
        }
        break;
    case 1:
        std::cout << "Experiment directory exists." << std::endl;
        std::cout << "Experiment directory is a directory" << std::endl;
        break;
    case 2:
        std::cout << "Experiment directory exists." << std::endl;
        std::cout << "Experiment directory is not a directory. Deleting file and creating directory" << std::endl;
        if( remove(experimentBaseDirectory_.c_str()) != 0 )
        {
            std::cout << "Error deleting file." << std::endl;
            exit(-1);
        }
        else
        {
            std::cout << "File successfully deleted." << std::endl;
        }
        if (FileUtils::createDirectory(experimentBaseDirectory_) == -1)
        {
            std::cout << "Error creating directory" << std::endl;
            exit(-1);
        }
        break;
    case -1:
        std::cout << "Error checking experiment directory" << std::endl;
        exit(-1);
    }
} // checkExperimentDirectory


void Experiment::resetFile(std::string file)
{
    int res = FileUtils::existsPath(file.c_str());
    switch (res)
    {
    case 0:
        std::cout << "File (" << file << ") does NOT exist." << std::endl;
        break;
    case 1:
        std::cout << "File (" << file << ") exists." << std::endl;
        std::cout << "File (" << file << ") is a directory. Deleting directory." << std::endl;
        if( remove(file.c_str()) != 0 )
        {
            std::cout << "Error deleting directory." << std::endl;
            exit(-1);
        }
        else
        {
            std::cout << "Directory successfully deleted." << std::endl;
        }
        break;
    case 2:
        std::cout << "File (" << file << ") exists." << std::endl;
        std::cout << "File (" << file << ") is a file. Deleting file." << std::endl;
        if( remove(file.c_str()) != 0 )
        {
            std::cout << "Error deleting file." << std::endl;
            exit(-1);
        }
        else
        {
            std::cout << "File successfully deleted." << std::endl;
        }
        break;
    case -1:
        std::cout << "Error checking file (" << file << ")" << std::endl;
        exit(-1);
    }
} // resetFile

