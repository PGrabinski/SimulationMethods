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
    totalHeat = new double[samples];
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
            tempEnergy = measureEnergyDif(i, j, lattice);
            dEnergy += tempEnergy;
            dEnergySquared += tempEnergy*tempEnergy;
        }
    }
    totalH2[step] = dEnergySquared;
    totalEnergy[step] = (dEnergy);
    totalMagnetization[step] = abs(magnetization);
    totalHeat[step] = dEnergySquared - dEnergy*dEnergy;
}

// Measure the heat and its variance
std::tuple<double, double> Measurer::measureHeat(double temperature){
    int energySamples = 10.0;
    int heatSamples = samplesNumber/energySamples;
    double temporaryHeat = 0.0;
    double finalHeatEstimator = 0.0;
    double finalHeatEstimatorSquared = 0.0;
    double energyNormalization = energySamples * std::pow(latticeSize,2) * std::pow(temperature,2);
    for(int i=0;i<heatSamples;i++){
        temporaryHeat = 0.0;
        for(int j=0;j<energySamples;j++){
            temporaryHeat += totalH2[i*energySamples + j] - totalEnergy[i*energySamples + j] * totalEnergy[i*energySamples + j]/energyNormalization;
        }
        finalHeatEstimator += temporaryHeat/energyNormalization;
        finalHeatEstimatorSquared += std::pow(temporaryHeat,2)/energyNormalization;
    }
    double heatNormalization = heatSamples;
    finalHeatEstimator /= heatNormalization;
    finalHeatEstimatorSquared /= heatNormalization;
    double heatDeviation = finalHeatEstimatorSquared - std::pow(finalHeatEstimator,2);
    heatDeviation = std::sqrt(heatDeviation/heatSamples);
    return std::make_tuple(finalHeatEstimator, heatDeviation);

};


// Prints averages of counted values
void Measurer::printAvg(double temperature){
    double totEnergy = 0.0;
    double totMag = 0.0;
    double totHeat = 0.0;
    double totH2 = 0.0;
    for(int i=0; i<samplesNumber; i++){
        totEnergy+=totalEnergy[i];
        totMag+=totalMagnetization[i];
        totHeat+=totalHeat[i];
        totH2+=totalH2[i];
    }
    double normalization = double(samplesNumber * latticeSize * latticeSize);
    totEnergy/=normalization;
    double varEnergy =totH2 / normalization - totEnergy * totEnergy;
    totMag/=normalization;
    varEnergy= sqrt(varEnergy/samplesNumber);
    // totHeat = varEnergy/(temperature*temperature);
    double heatDev = 0.0;
    std::tie(totHeat, heatDev) = measureHeat(temperature); 
    // << ","  << heatDev
    std::cout << totEnergy << "," << varEnergy << "," << totMag << "," << totHeat << ","  << temperature << "\n";
};