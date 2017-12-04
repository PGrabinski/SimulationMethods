#include <iostream>
#include <cmath>
#include <gsl/gsl_rng.h>

using namespace std;
const double e3 = exp(-3);
const int inf = 20;

double expectN(int N){
  gsl_rng * r = gsl_rng_alloc (gsl_rng_mt19937);
  int counter = 0;
  int counters[inf];
  int rest = 0;
  double productTemp = 0;
  double productN = 0;
  for(int i = 0; i<N; i++){
    counter = 0;
    productTemp = 0;
    while (productTemp > e3){
      productTemp *=  gsl_rng_uniform (r);
      counter++;
    }
    productN += counter;
    if(counter < inf) {
		counters[counter]++;
	} else {
		rest++;
	}
  }
  for(int i=1; i < inf; i++) {
    cout << "For N= " << i << " the probability is: " << (counters[i]/ N) << "\n";
  }
	cout << "For N>=100 the probability is: " << (rest/N) << "\n";

  return productN/N;
}


int main() {
  gsl_rng_env_setup();
  cout << expectN(1000);
  return 0;
}
