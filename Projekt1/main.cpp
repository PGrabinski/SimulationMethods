#include <iostream>
#include <cmath>
#include <gsl/gsl_rng.h>
#include <stdio.h>


using namespace std;

// Size of the square lattice (LxL)
const int latticeSize = 16;
// Array of the LxL lattice values -1(down) or 1(up)
int latticeArray[latticeSize][latticeSize];
// Array of the LxL flipping helpers
int helpersArray[latticeSize][latticeSize][4];
// Coupling constant
const int couplingJ = 1;
// RNG
gsl_rng * s = gsl_rng_alloc (gsl_rng_mt19937);
// Total energy of the system
double totalEnergy = 0.0;
// Total magnetization
double totalMagnetization = 0.0;
// Total heat
double totalHeat = 0.0;


// double spinFlipProbability(double temperature, int xPosition, int yPosition){
  // Takes the given spin value
  // int givenSpin = latticeArray[xPosition][yPosition];

  // Declaration of helper sums
  // int spinInteractionSum = 0;
  // int surroundingSpinsSum = 0;

  // Summing over all 4 neighboring nodes
  // surroundingSpinsSum += latticeArray[cyclicBoundariesX(xPosition,-1)][yPosition];
  // surroundingSpinsSum += latticeArray[cyclicBoundariesX(xPosition,1)][yPosition];
  // surroundingSpinsSum += latticeArray[xPosition][cyclicBoundariesY(yPosition,-1)];
  // surroundingSpinsSum += latticeArray[xPosition][cyclicBoundariesY(yPosition,1)];
  // if (abs(latticeArray[cyclicBoundariesX(xPosition,-1)][yPosition])!=1) cout << "Shit went south!\n";
  // Multiplying sum of the all neighboring by coupling constant and th value of the given spin
  // spinInteractionSum += couplingJ * givenSpin * surroundingSpinsSum;

  // Return probability which is equal 1 - exp(-2J/kT) with k=1
//   double prob = 1.0 - exp(-2  / temperature);
//   cout << "Probability " << prob << "\n";
//   return prob;
// }

double spinFlipProbability(double temperature){
  double prob = 1.0 - exp(-2  / temperature);
  return prob;
}


// Clear helpers array
void clearHelpers(){
  for(int i=0;i<latticeSize;i++){
    for(int j=0;j<latticeSize;j++){
      for(int k=0;k<4;k++){
        helpersArray[i][j][k]=0;
      }
    }
  }
}

// Randomly sets values in the lattice for -1(down) or 1(up)
void shuffleLattice(){
  gsl_rng * r = gsl_rng_alloc (gsl_rng_mt19937);
  for(int i=0; i<latticeSize; i++){
    for(int j=0; j<latticeSize; j++){
      if(gsl_rng_uniform (r)<0.5) latticeArray[i][j] = 1;
      else  latticeArray[i][j] = -1;
    }
  }
}

// Flips marked surroundingSpinsSum
void flipMarkedSpins(){
  for(int i=0; i<latticeSize; i++){
    for(int j=0; j<latticeSize; j++){
      if(helpersArray[i][j][0]==2) latticeArray[i][j] *= -1;
    }
  }
}

void markSpin(int xPosition,int yPosition){
  for(int k=0;k<4;k++){
    helpersArray[xPosition][yPosition][k]=2;
  }
}

int track(int x,int y){
  if(x == 1) return 0;
  if(x == -1) return 1;
  if(y == 1) return 2;
  if(y == -1) return 3;
  return -1;
}

