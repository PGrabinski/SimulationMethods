#ifndef MEASURER_H
#define MEASURER_H
#include <tuple>
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
        // Total H^2
        double * totalH2;
        // std::tuple<double, double> measureHeat(double temperature, double heat);
    public:
        Measurer();
        Measurer(int samplesNumber);
        void measureObservables(Lattice& lattice, double temperature, int step);
        double measureEnergyDif(int xPosition, int yPosition, Lattice& lattice);
        void printAvg(double temperature);
        
};
#endif