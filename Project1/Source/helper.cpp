#include "helper.h"
#include "lattice.h"

// Clear helpers array
void Helper::clearHelpers(){
  for(int i=0;i<latticeSize;i++){
    for(int j=0;j<latticeSize;j++){
      for(int k=0;k<4;k++){
        helpersArray[i][j][k]=0;
      }
    }
  }
};

// Flips marked surroundingSpinsSum
void Helper::flipMarkedSpins(Lattice& lattice){
  for(int i=0; i<latticeSize; i++){
    for(int j=0; j<latticeSize; j++){
      if(helpersArray[i][j][0]==2) lattice.setNode(i, j, lattice.getNode(i,j) * -1);
    }
  }
};

void Helper::markSpin(int xPosition, int yPosition){
  for(int k=0;k<4;k++){
    helpersArray[xPosition][yPosition][k]=2;
  }
};

int Helper::getNode(int xPosition, int yPosition, int level){
    return helpersArray[xPosition][yPosition][level];
};

void Helper::setNode(int xPosition, int yPosition, int level, int value){
    helpersArray[xPosition][yPosition][level] = value;
};