// Creates claster for spin flipping
void addConnection(int xPosition, int yPosition, int xMove, int yMove, double probability){
  // cout<< xPosition << " " << yPosition << "\n";
  xPosition=(xPosition+latticeSize)%latticeSize;
  yPosition=(yPosition+latticeSize)%latticeSize;
  // cout<< xPosition << " " << yPosition << "\n";
  int currentSpin = latticeArray[xPosition][yPosition];
  if(xMove == -10){
    markSpin(xPosition,yPosition);
    addConnection(xPosition-1,yPosition,-1,0,probability);
    addConnection(xPosition+1,yPosition,1,0,probability);
    addConnection(xPosition,yPosition-1,0,-1,probability);
    addConnection(xPosition,yPosition+1,0,1,probability);
    return;
  }
  if(helpersArray[xPosition][yPosition][0]==2) return;

  if(gsl_rng_uniform(s) < probability ){

    if((currentSpin == latticeArray[(xPosition-xMove+latticeSize)%latticeSize][(yPosition-yMove+latticeSize)%latticeSize]
      && helpersArray[xPosition][yPosition][track(xMove,yMove)]==1)){
        return;
    }
    if(currentSpin == latticeArray[(xPosition-xMove+latticeSize)%latticeSize][(yPosition-yMove+latticeSize)%latticeSize]) {
      markSpin(xPosition,yPosition);
      addConnection(xPosition-1,yPosition,-1,0,probability);
      addConnection(xPosition+1,yPosition,1,0,probability);
      addConnection(xPosition,yPosition-1,0,-1,probability);
      addConnection(xPosition,yPosition+1,0,1,probability);
    }
  } else {
    helpersArray[xPosition][yPosition][track(xMove,yMove)]=1;
  }
}

// Measure magnetization
void printLattice(){
  for(int i=0;i<latticeSize;i++){
    for(int j=0;j<latticeSize;j++){
      if(latticeArray[i][j]==-1) printf("%c[%d;%dm %c[%dm\n",27,1,41,27,0);
      else printf("%c[%d;%dm %c[%dm\n",27,1,42,27,0);
    }
    cout << "\n";
  }
}

// Measure energy difference after flip
double measureEnergyDif(int x, int y){
    int spinSum=0;
    for(int i=x-1;i<x+1;i++){
        for(int j=y-1;j<y+1;j++){
            if(i!=j)
                spinSum+=latticeArray[(i+latticeSize)%latticeSize][(j+latticeSize)%latticeSize];
        }
    }
    return 2*latticeArray[x][y]*spinSum*couplingJ;
}

// Measure obserables
void measureObservables(){
    double energy = 0.0;
    double magnetization = 0.0;
    for(int i=0;i<latticeSize;i++){
      for(int j=0;j<latticeSize;j++){
        magnetization +=  latticeArray[i][j];
        energy += measureEnergyDif(i,j)/4.0;
      }
    }
    totalEnergy = energy/latticeSize/latticeSize;
    totalMagnetization = magnetization/latticeSize/latticeSize;
    //printLattice();
}

// Controls the Wolf algorithm for given temperature
void timeControl(double temperature){
  // Number of time steps
  int N = 1000;
  // Temp variables for (x,y) of the begining node
  int tempX;
  int tempY;
  measureObservables();
  for(int i=0;i<N;i++){
    // if(i%10==0) printLattice();
    tempX = (int) (latticeSize * gsl_rng_uniform(s));
    tempY = (int) (latticeSize * gsl_rng_uniform(s));
    addConnection(tempX,tempY,-10,-10, spinFlipProbability(temperature));
    flipMarkedSpins();
    clearHelpers();
    measureObservables();
  //  cout << totalEnergy << " " << totalMagnetization << " " << totalHeat << " " << temperature << "\n";// i << "\n";
  }
  measureObservables();
}

// Controls temperature change in the lattice
void temperatureFlow(){
  for (double i = 1; i < 5; i = i + 0.01) {
    shuffleLattice();
    clearHelpers();
    timeControl(i);
    cout << totalEnergy << " " << abs(totalMagnetization) << " " << totalHeat << " " << i << "\n";
  }
}

int main() {
  gsl_rng_env_setup();
  shuffleLattice();
  clearHelpers();
  temperatureFlow();
  return 0;
}
