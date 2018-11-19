#include <iostream>
#include <cmath>
#include <gsl/gsl_rng.h>
#include <stdio.h>

#include "wolfer.h"

// Controls temperature change in the lattice
void temperatureFlow(double initialTemperature, double finalTemperature, double stepTemperature, int samplesNumber, gsl_rng * r){
  Wolfer wolfer = Wolfer(samplesNumber, r);
  for (double currentTemperature = initialTemperature; currentTemperature <= finalTemperature; currentTemperature += stepTemperature) {
    wolfer.timeControl(currentTemperature);
  }
}

int main() {
  gsl_rng_env_setup();

  const double criticalTemperature = 2.269185;
  const double epsilon = 0.05;
  const double minTemperature = epsilon;
  const double maxTemperature = criticalTemperature * 2;
  const int samplesNumber = 100;

  temperatureFlow(minTemperature, maxTemperature, epsilon, samplesNumber, gsl_rng_alloc(gsl_rng_ranlxs0));

  return 0;
}
