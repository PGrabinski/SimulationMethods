#include <iostream>
#include <cmath>
#include <gsl/gsl_rng.h>

using namespace std;

const double N = 1000000;

double cov1() {
  gsl_rng * rs = gsl_rng_alloc (gsl_rng_mt19937);
  gsl_rng * r = gsl_rng_alloc (gsl_rng_mt19937);
  gsl_rng * s = gsl_rng_alloc (gsl_rng_mt19937);

  double expU1U = 0;
  double expU = 0;
  double exp1U = 0;
  double sampleU;
  double sample1U;
  double sampleU1U;

  for(int i=0; i<N ; i++) {
     sampleU1U =  gsl_rng_uniform (rs);
     sampleU =  gsl_rng_uniform (r);
     sample1U =  gsl_rng_uniform (s);
     expU1U += sampleU1U * sqrt(1- sampleU1U*sampleU1U);
     expU += sampleU;
     exp1U += sqrt(1- sample1U*sample1U);
  }
  expU = expU / N;
  exp1U = exp1U / N;
  expU1U = expU1U / N;

  double U1U = expU1U - expU *exp1U;
  cout << "Covariance of the U^2 and sqrt(1-U^2) is equal to: " << U1U << " with E(U): " << expU << " and E(sqrt(1-U^2)):" << exp1U << "\n";
  return U1U;
}

double cov2() {
  gsl_rng * rs = gsl_rng_alloc (gsl_rng_mt19937);
  gsl_rng * r = gsl_rng_alloc (gsl_rng_mt19937);
  gsl_rng * s = gsl_rng_alloc (gsl_rng_mt19937);

  double expU1U = 0;
  double expU = 0;
  double exp1U = 0;
  double sampleU;
  double sample1U;
  double sampleU1U;

  for(int i=0; i<N ; i++) {
     sampleU1U =  gsl_rng_uniform (rs);
     sampleU =  gsl_rng_uniform (r);
     sample1U =  gsl_rng_uniform (s);
     expU1U += sampleU1U * sampleU1U * sqrt(1- sampleU1U*sampleU1U);
     expU += sampleU * sampleU;
     exp1U += sqrt(1- sample1U*sample1U);
  }
  expU = expU / N;
  exp1U = exp1U / N;
  expU1U = expU1U / N;

  double U1U = expU1U - expU *exp1U;
  cout << "Covariance of the U^2 and sqrt(1-U^2) is equal to: " << U1U << " with E(U^2): " << expU << " and E(sqrt(1-U^2)):" << exp1U << "\n";
  return U1U;
}

int main() {
  gsl_rng_env_setup();
  cov1();
  cov2();
  return 0;
}
