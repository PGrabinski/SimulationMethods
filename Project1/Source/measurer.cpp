#include "measurer.h"
#include "lattice.h"

#include <iostream>
#include <cassert>
#include <cmath>
#include <tuple>

Measurer::Measurer(){};

Measurer::Measurer(int samples, int hsamples)
{
    configurations = samples;
    heatSamples = hsamples;
    eraseObservables();
    latticeSize = lattice.getLatticeSize();
    // std::cout << "Energy" << "," << "EnergyDev" << "," << "Magnetization" << "," << "Heat" << "," < ","  << "HeatDev" << "Temperature" << "\n";
};

void Measurer::eraseObservables()
{
    totalEnergy = 0.0;
    totalMagnetization = 0.0;
    totalEnergySquared = 0.0;
    totalHeat = 0.0;
    totalHeatSquared = 0.0;

    sampleEnergy = 0.0;
    sampleMagnetization = 0.0;
    sampleEnergySquared = 0.0;
};

// Measure energy difference after a single flip
double Measurer::measureEnergyDif(int xPosition, int yPosition, Lattice &lattice)
{
    int spinSum = 0;
    spinSum += lattice.getNode((xPosition + 1 + latticeSize) % latticeSize, yPosition);
    spinSum += lattice.getNode((xPosition - 1 + latticeSize) % latticeSize, yPosition);
    spinSum += lattice.getNode(xPosition, (yPosition + 1 + latticeSize) % latticeSize);
    spinSum += lattice.getNode(xPosition, (yPosition - 1 + latticeSize) % latticeSize);
    return -0.5 * lattice.getNode(xPosition, yPosition) * spinSum;
};

// Measure observables for a single configuration
void Measurer::measureSingleConfigurationObservables(Lattice &lattice, double temperature, int step)
{
    double singleConfiguratioEnergy = 0.0;
    double magnetization = 0.0;
    int tempSpin = 0;
    // lattice.printLattice();
    for (int i = 0; i < latticeSize; i++)
    {
        for (int j = 0; j < latticeSize; j++)
        {
            tempSpin = lattice.getNode(i, j);
            magnetization += tempSpin;
            singleConfiguratioEnergy += measureEnergyDif(i, j, lattice);
        }
    }
    sampleEnergySquared += std::pow(singleConfiguratioEnergy, 2);
    sampleEnergy += singleConfiguratioEnergy;
    sampleMagnetization += abs(magnetization);
}

// Measures the observables for a batch of configurations
void Measurer::measureBatchObservables(double temperature)
{
    double batchEnergySquared = sampleEnergySquared / heatSamples;
    double batchEnergy = sampleEnergy / heatSamples;
    double batchHeat = (batchEnergySquared - std::pow(batchEnergy, 2)) / std::pow(latticeSize, 2) / std::pow(temperature, 2);

    totalEnergy += batchEnergy;
    totalEnergySquared += batchEnergySquared;

    totalMagnetization += sampleMagnetization / heatSamples;

    totalHeat += batchHeat;
    totalHeatSquared += std::pow(batchHeat, 2);

    sampleEnergy = 0.0;
    sampleEnergySquared = 0.0;
    sampleMagnetization = 0.0;
};

// Prints averages of counted values
void Measurer::printAvg(double temperature)
{
    int batches = (configurations / heatSamples);
    int spinNumber = std::pow(latticeSize, 2);

    totalEnergy /= batches * spinNumber;
    totalEnergySquared /= batches * spinNumber;
    double statisticalErrorEnergy = std::sqrt((totalEnergySquared - std::pow(totalEnergy, 2)) / configurations);

    totalMagnetization /= batches * spinNumber;

    totalHeat /= batches;
    totalHeatSquared /= batches;
    double statisticalErrorHeat = std::sqrt((totalHeatSquared - std::pow(totalHeat, 2)) / batches);

    std::cout << totalEnergy << "," << statisticalErrorEnergy << "," << totalMagnetization << "," << totalHeat << "," << statisticalErrorHeat << "," << temperature << "\n";
};

double Measurer::currentEnergy(Lattice &lattice)
{
    double singleConfiguratioEnergy = 0.0;
    int tempSpin = 0;
    for (int i = 0; i < latticeSize; i++)
    {
        for (int j = 0; j < latticeSize; j++)
        {
            tempSpin = lattice.getNode(i, j);
            singleConfiguratioEnergy += measureEnergyDif(i, j, lattice);
        }
    }
    return singleConfiguratioEnergy / std::pow(latticeSize,2);
    
}