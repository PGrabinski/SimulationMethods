#include "lattice.h"

#include <gsl/gsl_rng.h>
#include <iostream>
#include <stdexcept>

Lattice::Lattice(gsl_rng * s){
    r = s;
    rng = NULL;
};

Lattice::Lattice(RNG& newRng){
    r = NULL;
    rng = newRng;
};

Lattice::Lattice(){};

void Lattice::shuffleLattice(){
  for(int i=0; i<latticeSize; i++){
    for(int j=0; j<latticeSize; j++){
      double sampleProbability = 0.0;
      if(r == NULL){
        sampleProbability = rng.rnlx();
      } else if(r != NULL){
        sampleProbability = gsl_rng_uniform (r);
      } else {
        std::cout << "Problem with RNG!\n";
        throw std::runtime_error("Wrong RNG");
      }
      if(sampleProbability<0.5) latticeArray[i][j] = 1;
      else  latticeArray[i][j] = -1;
    }
  }
};

int Lattice::getLatticeSize(){
    return latticeSize;
};

void Lattice::printLattice(){
  for(int i=0;i<latticeSize;i++){
    for(int j=0;j<latticeSize;j++){
      if(latticeArray[i][j]==-1) printf("%c[%d;%dm %c[%dm",27,1,41,27,0);
      else if (latticeArray[i][j]==1) printf("%c[%d;%dm %c[%dm",27,1,42,27,0);
      else printf("%c[%d;%dm %c[%dm",27,1,43,27,0);
    }
    std::cout << "\n";
  }
};

int Lattice::getNode(int xPosition, int yPosition){
    int temp = latticeArray[xPosition][yPosition];
    // std::cout << temp << "\n";
    return temp;
}

void Lattice::setNode(int xPosition, int yPosition, int value){
    latticeArray[xPosition][yPosition] = value;
}