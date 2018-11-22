#ifndef LATTICE_H
#define LATTICE_H

#include <gsl/gsl_rng.h>

#include "rng.h"

class Lattice{
    // Class encapsulating the lattice of the Ising model
    // It consists of a square array with values 1/-1 and methods for its usage
    private:
        // Size of the square lattice (LxL)
        static const int latticeSize = 16;
        // Array of the LxL lattice values -1(down) or 1(up)
        int latticeArray[latticeSize][latticeSize];

        // Two possible RNGs
        gsl_rng * r;
        RNG rng;
    public:
        Lattice();
        Lattice(gsl_rng * s);
        Lattice(RNG& newRng);
        void shuffleLattice();
        int getLatticeSize();
        void printLattice();
        int getNode(int xPosition, int yPosition);
        void setNode(int xPosition, int yPosition, int value);
};
#endif