#include <iostream>
#include <gsl/gsl_rng.h>
#include <cmath>

using namespace std;

/*
Generating random numbers form cosine distribution
by the inverse cummulative distribution method.
*/

int main(){
	gsl_rng_env_setup();
	gsl_rng * r = gsl_rng_alloc(gsl_rng_mt19937);
	
	// Number of generated samples
	int N = 1e6;

	cout << "Theta\n";
	for(int i=0; i < N; i++){
		cout << asin(2 * gsl_rng_uniform(r) - 1) << "\n";
	}	
	return 0;
}
