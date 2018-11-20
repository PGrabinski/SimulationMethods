#include "measurer.h"
#include "lattice.h"

#include <iostream>
#include <cassert>
#include <cmath>
#include <tuple>

Measurer::Measurer(){};

Measurer::Measurer(int samples){
    samplesNumber = samples;
    totalEnergy = new double[samples];
    totalMagnetization = new double[samples];
    totalH2 = new double[samples];
    latticeSize = lattice.getLatticeSize();
    // std::cout << "Energy" << "," << "EnergyDev" << "," << "Magnetization" << "," << "Heat" << "," < ","  << "HeatDev" << "Temperature" << "\n";
};

// Measure energy difference after a single flip
double Measurer::measureEnergyDif(int xPosition, int yPosition, Lattice& lattice){
    int spinSum=0;
    spinSum += lattice.getNode((xPosition+1+latticeSize)%latticeSize, yPosition);
    spinSum += lattice.getNode((xPosition-1+latticeSize)%latticeSize, yPosition);
    spinSum += lattice.getNode(xPosition, (yPosition+1+latticeSize)%latticeSize);
    spinSum += lattice.getNode(xPosition, (yPosition-1+latticeSize)%latticeSize);
    return -0.5 * lattice.getNode(xPosition, yPosition) * spinSum;
};

// Measure observables
void Measurer::measureObservables(Lattice& lattice, double temperature, int step){
    double dEnergy = 0.0;
    double dEnergySquared = 0.0;
    double magnetization = 0.0;
    double tempEnergy = 0.0;
    int tempSpin = 0;
    // lattice.printLattice();
    for(int i=0;i<latticeSize;i++){
        for(int j=0;j<latticeSize;j++){
            tempSpin = lattice.getNode(i, j);
            magnetization += tempSpin;
            dEnergy += measureEnergyDif(i, j, lattice);
        }
    }
    totalH2[step] = std::pow(dEnergy, 2);
    totalEnergy[step] = dEnergy;
    totalMagnetization[step] = abs(magnetization);
}

// // Measure the heat and its variance
// std::tuple<double, double> Measurer::measureHeat(double temperature, double heat){
//     int energySamples = 10.0;
//     int heatSamples = samplesNumber/energySamples;
//     double temporaryHeat = 0.0;
//     double finalHeatEstimator = 0.0;
//     double finalHeatEstimatorSquared = 0.0;
//     for(int i=0;i<heatSamples;i++){
//         temporaryHeat = 0.0;
//         for(int j=0;j<energySamples;j++){
//             temporaryHeat += totalH2[i*energySamples + j]
//              - totalEnergy[i*energySamples + j] * totalEnergy[i*energySamples + j];
//         }
//         finalHeatEstimator += temporaryHeat/energyNormalization;
//         finalHeatEstimatorSquared += std::pow(temporaryHeat,2)/energyNormalization;
//     }
//     double heatNormalization = heatSamples;
//     finalHeatEstimator /= heatNormalization;
//     finalHeatEstimatorSquared /= heatNormalization;
//     double heatDeviation = finalHeatEstimatorSquared - std::pow(finalHeatEstimator,2);
//     heatDeviation = std::sqrt(heatDeviation/heatSamples);
//     return std::make_tuple(finalHeatEstimator, heatDeviation);

// };


// Prints averages of counted values
void Measurer::printAvg(double temperature){
    double totEnergy = 0.0;
    double totMag = 0.0;
    double totH2 = 0.0;
    int heatSamples = 100;
    double heatSquared = 0.0;
    double tempEnergy = 0.0;
    double tempEnergySquared = 0.0;
    int heatCounter = 0;

    for(int i=0; i<samplesNumber; i++){
        if (heatCounter == heatSamples){
            heatSquared += std::pow((tempEnergySquared/heatSamples - std::pow(tempEnergy/heatSamples, 2))
             / std::pow(temperature,2) / std::pow(latticeSize, 2),2);
            heatCounter = 0;
            tempEnergy = 0;
            tempEnergySquared = 0;
        } else {
            tempEnergy += totalEnergy[i];
            tempEnergySquared += totalH2[i];
            heatCounter++;
        }
        totEnergy += totalEnergy[i];
        totMag += totalMagnetization[i];
        totH2 += totalH2[i];
    }

    double avgEnergy = totEnergy / samplesNumber;
    double avgSquaredEnergy = totH2 / samplesNumber;
    double avgMagnetization = totMag / samplesNumber;
    double varEnergy = avgSquaredEnergy - std::pow(avgEnergy,2);
    double energyDeviation = std::sqrt(varEnergy/samplesNumber);
    double heat = varEnergy / std::pow(temperature,2) / std::pow(latticeSize, 2);

    double energyPerSpin = avgEnergy / std::pow(latticeSize, 2);
    double energySquaredPerSpin = avgSquaredEnergy / std::pow(latticeSize, 2);
    double devEnergyPerSpin = std::sqrt((energySquaredPerSpin - std::pow(energyPerSpin,2)) / samplesNumber);
    double magnetizationPerSpin = avgMagnetization / std::pow(latticeSize, 2);

    double heatDeviation = std::sqrt((heatSquared - std::pow(heat,2)) / (samplesNumber / heatSamples));
    
    std::cout << energyPerSpin << "," << devEnergyPerSpin << "," << magnetizationPerSpin << "," << heat << "," << heatDeviation << ","  << temperature << "\n";
};