#ifndef WOLFER_H
#define WOLFER_H
#include "lattice.h"
#include "helper.h"
#include "measurer.h"
#include "rng.h"

#include <gsl/gsl_rng.h>
#include <string>

class Wolfer
{
  private:
    // Number of steps used for thermalisations
    static const int thermalisationSamples = 1000;

    // Number of steps used for transitions between measured configurations
    static const int transitionSteps = 1;

    // Number of samples for Heat measurement
    static const int heatSamples = 1000;

    // Number of considered configurations
    int configurations;

    // Size of the considered lattice
    int latticeSize;

    // Temperature of the lattice
    double temperature;

    // Probability of adding a spin to a cluster corresponding to the given temperature
    double probability;

    // Two possible RNGs
    gsl_rng *s;
    RNG r;

    // Sampling from the RNG
    double getProbability();

    // Sets current temperature and updates the coressponding probability
    void setTemperature(double newTemperature);
    void updateProbability();
    double spinFlipProbability();

    // Utility function for encoding the movement
    int track(int xPosition, int yPosition);

    // Recurrent function of the Wolf algorithm
    void addConnection(int xPosition, int yPosition, int xMove, int yMove);

    // Add a spin to a cluster
    void addSpin(int xPosition, int yPosition);

    // Generate a cluster
    void generateCluster();

    // Thermalisation function
    void thermaliseLattice();

    // Classes used
    Lattice lattice;
    Helper helper;
    Measurer measurer;

  public:
    Wolfer(int samples, std::string rng);
    void timeControl(double temperature);
};
#endif