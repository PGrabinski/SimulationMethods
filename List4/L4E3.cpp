#include <iostream>
#include <gsl/gsl_rng.h>
#include <cmath>
#include <string>

using namespace std;

/*
Generating random numbers from Poisson distribution
P(x=k)=exp(-lambda) lambda^x/x!
using its recursive nature
P(0)=exp(-lambda)
P(k+1)=P(k) lambda/(k+1)
*/

double poissonGen(gsl_rng * r, double lambda){
	double p = exp(-lambda);
	double F = p;
	double u = gsl_rng_uniform(r);
	int i = 0;
	while(true){
			if ( u < F) {
				return i;
			}
			else {
				i++;
				p *= lambda/i;
				F += p;
			}	
	}
}


int main(int argc, char *argv[]){
	if (argc !=2) 
	{
		cout << "Wrong number of parameters!\n";
		return 1;
	}
	else
	{
		gsl_rng_env_setup();
		gsl_rng * r = gsl_rng_alloc(gsl_rng_mt19937);
		
		// Number of generated samples
		int N = 1e6;
		
		string lambda_string = argv[1];
		double lambda = stoi(lambda_string); 
		cout << "X\n";
		for(int i=0; i < N; i++){
			cout << poissonGen(r, lambda) << "\n";
		}	
		return 0;
	}
}
