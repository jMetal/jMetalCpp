//  ProblemFactory.cpp
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


#include <ProblemFactory.h>


/**
 * Problem factory
 * @param name : Name of the problem
 */
Problem * ProblemFactory::getProblem(char * name) {
  return getProblem(name, 0, NULL);
}


/**
 * Problem factory which uses the same arguments as the main from where
 * is called (minimum two arguments)
 * @param argc : Number of arguments
 * @param argv : Array of arguments
 */
Problem * ProblemFactory::getProblem(int argc, char ** argv) {
  if (argc==2) {
    return getProblem(argv[1], 0, NULL);
  } else if (argc>2) {
    char ** argv2 = new char*[argc-2];
    for (int i=0; i<argc-2; i++) {
      argv2[i] = argv[i+2];
    }
    return getProblem(argv[1], argc-2, argv2);
  } else {
    cerr << "Too few arguments to build a problem.";
    exit(-1);
  }
}


/**
 * Problem factory with some optional parameters to be used to construct the
 * problem
 * @param name : Name of the problem
 * @param argc : Number of parameters
 * @param argv : Array of parameters
 */
Problem * ProblemFactory::getProblem(char * name, int argc, char ** argv) {

  if (strcmp(name, "DTLZ1")==0) { // DTLZ1
    if (argc==0)
      return new DTLZ1("Real");
    else if (argc==1)
      return new DTLZ1(argv[0]);
    else if (argc==2)
      return new DTLZ1(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new DTLZ1(argv[0], atoi(argv[1]), atoi(argv[2]));
    else {
      cerr << "Incorrect number of arguments for DTLZ1 problem." << endl;
      exit(-1);
    }
  }
  else if (strcmp(name, "DTLZ2")==0) { // DTLZ2
    if (argc==0)
      return new DTLZ2("Real");
    else if (argc==1)
      return new DTLZ2(argv[0]);
    else if (argc==2)
      return new DTLZ2(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new DTLZ2(argv[0], atoi(argv[1]), atoi(argv[2]));
    else {
      cerr << "Incorrect number of arguments for DTLZ2 problem." << endl;
      exit(-1);
    }
  }
  else if (strcmp(name, "DTLZ3")==0) { // DTLZ3
    if (argc==0)
      return new DTLZ3("Real");
    else if (argc==1)
      return new DTLZ3(argv[0]);
    else if (argc==2)
      return new DTLZ3(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new DTLZ3(argv[0], atoi(argv[1]), atoi(argv[2]));
    else {
      cerr << "Incorrect number of arguments for DTLZ3 problem." << endl;
      exit(-1);
    }
  }
  else if (strcmp(name, "DTLZ4")==0) { // DTLZ4
    if (argc==0)
      return new DTLZ4("Real");
    else if (argc==1)
      return new DTLZ4(argv[0]);
    else if (argc==2)
      return new DTLZ4(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new DTLZ4(argv[0], atoi(argv[1]), atoi(argv[2]));
    else {
      cerr << "Incorrect number of arguments for DTLZ4 problem." << endl;
      exit(-1);
    }
  }
  else if (strcmp(name, "DTLZ5")==0) { // DTLZ5
    if (argc==0)
      return new DTLZ5("Real");
    else if (argc==1)
      return new DTLZ5(argv[0]);
    else if (argc==2)
      return new DTLZ5(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new DTLZ5(argv[0], atoi(argv[1]), atoi(argv[2]));
    else {
      cerr << "Incorrect number of arguments for DTLZ5 problem." << endl;
      exit(-1);
    }
  }
  else if (strcmp(name, "DTLZ6")==0) { // DTLZ6
    if (argc==0)
      return new DTLZ6("Real");
    else if (argc==1)
      return new DTLZ6(argv[0]);
    else if (argc==2)
      return new DTLZ6(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new DTLZ6(argv[0], atoi(argv[1]), atoi(argv[2]));
    else {
      cerr << "Incorrect number of arguments for DTLZ6 problem." << endl;
      exit(-1);
    }
  }
  else if (strcmp(name, "DTLZ7")==0) { // DTLZ7
    if (argc==0)
      return new DTLZ7("Real");
    else if (argc==1)
      return new DTLZ7(argv[0]);
    else if (argc==2)
      return new DTLZ7(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new DTLZ7(argv[0], atoi(argv[1]), atoi(argv[2]));
    else {
      cerr << "Incorrect number of arguments for DTLZ7 problem." << endl;
      exit(-1);
    }
  }  else if (strcmp(name, "Fonseca")==0) { // Fonseca
    if (argc==0)
      return new Fonseca("Real");
    else if (argc==1)
      return new Fonseca(argv[0]);
    else {
      cerr << "Incorrect number of arguments for Fonseca problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "Griewank")==0) { // Griewank
      if (argc==0)
        return new Griewank("Real");
      else if (argc==1)
        return new Griewank(argv[0]);
      else if (argc==2)
        return new Griewank(argv[0], atoi(argv[1]));
      else {
        cerr << "Incorrect number of arguments for Griewank problem." << endl;
        exit(-1);
      }
  } else if (strcmp(name, "Kursawe")==0) { // Kursawe
    if (argc==0)
      return new Kursawe("Real");
    else if (argc==1)
      return new Kursawe(argv[0]);
    else if (argc==2)
      return new Kursawe(argv[0], atoi(argv[1]));
    else {
      cerr << "Incorrect number of arguments for Kursawe problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "LZ09_F1")==0) { // LZ09_F1
    if (argc==0)
      return new LZ09_F1("Real");
    else if (argc==1)
      return new LZ09_F1(argv[0]);
    else if (argc==2)
      return new LZ09_F1(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new LZ09_F1(argv[0], atoi(argv[1]), atoi(argv[2]));
    else if (argc==4)
      return new LZ09_F1(argv[0], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    else {
      cerr << "Incorrect number of arguments for LZ09_F1 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "LZ09_F2")==0) { // LZ09_F2
    if (argc==0)
      return new LZ09_F2("Real");
    else if (argc==1)
      return new LZ09_F2(argv[0]);
    else if (argc==2)
      return new LZ09_F2(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new LZ09_F2(argv[0], atoi(argv[1]), atoi(argv[2]));
    else if (argc==4)
      return new LZ09_F2(argv[0], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    else {
      cerr << "Incorrect number of arguments for LZ09_F1 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "LZ09_F3")==0) { // LZ09_F3
    if (argc==0)
      return new LZ09_F3("Real");
    else if (argc==1)
      return new LZ09_F3(argv[0]);
    else if (argc==2)
      return new LZ09_F3(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new LZ09_F3(argv[0], atoi(argv[1]), atoi(argv[2]));
    else if (argc==4)
      return new LZ09_F3(argv[0], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    else {
      cerr << "Incorrect number of arguments for LZ09_F1 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "LZ09_F4")==0) { // LZ09_F4
    if (argc==0)
      return new LZ09_F4("Real");
    else if (argc==1)
      return new LZ09_F4(argv[0]);
    else if (argc==2)
      return new LZ09_F4(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new LZ09_F4(argv[0], atoi(argv[1]), atoi(argv[2]));
    else if (argc==4)
      return new LZ09_F4(argv[0], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    else {
      cerr << "Incorrect number of arguments for LZ09_F1 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "LZ09_F5")==0) { // LZ09_F5
    if (argc==0)
      return new LZ09_F5("Real");
    else if (argc==1)
      return new LZ09_F5(argv[0]);
    else if (argc==2)
      return new LZ09_F5(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new LZ09_F5(argv[0], atoi(argv[1]), atoi(argv[2]));
    else if (argc==4)
      return new LZ09_F5(argv[0], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    else {
      cerr << "Incorrect number of arguments for LZ09_F1 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "LZ09_F6")==0) { // LZ09_F6
    if (argc==0)
      return new LZ09_F6("Real");
    else if (argc==1)
      return new LZ09_F6(argv[0]);
    else if (argc==2)
      return new LZ09_F6(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new LZ09_F6(argv[0], atoi(argv[1]), atoi(argv[2]));
    else if (argc==4)
      return new LZ09_F6(argv[0], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    else {
      cerr << "Incorrect number of arguments for LZ09_F1 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "LZ09_F7")==0) { // LZ09_F7
    if (argc==0)
      return new LZ09_F7("Real");
    else if (argc==1)
      return new LZ09_F7(argv[0]);
    else if (argc==2)
      return new LZ09_F7(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new LZ09_F7(argv[0], atoi(argv[1]), atoi(argv[2]));
    else if (argc==4)
      return new LZ09_F7(argv[0], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    else {
      cerr << "Incorrect number of arguments for LZ09_F1 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "LZ09_F8")==0) { // LZ09_F8
    if (argc==0)
      return new LZ09_F8("Real");
    else if (argc==1)
      return new LZ09_F8(argv[0]);
    else if (argc==2)
      return new LZ09_F8(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new LZ09_F8(argv[0], atoi(argv[1]), atoi(argv[2]));
    else if (argc==4)
      return new LZ09_F8(argv[0], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    else {
      cerr << "Incorrect number of arguments for LZ09_F1 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "LZ09_F9")==0) { // LZ09_F9
    if (argc==0)
      return new LZ09_F9("Real");
    else if (argc==1)
      return new LZ09_F9(argv[0]);
    else if (argc==2)
      return new LZ09_F9(argv[0], atoi(argv[1]));
    else if (argc==3)
      return new LZ09_F9(argv[0], atoi(argv[1]), atoi(argv[2]));
    else if (argc==4)
      return new LZ09_F9(argv[0], atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    else {
      cerr << "Incorrect number of arguments for LZ09_F1 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "OneMax")==0) { // OneMax
    if (argc==0)
      return new OneMax(400);
    else if (argc==1)
      return new OneMax(atoi(argv[0]));
    else if (argc==2)
      return new OneMax(atoi(argv[0]), atoi(argv[1]));
    else {
      cerr << "Incorrect number of arguments for OneMax problem." << endl;
      exit(-1);
    }
    
  } else if (strcmp(name, "Rastrigin")==0) { // Rastrigin
    if (argc==0)
      return new Rastrigin("Real");
    else if (argc==1)
      return new Rastrigin(argv[0]);
    else if (argc==2)
      return new Rastrigin(argv[0], atoi(argv[1]));
    else {
      cerr << "Incorrect number of arguments for Rastrigin problem." << endl;
      exit(-1);
    }
    
  } else if (strcmp(name, "Rosenbrock")==0) { // Rosenbrock
    if (argc==0)
      return new Rosenbrock("Real");
    else if (argc==1)
      return new Rosenbrock(argv[0]);
    else if (argc==2)
      return new Rosenbrock(argv[0], atoi(argv[1]));
    else {
      cerr << "Incorrect number of arguments for Rosenbrock problem." << endl;
      exit(-1);
    }

  } else if (strcmp(name, "Schaffer")==0) { // Schaffer
    if (argc==0)
      return new Schaffer("Real");
    else if (argc==1)
      return new Schaffer(argv[0]);
    else {
      cerr << "Incorrect number of arguments for Schaffer problem." << endl;
      exit(-1);
    }

  } else if (strcmp(name, "Sphere")==0) { // Sphere
    if (argc==0)
      return new Sphere("Real");
    else if (argc==1)
      return new Sphere(argv[0]);
    else if (argc==2)
      return new Sphere(argv[0], atoi(argv[1]));
    else {
      cerr << "Incorrect number of arguments for Sphere problem." << endl;
      exit(-1);
    }
    
  } else if (strcmp(name, "Srinivas")==0) { // Srinivas
    if (argc==0)
      return new Srinivas("Real");
    else if (argc==1)
      return new Srinivas(argv[0]);
    else {
      cerr << "Incorrect number of arguments for Srinivas problem." << endl;
      exit(-1);
    }
    
   } else if (strcmp(name, "Tanaka")==0) { // Tanaka
    if (argc==0)
      return new Tanaka("Real");
    else if (argc==1)
      return new Tanaka(argv[0]);
    else {
      cerr << "Incorrect number of arguments for Tanaka problem." << endl;
      exit(-1);
    }

  } else if (strcmp(name, "ZDT1")==0) { // ZDT1
    if (argc==0)
      return new ZDT1("Real");
    else if (argc==1)
      return new ZDT1(argv[0]);
    else if (argc==2)
      return new ZDT1(argv[0], atoi(argv[1]));
    else {
      cerr << "Incorrect number of arguments for ZDT1 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "ZDT2")==0) { // ZDT2
    if (argc==0)
      return new ZDT2("Real");
    else if (argc==1)
      return new ZDT2(argv[0]);
    else if (argc==2)
      return new ZDT2(argv[0], atoi(argv[1]));
    else {
      cerr << "Incorrect number of arguments for ZDT3 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "ZDT3")==0) { // ZDT3
    if (argc==0)
      return new ZDT3("Real");
    else if (argc==1)
      return new ZDT3(argv[0]);
    else if (argc==2)
      return new ZDT3(argv[0], atoi(argv[1]));
    else {
      cerr << "Incorrect number of arguments for ZDT4 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "ZDT4")==0) { // ZDT4
    if (argc==0)
      return new ZDT4("Real");
    else if (argc==1)
      return new ZDT4(argv[0]);
    else if (argc==2)
      return new ZDT4(argv[0], atoi(argv[1]));
    else {
      cerr << "Incorrect number of arguments for ZDT4 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "ZDT5")==0) { // ZDT5
    if (argc==0)
      return new ZDT5("Binary");
    else if (argc==1)
      return new ZDT5(argv[0]);
    else if (argc==2)
      return new ZDT5(argv[0], atoi(argv[1]));
    else {
      cerr << "Incorrect number of arguments for ZDT5 problem." << endl;
      exit(-1);
    }
  } else if (strcmp(name, "ZDT6")==0) { // ZDT6
    if (argc==0)
      return new ZDT6("Real");
    else if (argc==1)
      return new ZDT6(argv[0]);
    else if (argc==2)
      return new ZDT6(argv[0], atoi(argv[1]));
    else {
      cerr << "Incorrect number of arguments for ZDT6 problem." << endl;
      exit(-1);
    }

  } else {

    cerr << "ProblemFactory::getProblem: Problem '" << name
        << "' does not exist. Please, check the problem names "
        << "in jmetalcpp/problems" << endl;
    exit(-1);

  }

}

