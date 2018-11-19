#ifndef HELPER_H
#define HELPER_H
#include "lattice.h"
class Helper{
    private:
        static const int latticeSize = 16;
        int helpersArray[latticeSize][latticeSize][4];
    public:
        void flipMarkedSpins(Lattice& lattice);
        void clearHelpers();
        void markSpin(int xPosition, int yPosition);
        int getNode(int xPosition, int yPosition, int level);
        void setNode(int xPosition, int yPosition, int level, int value);
};
#endif