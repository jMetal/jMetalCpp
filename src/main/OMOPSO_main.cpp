//  OMOPSO_main.cpp
//
//  Author:
//       Esteban López-Camacho <esteban@lcc.uma.es>
//       Sérgio Vieira <sergiosvieira@gmail.com>
//
//  Copyright (c) 2014 Antonio J. Nebro
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

#include <Algorithm.h>
#include <Problem.h>
#include <Operator.h>
#include <Solution.h>

#include <OMOPSO.h>

#include <NonUniformMutation.h>
#include <ProblemFactory.h>
#include <QualityIndicator.h>
#include <UniformMutation.h>

#include <iostream>
#include <time.h>

/**
 * Method for configuring and running the OMOPSO algorithm
 */
int main(int argc, char ** argv)
{

    clock_t t_ini, t_fin;

    Problem   *problem;   // The problem to solve
    Algorithm *algorithm; // The algorithm to use
    Mutation  *uniformMutation;
    Mutation  *nonUniformMutation;

    QualityIndicator *indicators ; // Object to get quality indicators

   std::map<std::string, void *> parameters; // Operator parameters

    indicators = nullptr;

    if (argc>=2)
    {
        problem = ProblemFactory::getProblem(argc, argv);
        std::cout << "Selected problem: " << problem->getName() << std::endl;
    }
    else
    {
        std::cout << "No problem selected." << std::endl;
        std::cout << "Default problem will be used: Kursawe" << std::endl;
        problem = ProblemFactory::getProblem(const_cast<char *>("Kursawe"));
    }

    algorithm = snew OMOPSO(problem);

    int maxIterations = 250;
    double perturbationIndex = 0.5;
    double mutationProbability = 1.0/problem->getNumberOfVariables();
    int swarmSize = 100;
    int archiveSize = 100;

    // Algorithm parameters
    algorithm->setInputParameter("swarmSize",&swarmSize);
    algorithm->setInputParameter("archiveSize",&archiveSize);
    algorithm->setInputParameter("maxIterations",&maxIterations);

    parameters["probability"] =  &mutationProbability;
    parameters["perturbation"] = &perturbationIndex;
    uniformMutation = snew UniformMutation(parameters);

    parameters.clear();
    parameters["probability"] =  &mutationProbability;
    parameters["perturbation"] =  &perturbationIndex;
    parameters["maxIterations"] = &maxIterations;
    nonUniformMutation = snew NonUniformMutation(parameters);


    // Add the operators to the algorithm
    algorithm->addOperator("uniformMutation",uniformMutation);
    algorithm->addOperator("nonUniformMutation",nonUniformMutation);

    // Execute the Algorithm
    t_ini = clock();
    SolutionSet * population = algorithm->execute();
    t_fin = clock();
    double secs = (double) (t_fin - t_ini);
    secs = secs / CLOCKS_PER_SEC;

    // Print the results
    std::cout << "Total execution time: " << secs << "s" << std::endl;
    std::cout << "Variables values have been written to file VAR" << std::endl;
    population->printVariablesToFile("VAR");
    std::cout << "Objectives values have been written to file FUN" << std::endl;
    population->printObjectivesToFile("FUN");

    if (indicators != nullptr)
    {
        std::cout << "Quality indicators" << std::endl ;
        std::cout << "Hypervolume: " << indicators->getHypervolume(population) << std::endl;
        std::cout << "GD         : " << indicators->getGD(population) << std::endl ;
        std::cout << "IGD        : " << indicators->getIGD(population) << std::endl ;
        std::cout << "Spread     : " << indicators->getSpread(population) << std::endl ;
        std::cout << "Epsilon    : " << indicators->getEpsilon(population) << std::endl ;
    } // if

    delete uniformMutation;
    delete nonUniformMutation;
    delete population;
    delete algorithm;

} // main
