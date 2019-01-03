#include <iostream>
#include <cmath>
#include <gsl/gsl_rng.h>

using namespace std;

double sinZeroPiHalf(int N, gsl_rng *r) {
  /* Integral of sin(x) from 0 to pi/2.
    @params: N - number of samples,
      r - rng
  */

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
  cout << "The sin(x) integral on [0,pi/2]: "<< sum << " with statistical error: "<< error << '\n';
  return sum;
}

double gaussianZero164(int N, gsl_rng *r) {
  /* Integral of 1/sqrt(2*pi)*exp(-0.5*x^2) from 0 to 1.64.
    @params: N - number of samples,
      r - rng
  */

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
  cout << "The 1/sqrt(2*pi)*exp(-0.5*x^2) integral on [0,1.64]: "<< sum << " with statistical error: "<< error << '\n';
  return sum;
}

double expXYZeroOne(int N, gsl_rng *r) {
  /* Integral of exp((x+y)^2) on [0,1]^2.
    @params: N - number of samples,
      r - rng
  */

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
  cout << "The exp((x+y)^2) integral on [0,1]^2: "<< sum << " with statistical error: "<< error << '\n';
  return sum;
}

int main() {
  gsl_rng_env_setup();
  int N = 1;
  gsl_rng * r = gsl_rng_alloc (gsl_rng_mt19937);
  cout << "Expected values:\n";
  cout << "The sin(x) integral on [0,pi/2] by WolframAlpha: 1\n";
  cout << "The 1/sqrt(2*pi)*exp(-0.5*x^2) integral on [0,1.64]: by WolframAlpha: 0.949497\n";
  cout << "The exp((x+y)^2) integral on [0,1]^2 by WolframAlpha: 4.89916\n";
  for (int i = 0; i<9; i++){
    N *= 10;
    cout << "For N equal: " << N << "(10^" << i+1 << ") " << '\n';
    //Wolfram alpha: 1
    sinZeroPiHalf(N, r);
    
    //Wolfram alpha: 0.949497
    gaussianZero164(N, r);
    
    //Wolfram alpha: 4.89916
    expXYZeroOne(N, r);
    cout << '\n';
  }
  return 0;
}
