#ifndef RNG_H
#define RNG_H

class RNG{
    private:
         double carry, dseeds[24];
        int i24, j24, count24, nskip;
        long two24;
        double twom24;
        double twom12;
        void setseeds(long seed, int lux);
    public:
        RNG();
        RNG(int lux);
        double rnlx();

};
#endif