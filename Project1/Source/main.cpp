#include <iostream>
#include <cmath>
#include <gsl/gsl_rng.h>
#include <stdio.h>
#include <string>

#include "wolfer.h"

// Controls temperature change in the lattice
void temperatureFlow(double initialTemperature, double finalTemperature, double stepTemperature, int samplesNumber, std::string rng){
  Wolfer wolfer = Wolfer(samplesNumber, rng);
  for (double currentTemperature = initialTemperature; currentTemperature <= finalTemperature; currentTemperature += stepTemperature) {
    wolfer.timeControl(currentTemperature);
  }
}

int main(int argc, char*argv[]) {
  if(argc != 4){
    std::cout << "Wrong number of parameters!\n";
    return 1;
  } else {
    gsl_rng_env_setup();
    std::string rng = argv[1];
    if(rng != "mt" && rng != "rnlx0" && rng != "r250"){
      std::cout << "Unknown RNG!";
      return 1;
    }
    int samplesNumber = -1;
    try{
      samplesNumber = std::atoi(argv[2]);
    } catch(const std::exception&){
      std::cout << "Wrong sample number parameter!";
      return 1;
    }
    std::string mode = std::string(argv[3]);
    if(mode == "interval"){
      const double criticalTemperature = 2.269185;
      const double epsilon = 0.05;
      const double minTemperature = epsilon;
      const double maxTemperature = criticalTemperature * 2;
      temperatureFlow(minTemperature, maxTemperature, epsilon, samplesNumber, rng);
    } else if(mode == "point") {
      const double criticalTemperature = 2.269185;
      const double epsilon = 0.05;
      const double minTemperature = criticalTemperature;
      const double maxTemperature = criticalTemperature;
      temperatureFlow(minTemperature, maxTemperature, epsilon, samplesNumber, rng);
    } else {
      std::cout << "Wrong mode paramter!"<<mode<<"\n";
      return 1;
    }
  }
  return 0;
}
