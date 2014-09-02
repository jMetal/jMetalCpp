//  MetricsUtil.cpp
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


#include <MetricsUtil.h>


using namespace std;


/**
 * This method reads a Pareto Front for a file.
 * @param path The path to the file that contains the pareto front
 * @return double [][] whit the pareto front
 **/
vector< vector <double> > MetricsUtil::readFront(string path) {

  vector< vector <double> > front;

  std::ifstream in(path.c_str());
  if( !in ) {
    cout << "Error trying to read Pareto Front file: " << path << endl;
    exit(-1);
  }

  string line;
  while( getline(in, line ) ) {

    vector<double> list;

    istringstream iss(line);

    while (iss) {
      string token;
      iss >> token;
      if (token.compare("")!=0) {
        //cout << "Substring: " << token << endl;
        list.push_back(atof(token.c_str()));
      }
    }
    front.push_back(list);

  }

  in.close();

  return front;

} // readFront


/** Gets the maximum values for each objectives in a given pareto
 *  front
 *  @param front The pareto front
 *  @param noObjectives Number of objectives in the pareto front
 *  @return vector<double> A vector of noOjectives values with the maximum values
 *  for each objective
 **/
vector<double> MetricsUtil::getMaximumValues(vector< vector<double> > front,
    int noObjectives) {

  vector<double> maximumValue;

	for (int i = 0; i < noObjectives; i++) {
		maximumValue.push_back(-std::numeric_limits<double>::max());
	}

	for (int i =0; i < front.size(); i++ ) {
		for (int j = 0; j < front[i].size(); j++) {
			if (front[i][j] > maximumValue[j]) {
				maximumValue[j] = front[i][j];
			}
		}
	}

	return maximumValue;

} // getMaximumValues


/** Gets the minimum values for each objectives in a given pareto
 *  front
 *  @param front The pareto front
 *  @param noObjectives Number of objectives in the pareto front
 *  @return vector<double> A vector of noOjectives values with the minimum values
 *  for each objective
 **/
vector<double> MetricsUtil::getMinimumValues(vector< vector<double> > front,
    int noObjectives) {

  vector<double> minimumValue;

  for (int i = 0; i < noObjectives; i++) {
    minimumValue.push_back(std::numeric_limits<double>::max());
  }

  for (int i =0; i < front.size(); i++ ) {
    for (int j = 0; j < front[i].size(); j++) {
      if (front[i][j] < minimumValue[j]) {
        minimumValue[j] = front[i][j];
      }
    }
  }

  return minimumValue;

} // getMinimumValues


/**
 *  This method returns the distance (taken the euclidean distance) between
 *  two points given as <code>double []</code>
 *  @param a A point
 *  @param b A point
 *  @return The euclidean distance between the points
 **/
double MetricsUtil::distance(vector<double> a, vector<double> b) {

  double distance = 0.0;

  for (int i = 0; i < a.size(); i++) {
    distance += pow(a[i]-b[i],2.0);
  }

  return sqrt(distance);
} // distance


/**
 * Gets the distance between a point and the nearest one in
 * a given front (the front is given as <code>vector< vector<double> ></code>)
 * @param point The point
 * @param front The front that contains the other points to calculate the
 * distances
 * @return The minimum distance between the point and the front
 **/
double MetricsUtil::distanceToClosedPoint(vector<double> point,
    vector< vector<double> > front) {

  double minDistance = distance(point,front[0]);

  for (int i = 1; i < front.size(); i++) {
    double aux = distance(point,front[i]);
    if (aux < minDistance) {
      minDistance = aux;
    }
  }

  return minDistance;

} // distanceToClosedPoint


/**
 * Gets the distance between a point and the nearest one in
 * a given front, and this distance is greater than 0.0
 * @param point The point
 * @param front The front that contains the other points to calculate the
 * distances
 * @return The minimun distances greater than zero between the point and
 * the front
 */
double MetricsUtil::distanceToNearestPoint(vector<double> point,
    vector< vector<double> > front) {

  double minDistance = std::numeric_limits<double>::max();

  for (int i = 0; i < front.size(); i++) {
    double aux = distance(point,front[i]);
    if ((aux < minDistance) && (aux > 0.0)) {
      minDistance = aux;
    }
  }

  return minDistance;

} // distanceToNearestPoint


