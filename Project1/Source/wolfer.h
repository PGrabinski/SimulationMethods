#ifndef WOLFER_H
#define WOLFER_H
#include "lattice.h"
#include "helper.h"
#include "measurer.h"
#include "rng.h"

#include <gsl/gsl_rng.h>
#include <string>

class Wolfer{
    private:
        int samplesPerTemperature;
        int latticeSize;
        double temperature;
        double probability;

        gsl_rng * s;
        RNG r;

        void setTemperature(double newTemperature);
        void updateProbability();

        double spinFlipProbability();
        int track(int xPosition, int yPosition);
        double getProbability();

        void addConnection(int xPosition, int yPosition, int xMove, int yMove);

        Lattice lattice;
        Helper helper;
        Measurer measurer;
    public:
        Wolfer(int samples, std::string rng);
        void timeControl(double temperature);

};
#endif