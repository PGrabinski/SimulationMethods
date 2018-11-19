#ifndef MEASURER_H
#define MEASURER_H

#include "lattice.h"
class Measurer{
    private:
        int samplesNumber;
        Lattice lattice;
        int latticeSize;
        // Total energy of the system
        double * totalEnergy;
        // Total magnetization
        double * totalMagnetization;
        // Total heat capacity
        double * totalHeat;
        // Total H^2
        double * totalH2;
    public:
        Measurer();
        Measurer(int samplesNumber);
        void measureObservables(Lattice& lattice, double temperature, int step);
        double measureEnergyDif(int xPosition, int yPosition, Lattice& lattice);
        void printAvg(double temperature);
        
};
#endif