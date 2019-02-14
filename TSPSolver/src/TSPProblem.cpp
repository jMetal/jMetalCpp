/*
 * TSPProblem.cpp
 *
 *  Created on: 26 Jan 2019
 *      Author: Emad Alharbi
 */

#include "TSPProblem.h"
#include "math.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>

#undef M_PI
#define M_PI 3.14159265358979323846264
typedef std::numeric_limits< double > dbl;

/*
int geom_edgelen (unsigned long long i, unsigned long long j, CCdatagroup *dat)
{
double lati, latj, longi, longj;
double q1, q2, q3, q4, q5;

lati = M_PI * dat->x[i] / 180.0;
latj = M_PI * dat->x[j] / 180.0;

longi = M_PI * dat->y[i] / 180.0;
longj = M_PI * dat->y[j] / 180.0;

//lati = M_PI * -77.5100 / 180.0;		for testing fixed values
//latj = M_PI * -77.5000 / 180.0;

//longi = M_PI * 166.4000 / 180.0;
//longj = M_PI * 166.4100 / 180.0;

q1 = cos (latj) * sin(longi - longj);
q3 = sin((longi - longj)/2.0);
q4 = cos((longi - longj)/2.0);
q2 = sin(lati + latj) * q3 * q3 - sin(lati - latj) * q4 * q4;
q5 = cos(lati - latj) * q4 * q4 - cos(lati + latj) * q3 * q3;
return (unsigned long long) (6378388.0 * atan2(sqrt(q1*q1 + q2*q2), q5) + 1.0) / 100.0;
}
*/
int EUC_2D (int i, int j, CCdatagroup *dat){
	double xd = dat->x[i] - dat->x[j];
	double yd = dat->y[i] - dat->y [j];
	return ( sqrt( xd*xd + yd*yd) ) + 0.5;
}
int geom_edgelen (int i, int j, CCdatagroup *dat)
{
     double lati, latj, longi, longj;
     double q1, q2, q3, q4, q5;

     lati = M_PI * dat->x[i] / 180.0;
     latj = M_PI * dat->x[j] / 180.0;

     longi = M_PI * dat->y[i] / 180.0;
     longj = M_PI * dat->y[j] / 180.0;

     q1 = cos (latj) * sin(longi - longj);
     q3 = sin((longi - longj)/2.0);
     q4 = cos((longi - longj)/2.0);
     q2 = sin(lati + latj) * q3 * q3 - sin(lati - latj) * q4 * q4;
     q5 = cos(lati - latj) * q4 * q4 - cos(lati + latj) * q3 * q3;
     return (int) (6378388.0 * atan2(sqrt(q1*q1 + q2*q2), q5) + 1.0);
}
//This code from http://www.cse.unt.edu/~garlick/teaching/4310/TSP.cpp
void fillGPSData (CCdatagroup* filldat) {

	string line;
	ifstream myfile ("world.tsp");
	unsigned long long index = 1;

	if (myfile.is_open())
	{
		// read and discard the header in world.tsp
		for (int zz = 1; zz < 8; zz++) {
		    getline (myfile,line);
		}

		while (! myfile.eof() )
		{

			if (index % 100000 == 0) cout << ".";



			getline (myfile,line);

			string buf; // Have a buffer string
			stringstream ss(line); // Insert the string into a stream

			ss >> buf;		// read and discard the city number - it is encoded in the array index.
			ss >> buf;
			filldat->x[index] = strtod(buf.c_str(), NULL);
			ss >> buf;
			filldat->y[index] = strtod(buf.c_str(), NULL);
			index++;

		}

		myfile.close();

	}
	else cout << "Unable to open file";
	cout << endl;

}
// End of the code from http://www.cse.unt.edu/~garlick/teaching/4310/TSP.cpp


TSPProblem::TSPProblem() {
	// TODO Auto-generated constructor stub
	CCdatagroup *tspdata = new CCdatagroup();
	fillGPSData(tspdata);
	TSPDATA=tspdata;
	//for (int i = 1; i < (sizeof(tspdata->x)/sizeof(*tspdata->x)); i++){

		//for (int b = 1; b < (sizeof(tspdata->x)/sizeof(*tspdata->x)); b++){
			//std::cout << "From "<< i  << " b "<< b <<" "<< EUC_2D(i,b,TSPDATA) << std::endl;

		//}
	//}

	numberOfVariables_   = (sizeof(tspdata->x)/sizeof(*tspdata->x))-1;
	std::cout << "numberOfVariables_ "<<numberOfVariables_ << std::endl;
	numberOfObjectives_  = 1;
	numberOfConstraints_ = 0;
	problemName_ 				 = "TSP";
	lowerLimit_ = new double[(sizeof(tspdata->x)/sizeof(*tspdata->x))-1];
	upperLimit_ = new double[(sizeof(tspdata->x)/sizeof(*tspdata->x))-1];

	for (int i = 0; i < (sizeof(tspdata->x)/sizeof(*tspdata->x))-1; i++) {
		    	lowerLimit_[i] = 1;
		    	upperLimit_[i] =  (sizeof(tspdata->x)/sizeof(*tspdata->x))-1 ;
	}
		//solutionType_ = new RealSolutionType(this);
		solutionType_ = new IntNoneRepeatedSolutionType(this);

}

TSPProblem::~TSPProblem() {
	// TODO Auto-generated destructor stub
	delete [] lowerLimit_ ;
	delete [] upperLimit_ ;
	delete solutionType_ ;
}
void TSPProblem::evaluate(Solution * solution) {

	Variable **variables = solution->getDecisionVariables();
	cout.precision(dbl::max_digits10);
	//	std::cout << solution->getType() << std::endl ;
	int cost=0;



	for (int i = 0; i < numberOfVariables_; i++){


		if(i+1 < numberOfVariables_)
	    cost+=geom_edgelen(variables[i]->getValue(),variables[i+1]->getValue(),TSPDATA);

	}
	cost+=geom_edgelen(variables[numberOfVariables_-1]->getValue(),variables[0]->getValue(),TSPDATA);

	solution->setObjective(0,cost);

}
