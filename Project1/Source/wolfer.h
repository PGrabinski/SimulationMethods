#ifndef WOLFER_H
#define WOLFER_H
#include "lattice.h"
#include "helper.h"
#include "measurer.h"
#include <gsl/gsl_rng.h>

class Wolfer{
    private:
        int samplesPerTemperature;
        int latticeSize;
        double temperature;
        double probability;

        gsl_rng * s;

        void setTemperature(double newTemperature);
        void updateProbability();

        double spinFlipProbability();
        int track(int xPosition, int yPosition);

        void addConnection(int xPosition, int yPosition, int xMove, int yMove);

        Lattice lattice;
        Helper helper;
        Measurer measurer;
    public:
        Wolfer(int samples, gsl_rng * r);
        void timeControl(double temperature);

};
#endif