/**
 * This method receives a pareto front and two points, one with maximum values
 * and the other with minimum values allowed, and returns the normalized
 * pareto front.
 * @param front A pareto front.
 * @param maximumValue The maximum values allowed
 * @param minimumValue The minimum values allowed
 * @return the normalized pareto front
 **/
vector< vector<double> > MetricsUtil::getNormalizedFront(vector< vector<double> > front,
    vector<double> maximumValue, vector<double> minimumValue) {

  vector< vector<double> > normalizedFront;

  for (int i = 0; i < front.size();i++) {
    vector<double> list;
    for (int j = 0; j < front[i].size(); j++) {
      //normalizedFront[i][j] = (front[i][j] - minimumValue[j]) /
      //                        (maximumValue[j] - minimumValue[j]);
      list.push_back((front[i][j] - minimumValue[j]) / (maximumValue[j] - minimumValue[j]));
    }
    normalizedFront.push_back(list);
  }

  return normalizedFront;

} // getNormalizedFront


/**
 * This method receives a normalized pareto front and return the inverted one.
 * This operation needed for minimization problems
 * @param front The pareto front to inverse
 * @return The inverted pareto front
 **/
vector< vector<double> > MetricsUtil::invertedFront(vector< vector<double> > front) {

	vector< vector<double> > invertedFront;

	for (int i = 0; i < front.size(); i++) {
		vector<double> list;
		for (int j = 0; j < front[i].size(); j++) {
			if (front[i][j] <= 1.0 && front[i][j]>= 0.0) {
				list.push_back(1.0 - front[i][j]);
			} else if (front[i][j] > 1.0) {
			  list.push_back(0.0);
			} else if (front[i][j] < 0.0) {
			  list.push_back(1.0);
			}
		}
		invertedFront.push_back(list);
	}

	return invertedFront;

} // invertedFront


/**
 * Reads a set of non dominated solutions from a file
 * @param path The path of the file containing the data
 * @return A solution set
 */
SolutionSet * MetricsUtil::readNonDominatedSolutionSet(string path) {

  std::ifstream in(path.c_str());
  if( !in ) {
    cout << "Error trying to read non dominated solutions file: "
        << path << endl;
    exit(-1);
  } // if

  NonDominatedSolutionList * solutionSet = new NonDominatedSolutionList();
  string line;

  while( getline(in, line ) ) {

    vector<double> list;
    istringstream iss(line);
    while (iss) {
      string token;
      iss >> token;
      if (token.compare("")!=0) {
        //cout << "Substring: " << token << endl;
        list.push_back(atof(token.c_str()));
      } // if
    } // while

    Solution * solution = new Solution(list.size());
    for (int i=0; i<list.size(); i++) {
      solution->setObjective(i,list[i]);
    } //for
    solutionSet->add(solution);

  } // while

  in.close();
  return solutionSet;

} // readNonDominatedSolutionSet


/**
 * Reads a set of non dominated solutions from a file
 * and store it in a existing non dominated solution set
 * @param path The path of the file containing the data
 * @return A solution set
 */
void MetricsUtil::readNonDominatedSolutionSet(string path, NonDominatedSolutionList * solutionSet) {

  std::ifstream in(path.c_str());
  if( !in ) {
    cout << "Error trying to read non dominated solutions file: "
        << path << endl;
    exit(-1);
  } // if

  string line;

  while( getline(in, line ) ) {

    vector<double> list;
    istringstream iss(line);
    while (iss) {
      string token;
      iss >> token;
      if (token.compare("")!=0) {
        //cout << "Substring: " << token << endl;
        list.push_back(atof(token.c_str()));
      } // if
    } // while

    Solution * solution = new Solution(list.size());
    for (int i=0; i<list.size(); i++) {
      solution->setObjective(i,list[i]);
    } //for
    solutionSet->add(solution);

  } // while

  in.close();

} // readNonDominatedSolutionSet
