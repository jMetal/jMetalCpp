/**
  * @file PolynomialMutation.cpp
  * @author Juan J. Durillo
  * @author Antonio J. Nebro
  * @author Esteban López
  * @date 01 December 2011
**/


#include <PolynomialMutation.h>


const double PolynomialMutation::ETA_M_DEFAULT_ = 20.0;
const double PolynomialMutation::eta_m_ = ETA_M_DEFAULT_;


/**
 * Constructor
 * Creates a new instance of the polynomial mutation operator
 */
PolynomialMutation::PolynomialMutation(map<string, void *> parameters)
: Mutation(parameters) {
	// TODO: mutationProbability_ = NULL;
	distributionIndex_ = eta_m_;
	if (parameters["probability"] != NULL)
		mutationProbability_ = *(double *) parameters["probability"];
	if (parameters["distributionIndex"] != NULL)
		distributionIndex_ = *(double *) parameters["distributionIndex"];
} // PolynomialMutation


/**
 * Destructor
 */
PolynomialMutation::~PolynomialMutation() { } // ~PolynomialMutation


/**
 * Perform the mutation operation
 * @param probability Mutation probability
 * @param solution The solution to mutate
 */
void * PolynomialMutation::doMutation(double probability, Solution *solution) {        
	double rnd, delta1, delta2, mut_pow, deltaq;
	double y, yl, yu, val, xy;
	XReal * x = new XReal(solution);
    
	for (int var=0; var < solution->getNumberOfVariables(); var++) {
		if (PseudoRandom::randDouble() <= probability) {
			y  = x->getValue(var);
			yl = x->getLowerBound(var);
			yu = x->getUpperBound(var);
			delta1 = (y-yl)/(yu-yl);
			delta2 = (yu-y)/(yu-yl);
			rnd = PseudoRandom::randDouble();
			mut_pow = 1.0/(eta_m_+1.0);
			if (rnd <= 0.5)	{
				xy     = 1.0-delta1;
				val    = 2.0*rnd+(1.0-2.0*rnd)*(pow(xy,(eta_m_+1.0)));
				deltaq = pow(val,mut_pow) - 1.0;
			}	else {
				xy     = 1.0-delta2;
				val    = 2.0*(1.0-rnd)+2.0*(rnd-0.5)*(pow(xy,(eta_m_+1.0)));
				deltaq = 1.0 - (pow(val,mut_pow));
			}
			y = y + deltaq*(yu-yl);
			if (y<yl)
				y = yl;
			if (y>yu)
				y = yu;
			x->setValue(var, y);
		}
	} // for

	delete x;

} // doMutation


/**
 * Executes the operation
 * @param object An object containing a solution
 * @return An object containing the mutated solution
 * @throws JMException 
 */  
void * PolynomialMutation::execute(void *object) {
	Solution *solution = (Solution *)object;
	// TODO: VALID_TYPES?
	//double probability = *(double *)getParameter("probability");
	doMutation(mutationProbability_,solution);
	return solution;      
} // execute
