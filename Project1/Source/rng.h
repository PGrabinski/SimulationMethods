#ifndef RNG_H
#define RNG_H

class RNG{
    private:
         double carry, dseeds[24];
        int i24, j24, count24, nskip;
        static const long two24 = 16777216;
        static const double twom24= 1.0/16777216.0;
        static const double twom12= 1.0/4096.0;
    public:
        void setseeds(long seed, int lux);
        double rnlx();

};
#endif