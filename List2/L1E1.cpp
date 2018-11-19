#include <iostream>
#include <cmath>
#include <gsl/gsl_rng.h>

using namespace std;


double sinZeroPiHalf(int N) {
  gsl_rng * r = gsl_rng_alloc (gsl_rng_mt19937);

  double sum = 0;
  double sample;
  double error = 0;
  double element = 0;

  for(int i=0; i<N ; i++){
     sample =   gsl_rng_uniform (r);
     element = sin(M_PI_2*sample);
     sum += element;
     error += element * element;
  }
  sum = M_PI_2*sum / N;
  error = M_PI_2*M_PI_2* error / N;
  error = 1 / sqrt(N) * sqrt(error - sum);
  cout << "The first integral: "<< sum << " with statistical error: "<< error << '\n';
  return sum;
}

double secondIntegral(int N) {
  gsl_rng * r = gsl_rng_alloc (gsl_rng_mt19937);

  double sum = 0;
  double sample;
  double error = 0;
  double element = 0;

  for(int i=0; i<N ; i++){
     sample =   gsl_rng_uniform (r);
     double a = 1.64;
     element = exp(-0.5 * (-1 / sample + 1 + a) * (-1 / sample + 1 + a)) / sample /sample;
     sum += element;
     error += element * element;
  }
  sum =  sum / N / sqrt(2*M_PI);
  error =  error / N/ sqrt(2*M_PI)/ sqrt(2*M_PI);
  error = 1 / sqrt(N) * sqrt(error - sum);
  cout << "The first integral: "<< sum << " with statistical error: "<< error << '\n';
  return sum;
}

double expTwoDimensions(int N) {
  gsl_rng * r = gsl_rng_alloc (gsl_rng_mt19937);

  double sum = 0;
  double sampleX;
  double sampleY;
  double error = 0;
  double element = 0;

  for(int i=0; i<N ; i++){
     sampleX =   gsl_rng_uniform (r);
     sampleY =   gsl_rng_uniform (r);
     element = exp((sampleX + sampleY)*(sampleX + sampleY));
     sum += element;
     error += element * element;
  }
  sum = sum / N;
  error =  error / N;
  error = 1 / sqrt(N) * sqrt(error - sum);
  cout << "The first integral: "<< sum << " with statistical error: "<< error << '\n';
  return sum;
}

int main() {
  gsl_rng_env_setup();
  int N = 1;
  for (int i = 0; i<9; i++){
    N *= 10;
    cout << "For N equal: " << N << "(10^" << i+1 << ") " << '\n';
    //Wolfram alpha: 1
    sinZeroPiHalf(N);
    //Wolfram alpha: 0.949497
    secondIntegral(N);
    //Wolfram alpha: 4.89916
    expTwoDimensions(N);
    cout << '\n';
  }
  return 0;
}
