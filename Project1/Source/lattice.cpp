#include "lattice.h"

#include <gsl/gsl_rng.h>
#include <iostream>

Lattice::Lattice(){
    r = gsl_rng_alloc (gsl_rng_mt19937);
};

void Lattice::shuffleLattice(){
  for(int i=0; i<latticeSize; i++){
    for(int j=0; j<latticeSize; j++){
      if(gsl_rng_uniform (r)<0.5) latticeArray[i][j] = 1;
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