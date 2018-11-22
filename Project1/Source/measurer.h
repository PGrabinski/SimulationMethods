#ifndef MEASURER_H
#define MEASURER_H
#include <tuple>
#include "lattice.h"
class Measurer{
    private:
        int configurations;
        int heatSamples;
        Lattice lattice;
        int latticeSize;

        // Total energy of the system
        double totalEnergy;
        // Total magnetization
        double totalMagnetization;
        // Total EnergySquared
        double totalEnergySquared;
        // Total Heat
        double totalHeat;
        // Total HeatSquared
        double totalHeatSquared;

        // Sample energy of the system
        double sampleEnergy;
        // Sample magnetization
        double sampleMagnetization;
        // Sample H^2
        double sampleEnergySquared;

    public:
        Measurer();
        Measurer(int configurations, int heatSamples);
        void measureSingleConfigurationObservables(Lattice& lattice, double temperature, int step);
        double measureEnergyDif(int xPosition, int yPosition, Lattice& lattice);
        void measureBatchObservables(double temperature);
        void printAvg(double temperature);
        void eraseObservables();
        
};
#endif