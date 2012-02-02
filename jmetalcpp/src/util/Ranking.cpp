/**
 * @file Ranking.cpp
 * @author Juan J. Durillo
 * @author Esteban López Camacho
 * @version 1.0
 * @date 01 December 2011
 */


#include <Ranking.h>


/**
 * This class implements some facilities for ranking solutions.
 * Given a <code>SolutionSet</code> object, their solutions are ranked
 * according to scheme proposed in NSGA-II; as a result, a set of subsets
 * are obtained. The subsets are numbered starting from 0 (in NSGA-II, the
 * numbering starts from 1); thus, subset 0 contains the non-dominated
 * solutions, subset 1 contains the non-dominated solutions after removing those
 * belonging to subset 0, and so on.
 */


/**
 * Constructor.
 * @param solutionSet The <code>SolutionSet</code> to be ranked.
 */
Ranking::Ranking (SolutionSet * solutionSet) {
	
	solutionSet_ = solutionSet;
	dominance_   = new DominanceComparator();
	constraint_  = new OverallConstraintViolationComparator();

  // dominateMe[i] contains the number of solutions dominating i        
  int * dominateMe = new int[solutionSet_->size()];
    
  if (dominateMe == NULL) {
    cout << "Fatal Problem: Cannot reserve memory in class Ranking" << endl;
    exit(-1);
  }

  // iDominate[k] contains the list of solutions dominated by k
  vector<int> * iDominate = new vector<int>[solutionSet_->size()];

  // front[i] contains the list of individuals belonging to the front i
  vector<int> * front = new vector<int>[solutionSet_->size()+1];
        
  // flagDominate is an auxiliar variable
  int flagDominate;    

	// Initialize the fronts
	//for (int i = 0; i < front.length; i++)
	//  front[i] = new LinkedList<Integer>();
        
  //-> Fast non dominated sorting algorithm
  for (int p = 0; p < solutionSet_->size(); p++) {
		dominateMe[p] = 0;
		// For all q individuals , calculate if p dominates q or vice versa
		for (int q = 0; q < solutionSet_->size(); q++) {

      flagDominate =constraint_->compare(solutionSet->get(p),solutionSet->get(q));
//      cout << "Ranking: flagDominate = " << flagDominate << endl;
//      cout << "Ranking: solutionSet->get(p)->getOverallConstraintViolation() = " << solutionSet->get(p)->getOverallConstraintViolation() << endl;
//      cout << "Ranking: solutionSet->get(q)->getOverallConstraintViolation() = " << solutionSet->get(q)->getOverallConstraintViolation() << endl;
      if (flagDominate == 0) {
        flagDominate =dominance_->compare(solutionSet->get(p),solutionSet->get(q));
      } // if
//      cout << "Ranking: new flagDominate = " << flagDominate << endl;

      if (flagDominate == -1) {
        iDominate[p].push_back(q);
      } else if (flagDominate == 1) {
      	dominateMe[p]++;
      } // if

		} // for
            
    // If nobody dominates p, p belongs to the first front
    if (dominateMe[p] == 0) {
    	front[0].push_back(p);
      solutionSet_->get(p)->setRank(0);
    } // if

  } // for
  
//  cout << "Ranking: front[0].size() = " << front[0].size() << endl;
//  cout << "Ranking: front[0][0] = " << front[0][0] << endl;
//  cout << "Ranking: front[1].size() = " << front[1].size() << endl;
  //cout << "Rank: iDominate.size() = " << iDominate.size() << endl;

	// Obtain the rest of fronts
	int i = 0;
	vector<int>::iterator it1, it2;
	while (front[i].size()!=0) {
//		cout << "Ranking: front[" << i << "].size() distinto de cero" << endl;
		i++;
		for (it1=front[i-1].begin(); it1<front[i-1].end(); it1++) {
//			cout << "Ranking: Valor de *it1 = " << *it1 << endl;
//			cout << "Rank: iDominate[" << *it1 << "].size() = " << iDominate[*it1].size() << endl;
			for (it2=iDominate[*it1].begin(); it2 < iDominate[*it1].end();it2++) {
//				cout << "Ranking: Valor de *it2 = " << *it2 << endl;
				dominateMe[*it2]--;
//				cout << "Ranking: Valor de dominateMe[*it2] = " << dominateMe[*it2] << endl;
				if (dominateMe[*it2]==0) {
					front[i].push_back(*it2);
					solutionSet->get(*it2)->setRank(i);
//					cout << "Ranking: Tamaño de front[i] = " << front[i].size() << endl;
				} // if
			} // for
		} // for
	} // while

//	cout << "Ranking: front[" << i << "].size() igual a cero" << endl;
//	cout << "Ranking: Creando ranking con tamaño " << i << endl;
        
	ranking_ = new SolutionSet*[i];
	if (ranking_ == NULL) {
		cout << "Fatal Error: Impossible to reserve memory in Ranking" << endl;
		exit(-1);
	}
    
  //0,1,2,....,i-1 are front, then i fronts
    
  numberOfSubfronts_ = i;

	// Pintar la forntera 0
	//cout << "la frontera 0 es : ";
	//for (it1=front[0].begin(); it1<front[0].end(); it1++) {
	//  	cout << " " << solutionSet_->get(*it1)->getObjective(0) << " " << solutionSet_->get(*it1)->getObjective(1) << endl;
	//}
    
	for (int j = 0; j < i; j++) {
		ranking_[j] = new SolutionSet(front[j].size());
		for (it1=front[j].begin(); it1<front[j].end(); it1++) {
			ranking_[j]->add(solutionSet_->get(*it1));
		} // for
	} // for

} // Ranking


/**
 * Returns a <code>SolutionSet</code> containing the solutions of a given rank.
 * @param rank The rank
 * @return Object representing the <code>SolutionSet</code>.
 */
SolutionSet * Ranking::getSubfront(int rank) {
	return ranking_[rank];
} // getSubFront


/**
 * Returns the total number of subFronts founds.
 */
int Ranking::getNumberOfSubfronts() {
	return numberOfSubfronts_;
}



