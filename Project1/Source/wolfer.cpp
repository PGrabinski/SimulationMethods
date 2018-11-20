#include "wolfer.h"
#include "lattice.h"
#include "helper.h"
#include "measurer.h"
#include "rng.h"

#include <gsl/gsl_rng.h>
#include <cmath>
#include <iostream>
#include <string>

Wolfer::Wolfer(int samples, std::string rng){
    samplesPerTemperature = samples;
    helper = Helper();
    measurer = Measurer(samplesPerTemperature);
    latticeSize = lattice.getLatticeSize();
    if(rng == "rnlx0"){
      s = NULL;
      r = RNG(0);
      lattice = Lattice(r);
    } else if(rng == "mt"){
      s = gsl_rng_alloc(gsl_rng_mt19937);
      lattice = Lattice(s);
    } else if(rng == "r250"){
      s = gsl_rng_alloc(gsl_rng_r250);
      lattice = Lattice(s);
    }
    
};

double Wolfer::getProbability(){
  if(s == NULL){
    return r.rnlx();
  } else {
    return gsl_rng_uniform(s);
  }
};

void Wolfer::updateProbability(){
    probability = spinFlipProbability();
};

void Wolfer::setTemperature(double newTemperature){
    temperature = newTemperature;
    updateProbability();
};

double Wolfer::spinFlipProbability(){
  double prob = 1.0 - exp(-2  / temperature);
  return prob;
};

int Wolfer::track(int x,int y){
  if(x == 1) return 0;
  if(x == -1) return 1;
  if(y == 1) return 2;
  if(y == -1) return 3;
  return -1;
};

// Creates cluster for spin flipping
void Wolfer::addConnection(int xPosition, int yPosition, int xMove, int yMove){
    
  xPosition=(xPosition+latticeSize)%latticeSize;
  yPosition=(yPosition+latticeSize)%latticeSize;
  
  int currentSpin = lattice.getNode(xPosition, yPosition);
  if(xMove == -10){
    helper.markSpin(xPosition,yPosition);
    addConnection(xPosition-1,yPosition,-1,0);
    addConnection(xPosition+1,yPosition,1,0);
    addConnection(xPosition,yPosition-1,0,-1);
    addConnection(xPosition,yPosition+1,0,1);
    return;
  }
  if(helper.getNode(xPosition, yPosition, 0) == 2) return;

  if(getProbability() < probability ){

    if((currentSpin == lattice.getNode((xPosition-xMove+latticeSize)%latticeSize, (yPosition-yMove+latticeSize)%latticeSize)
      && helper.getNode(xPosition, yPosition, track(xMove,yMove))==1)){
        return;
    }
    if(currentSpin == lattice.getNode((xPosition-xMove+latticeSize)%latticeSize, (yPosition-yMove+latticeSize)%latticeSize)) {
      helper.markSpin(xPosition,yPosition);
      addConnection(xPosition-1,yPosition,-1,0);
      addConnection(xPosition+1,yPosition,1,0);
      addConnection(xPosition,yPosition-1,0,-1);
      addConnection(xPosition,yPosition+1,0,1);
    }
  } else {
    helper.setNode(xPosition, yPosition, track(xMove,yMove), 1);
  }
};

// Controls the Wolf algorithm for given temperature
void Wolfer::timeControl(double temperature){
    setTemperature(temperature);

    for(int step=0; step < samplesPerTemperature; step++){
        lattice.shuffleLattice();
        // lattice.printLattice();
        helper.clearHelpers();

        // Number of time steps for thermalisation
        int N = 100;

        // Temp variables for (x,y) of the begining node
        int tempX;
        int tempY;

        for(int i=0;i<N;i++){
            tempX = (int) (latticeSize * getProbability());
            tempY = (int) (latticeSize * getProbability());
            addConnection(tempX,tempY,-10,-10);
            helper.flipMarkedSpins(lattice);
            helper.clearHelpers();
        }
        measurer.measureObservables(lattice, temperature, step);
    }
    measurer.printAvg(temperature);
};