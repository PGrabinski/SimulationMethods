#include <iostream>
#include <cmath>
#include <gsl/gsl_rng.h>

using namespace std;

//const double N = 1000000;

double expectN(int N){
  gsl_rng * r = gsl_rng_alloc (gsl_rng_mt19937);
  int counter = 0;
  double sumTemp = 0;
  double sumN = 0;
  for(int i = 0; i<N; i++){
    counter = 0;
    sumTemp = 0;
    while (sumTemp <= 1){
      sumTemp +=  gsl_rng_uniform (r);
      counter++;
    }
    sumN += counter;
  }
  return sumN/N;
}

int main() {
  gsl_rng_env_setup();
  cout << expectN(100) << '\n';
  cout << expectN(10000) << '\n';
  cout << expectN(1000000) << '\n';
  return 0;
}
