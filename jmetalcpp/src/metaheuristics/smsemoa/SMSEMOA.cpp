//  SMSEMOA.cpp
//
//  Author:
//       Cristian Zambrano V. <cristian_uteq@hotmail.com>
//
//  Copyright (c) 2013 Antonio J. Nebro, Juan J. Durillo
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


#include <SMSEMOA.h>


/*
 * This class implements the MOEA/D algorithm.
 */


/**
 * Constructor
 * @param problem Problem to solve
 */
SMSEMOA::SMSEMOA(Problem *problem) : Algorithm(problem) {
    utils_ = new MetricsUtil();
	hv_ = new Hypervolume();
} // SMSEMOA

/**
 * Destructor
 */
SMSEMOA::~SMSEMOA() {
  delete utils_;  delete hv_;

} // ~Hypervolume


/**
* Runs the SMS-EMOA algorithm.
* @return a <code>SolutionSet</code> that is a set of non dominated solutions
* as a result of the algorithm execution
*/
SolutionSet * SMSEMOA::execute() {
  int populationSize;
  int maxEvaluations;
  int evaluations;
  double offset = 100.0;

  QualityIndicator * indicators; // QualityIndicator object
  int requiredEvaluations; // Use in the example of use of the indicators object (see below)

  SolutionSet * population;
  SolutionSet * offspringPopulation;
  SolutionSet * union_;

  Operator * mutationOperator;
  Operator * crossoverOperator;
  Operator * selectionOperator;

  //Read the parameters
  populationSize = *(int *) getInputParameter("populationSize");
  maxEvaluations = *(int *) getInputParameter("maxEvaluations");
  offset = *(double *) getInputParameter("offset");

  //indicators = (QualityIndicator*) getInputParameter("indicators");


  //Initialize the variables
  population = new SolutionSet(populationSize);
  evaluations = 0;

  requiredEvaluations = 0;

  //Read the operators
  crossoverOperator = operators_["crossover"];
  mutationOperator = operators_["mutation"];
  selectionOperator = operators_["selection"];

  // Create the initial solutionSet
   Solution * newSolution;
   for (int i = 0; i < populationSize; i++) {
      newSolution = new Solution(problem_);
      problem_->evaluate(newSolution);
      problem_->evaluateConstraints(newSolution);
      evaluations++;
      population->add(newSolution);
   } //for

   Solution ** parents;
   Solution ** offSpring;

   // Generations ...
   while (evaluations < maxEvaluations) {

	   // Create the offSpring solutionSet
	   offspringPopulation = new SolutionSet(1);
	   //parents = new Solution*[2];

       /** POR AHORA SE ASUME QUE OPERADOR SELECCION RETORNA DOS SOLUCIONES ***/
	   parents = (Solution **) (selectionOperator->execute(population));

	   //offSpring = new Solution*[2];
	   offSpring = (Solution **) (crossoverOperator->execute(parents));

	   mutationOperator->execute(offSpring[0]);

       problem_->evaluate(offSpring[0]);
	   problem_->evaluateConstraints(offSpring[0]);

	   // insert child into the offspring population
       offspringPopulation->add(offSpring[0]);

       evaluations++;
       cout << "Evaluaciones.... " << evaluations << endl;


       delete offSpring[1];
       //delete[] offSpring; //Borra el vector, los elementos son copia de CRUCE
       //delete[] parents; //Borra el vector, los elementos son Soluciones de Population

       // Create the solutionSet union of solutionSet and offSpring
       union_ = population->join(offspringPopulation);
       delete offspringPopulation;

       // Ranking the union (non-dominated sorting)
       Ranking * ranking = new Ranking(union_);

       // ensure crowding distance values are up to date
       // (may be important for parent selection)
       for (int j = 0; j < population->size(); j++){
          population->get(j)->setCrowdingDistance(0.0);
       }

       cout << "front 0 size: " << ranking->getSubfront(0)->size()  << endl ;

       SolutionSet *lastFront = ranking->getSubfront(ranking->getNumberOfSubfronts() - 1);
       if (lastFront->size() > 1) {

    	   vector <vector<double> > frontValues = lastFront->writeObjectivesToMatrix();
    	   int numberOfObjectives = problem_->getNumberOfObjectives();

           // STEP 1. Obtain the maximum and minimum values of the Pareto front
           vector<double> maximumValues = utils_->getMaximumValues(union_->writeObjectivesToMatrix(), numberOfObjectives);
           vector<double> minimumValues = utils_->getMinimumValues(union_->writeObjectivesToMatrix(), numberOfObjectives);

           // STEP 2. Get the normalized front
           vector <vector<double> > normalizedFront = utils_->getNormalizedFront(frontValues, maximumValues, minimumValues);

           // compute offsets for reference point in normalized space
           vector<double> offsets;
           for (int i = 0; i < maximumValues.size(); i++) {
                 offsets.push_back(offset / (maximumValues[i] - minimumValues[i]));
           }

           
           // STEP 3. Inverse the pareto front. This is needed because the original
           //metric by Zitzler is for maximization problems
           vector <vector<double> > invertedFront = utils_->invertedFront(normalizedFront);
           // shift away from origin, so that boundary points also get a contribution > 0
           for (int i = 0; i < invertedFront.size();i++) {
             for (int j = 0; j < invertedFront[i].size(); j++) {
            	 invertedFront[i][j] = invertedFront[i][j] + offsets[j];
              }
           }
           
            // calculate contributions and sort
           vector<double> contributions = hvContributions(invertedFront);
            for (int i = 0; i < contributions.size(); i++) {
            	// contribution values are used analogously to crowding distance
                lastFront->get(i)->setCrowdingDistance(contributions[i]);
             }

            CrowdingDistanceComparator *cd = new CrowdingDistanceComparator();
			lastFront->sort(cd);
			delete cd;  /************OJO****************/
         }


       // all but the worst are carried over to the survivor population
       SolutionSet *front = NULL;
       for (int i=0;i<population->size();i++) {
          delete population->get(i);
        }
       population->clear();


       for (int i = 0; i < ranking->getNumberOfSubfronts() - 1; i++) {
             front = ranking->getSubfront(i);
             for (int j = 0; j < front->size(); j++)
            	   population->add(new Solution(front->get(j)));

        }
	    for (int i = 0; i < lastFront->size() - 1; i++)
              population->add(new Solution(lastFront->get(i)));


	    delete ranking;
	    delete union_;

	    // This piece of code shows how to use the indicator object into the code
        // of SMS-EMOA. In particular, it finds the number of evaluations required
        // by the algorithm to obtain a Pareto front with a hypervolume higher
        // than the hypervolume of the true Pareto front.
        /*if (indicators != NULL && requiredEvaluations == 0) {
        	double HV = indicators->getHypervolume(population);
            if (HV >= (0.98 * indicators->getTrueParetoFrontHypervolume())) {
            	requiredEvaluations = evaluations;
            } // if
        } // if */

  } //WHILE


   // Return the first non-dominated front
   Ranking *ranking = new Ranking(population);
   SolutionSet * result = new SolutionSet(ranking->getSubfront(0)->size());
   for (int i=0;i<ranking->getSubfront(0)->size();i++) {
       result->add(new Solution(ranking->getSubfront(0)->get(i)));
   }

    
   delete ranking;
   delete population;

   return result;

}

