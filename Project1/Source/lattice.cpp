#include "lattice.h"

#include <gsl/gsl_rng.h>
#include <iostream>
#include <stdexcept>

// The constructor in the case of a GSL-based RNG
Lattice::Lattice(gsl_rng *s)
{
  r = s;
  rng = NULL;
  shuffleLattice();
};

// The constructor in the case of an internal RNG class
Lattice::Lattice(RNG &newRng)
{
  r = NULL;
  rng = newRng;
  shuffleLattice();
};

// The default constructor
Lattice::Lattice(){};

// The initizalizaton of the lattice for 1/-1 values using the available RNG
void Lattice::shuffleLattice()
{
  for (int i = 0; i < latticeSize; i++)
  {
    for (int j = 0; j < latticeSize; j++)
    {
      double sampleProbability = 0.0;
      if (r == NULL)
      {
        sampleProbability = rng.rnlx();
      }
      else if (r != NULL)
      {
        sampleProbability = gsl_rng_uniform(r);
      }
      else
      {
        std::cout << "Problem with RNG!\n";
        throw std::runtime_error("Wrong RNG");
      }
      if (sampleProbability < 0.5)
        latticeArray[i][j] = 1;
      else
        latticeArray[i][j] = -1;
    }
  }
};

// Returns the size of the lattice
// Prepared in case of bigger lattices
int Lattice::getLatticeSize()
{
  return latticeSize;
};

// Function printing the lattice in green and red
// It uses ASCII-based backgrounds color
void Lattice::printLattice()
{
  for (int i = 0; i < latticeSize; i++)
  {
    for (int j = 0; j < latticeSize; j++)
    {
      if (latticeArray[i][j] == -1)
        printf("%c[%d;%dm %c[%dm", 27, 1, 41, 27, 0);
      else if (latticeArray[i][j] == 1)
        printf("%c[%d;%dm %c[%dm", 27, 1, 42, 27, 0);
      else
        printf("%c[%d;%dm %c[%dm", 27, 1, 43, 27, 0);
    }
    std::cout << "\n";
  }
};

// Returns the value of a specified node (x,y)
int Lattice::getNode(int xPosition, int yPosition)
{
  return latticeArray[xPosition][yPosition];
}

// Changes the value of a given node (x,y) to a given vale
void Lattice::setNode(int xPosition, int yPosition, int value)
{
  latticeArray[xPosition][yPosition] = value;
}