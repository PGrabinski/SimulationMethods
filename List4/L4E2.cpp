#include <iostream>
#include <gsl/gsl_rng.h>
#include <cmath>

using namespace std;
/*
Using the elimination method, we generate random numbers from the Maxwell-Boltzmann Distribution f(v).
We use the exponential distribution g_lambda(x) as a helper distribution.
The ELIMINATION_C constant was derived asc=min_x f(x)/g_lambda(x)
and the lambda is chosen in order to minimize the c constant.

A change of variables was performed, in order to obtain a dimensionless variable.
To retrieve the real physical features, we multiply the resulting numbers by the appropiate factor. 
*/
const double ELIMINATION_C = 40.23;

const double LAMBDA = 0.8165;

const double LOG_LAMBDA = log(LAMBDA);

const double BOLTZMAN_K = 1.38064852e-23;

const double B = 4/sqrt(M_PI)/LAMBDA/ELIMINATION_C;

// Generates numbers form the exponential distribution by the inverse cummulative distribution method.
double rng_exponential(gsl_rng * r){
    return -log(gsl_rng_uniform_pos(r))/LAMBDA;
}

// Computes the probablility treshold f(x)/g_lambda(x)/c.
double acceptance_prob(double x){
    return B*pow(x,2)*exp(-pow(x,2)+LAMBDA*x);
}

// Generates the Maxwell-Boltzman random variable values with the mentioned elimination method.
// The constant A is used as the factor to retrieve the physical meaning of the variable.
double rng_elimination_boltzman(gsl_rng * r, double A){
    double u;
    double y;
    while(true){
        u = gsl_rng_uniform(r);
        y = rng_exponential(r);
        if(u <= acceptance_prob(y)){
            return y * A;
        }
    }
}

int main(){
    // Set up Mersenne-Twister rng.
	gsl_rng_env_setup();
	gsl_rng * r = gsl_rng_alloc(gsl_rng_mt19937);
	
	// Number of generated samples
	int N = 1e6;
    // Mass of the particles considered in the distribution
    double m = 2*2.6566962e-26;
    // Temperature of the gas
    double T = 300;
    // The physical factor
    double A = sqrt((2*BOLTZMAN_K*T)/m);

	cout << "X\n";
	for(int i=0; i < N; i++){
		cout << rng_elimination_boltzman(r, A) << "\n";
	}

	return 0;
}