vector<double> SMSEMOA::hvContributions(vector< vector<double> > front){
	 int numberOfObjectives = problem_->getNumberOfObjectives();

	 vector<double> contributions;
	 vector< vector<double> > frontSubset;

	 double hv;

	 vector< vector<double> > frontCopy;
	 vector< vector<double> > totalFront;

 	 for (int i = 0; i < front.size(); i++) {
 		frontCopy.push_back(vector<double>());
 		totalFront.push_back(vector<double>());
	 	for (int j = 0; j < front[i].size(); j++) {
	 		frontCopy[i].push_back(front[i][j]);
	 		totalFront[i].push_back(front[i][j]);
	 	}
	 }
    cout << "3" << endl;
    
    double totalVolume = hv_->calculateHypervolume(&totalFront, totalFront.size(), numberOfObjectives);

    cout << "4" << endl;

	 for (int i = 0; i < front.size(); i++) {

		 vector<double> evaluatedPoint;
		 for (int j = 0; j < frontCopy[i].size(); j++) {
			 evaluatedPoint.push_back(frontCopy[i][j]);
		 }
		 frontCopy.erase(frontCopy.begin() + i);


		 frontSubset.erase( frontSubset.begin(), frontSubset.end() );
		 for (int f = 0; f < frontCopy.size(); f++) {
				frontSubset.push_back(vector<double>());
		 	 	for (int c = 0; c < frontCopy[f].size(); c++) {
		 	 		frontSubset[f].push_back(frontCopy[f][c]);
		 	 	}
		  }

         // STEP4. The hypervolume
		 hv = hv_->calculateHypervolume(&frontSubset, frontSubset.size(), numberOfObjectives);
	     contributions.push_back(totalVolume - hv);

         // put point back position i
	     frontCopy.insert(frontCopy.begin() + i , evaluatedPoint);



	  }
    cout << "5" << endl;

	  return contributions;

}
