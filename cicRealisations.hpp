#ifndef CICREALISATIONS_H_INCLUDED
#define CICREALISATIONS_H_INCLUDED

class CICInterpolator : public CICBase {
//Decimator form of the CIC Base class
    public:
        CICInterpolator(uint64_t r, uint64_t d, uint64_t s);
        ~CICInterpolator();
        void runFilter(uint64_t steps);
};

class CICDecimator : public CICBase {
//Decimator form of the CIC Base class
    public:
        CICDecimator(uint64_t r, uint64_t d, uint64_t s);
        ~CICDecimator();
        void runFilter(uint64_t steps);
};

#endif
