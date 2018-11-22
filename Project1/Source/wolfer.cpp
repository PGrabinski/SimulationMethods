#include "wolfer.h"
#include "lattice.h"
#include "helper.h"
#include "measurer.h"
#include "rng.h"

#include <gsl/gsl_rng.h>
#include <cmath>
#include <iostream>
#include <string>

Wolfer::Wolfer(int samples, std::string rng)
{
  configurations = samples;
  helper = Helper();
  measurer = Measurer(configurations, heatSamples);
  latticeSize = lattice.getLatticeSize();
  if (rng == "rnlx0")
  {
    s = NULL;
    r = RNG(0);
    lattice = Lattice(r);
  }
  else if (rng == "mt")
  {
    s = gsl_rng_alloc(gsl_rng_mt19937);
    lattice = Lattice(s);
  }
  else if (rng == "r250")
  {
    s = gsl_rng_alloc(gsl_rng_r250);
    lattice = Lattice(s);
  }
};

double Wolfer::getProbability()
{
  if (s == NULL)
  {
    return r.rnlx();
  }
  else
  {
    return gsl_rng_uniform(s);
  }
};

void Wolfer::updateProbability()
{
  probability = spinFlipProbability();
};

void Wolfer::setTemperature(double newTemperature)
{
  temperature = newTemperature;
  updateProbability();
  measurer.eraseObservables();
};

double Wolfer::spinFlipProbability()
{
  double prob = 1.0 - exp(-2 / temperature);
  return prob;
};

int Wolfer::track(int x, int y)
{
  if (x == 1)
    return 0;
  if (x == -1)
    return 1;
  if (y == 1)
    return 2;
  if (y == -1)
    return 3;
  return -1;
};

void Wolfer::addSpin(int xPosition, int yPosition)
{
  helper.markSpin(xPosition, yPosition);
  addConnection(xPosition - 1, yPosition, -1, 0);
  addConnection(xPosition + 1, yPosition, 1, 0);
  addConnection(xPosition, yPosition - 1, 0, -1);
  addConnection(xPosition, yPosition + 1, 0, 1);
};

// Creates cluster for spin flipping
void Wolfer::addConnection(int xPosition, int yPosition, int xMove, int yMove)
{

  xPosition = (xPosition + latticeSize) % latticeSize;
  yPosition = (yPosition + latticeSize) % latticeSize;

  int currentSpin = lattice.getNode(xPosition, yPosition);
  if (xMove == -10)
  {
    addSpin(xPosition, yPosition);
    return;
  }
  if (helper.getNode(xPosition, yPosition, 0) == 2)
    return;

  if (getProbability() < probability)
  {

    if ((currentSpin == lattice.getNode((xPosition - xMove + latticeSize) % latticeSize,
                                        (yPosition - yMove + latticeSize) % latticeSize) &&
         helper.getNode(xPosition, yPosition, track(xMove, yMove)) == 1))
    {
      return;
    }
    if (currentSpin == lattice.getNode((xPosition - xMove + latticeSize) % latticeSize,
                                       (yPosition - yMove + latticeSize) % latticeSize))
    {
      addSpin(xPosition, yPosition);
    }
  }
  else
  {
    helper.setNode(xPosition, yPosition, track(xMove, yMove), 1);
  }
};

// Thermalise the lattice
void Wolfer::thermaliseLattice()
{
  for (int i = 0; i < thermalisationSamples; i++)
  {
    generateCluster();
  }
};

// Create a cluster
void Wolfer::generateCluster()
{
  int tempX = (int)(latticeSize * getProbability());
  int tempY = (int)(latticeSize * getProbability());
  addConnection(tempX, tempY, -10, -10);
  helper.flipMarkedSpins(lattice);
  helper.clearHelpers();
};

// Controls the Wolf algorithm for given temperature
void Wolfer::timeControl(double temperature)
{
  setTemperature(temperature);
  helper.clearHelpers();
  thermaliseLattice();

  // Temp variables for (x,y) of the begining node
  int tempX;
  int tempY;

  for (int step = 0; step < int(configurations / heatSamples); step++)
  {
    for (int midstep = 0; midstep < heatSamples; midstep++)
    {
      for (int i = 0; i < transitionSteps; i++)
      {
        generateCluster();
      }
      measurer.measureSingleConfigurationObservables(lattice, temperature, step);
    }
    measurer.measureBatchObservables(temperature);
  }
  measurer.printAvg(temperature);
};