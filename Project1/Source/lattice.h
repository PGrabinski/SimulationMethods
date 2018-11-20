#ifndef LATTICE_H
#define LATTICE_H

#include <gsl/gsl_rng.h>

#include "rng.h"

class Lattice{
    private:
        // Size of the square lattice (LxL)
        static const int latticeSize = 16;
        // Array of the LxL lattice values -1(down) or 1(up)
        int latticeArray[latticeSize][latticeSize];
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