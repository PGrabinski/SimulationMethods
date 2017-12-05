#include <iostream>
#include <cmath>
#include <gsl/gsl_rng.h>

// Size of the square lattice (LxL)
const int latticeSize = 16;
// Array of the LxL array values -1(down) or 1(up)
int latticeArray[latticeSize][latticeSize];
// Coupling constant
const int couplingJ = -1;

// Imposses cyclic boundary conditions on x coordinate
int cyclicBoundariesX(int xPosition, int move){
  if (xPosition+move == latticeSize){
    return 0;
  }
  if (xPosition+move == -1){
    return latticeSize-1;
  }
  // Sth went wrong
  return -10;
}

// Imposses cyclic boundary conditions on y coordinate
int cyclicBoundariesY(int yPosition, int move){
  if (yPosition+move == latticeSize){
    return 0;
  }
  if (yPosition+move == -1){
    return latticeSize-1;
  }
  // Sth went wrong
  return -10;
}

double spinFlipProbability(double temperature, int xPosition, int yPosition){
  // Takes the given spin value
  int givenSpin = latticeArray[xPosition][yPosition];

  // Declaration of helper sums
  int spinInteractionSum = 0.0;
  int surroundingSpinsSum = 0.0;

  // Summing over all 4 neighboring nodes
  surroundingSpinsSum += latticeArray[cyclicBoundariesX(xPosition,-1)][yPosition];
  surroundingSpinsSum += latticeArray[cyclicBoundariesX(xPosition,1)][yPosition];
  surroundingSpinsSum += latticeArray[xPosition][cyclicBoundariesY(yPosition,-1)];
  surroundingSpinsSum += latticeArray[xPosition][cyclicBoundariesY(yPosition,1)];

  // Multiplying sum of the all neighboring by coupling constant and th value of the given spin
  spinInteractionSum += couplingJ * givenSpin * surroundingSpinsSum;

  // Return probability which is equal 1 - exp(-2J/kT) with k=1
  return 1.0 - exp(-2 * spinInteractionSum / temperature);
}


// Sets values in the lattice for -1(down) or 1(up)
void shuffleLattice(){
  gsl_rng * r = gsl_rng_alloc (gsl_rng_mt19937);
  for(int i=0; i<latticeSize; i++){
    for(int j=0; j<latticeSize; j++){
      if(gsl_rng_uniform (r)<0.5) latticeArray[i][j] = 1;
      else  latticeArray[i][j] = -1;
    }
  }
}

void addConnection(int xPositionCurrent, int yPositionCurrent,int xPositionPrevious, int yPositionPrevious){
  int currentSpin = latticeArray[xPositionCurrent][yPositionCurrent];
  if( currentSpin != latticeArray[xPositionPrevious][yPositionPrevious] ) return;
  
}



int main() {
  gsl_rng_env_setup();
  shuffleLattice();

  return 0;
}
