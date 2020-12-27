#ifndef HIGHFSCONV_H_INCLUDED
#define HIGHFSCONV_H_INCLUDED

class ConvolveHighFs {
//Decimator form of the CIC Base class
    public:
        ConvolveHighFs(uint64_t r, uint64_t dUp, uint64_t sUp, uint64_t dDown,
                        uint64_t sDown);
        ~ConvolveHighFs();

        //Modify our internal convolution
        //Which should itself be sparse!
        void addConvValues(uint64_t[] positions,
            int64_t[] values, uint64_t noValuesIn);
        void removeConvValues(uint64_t[] positions);
        void i64InOutSet(int64_t* input, int64_t* output)

        int64_t getConvPositions();
        int64_t getConvValues();

        void runFilter(uint64_t steps);

    private:
        //Dynamically allocated memory;
        uint64_t* convIndices;
        int64_t* convValues;
        uint64_t noConvValues;
        //Working memory. These signals will be very, very large
        int64_t* rawInterSignalHigh;
        int64_t* convolvedSignalHigh;
        int64_t* overflowSignalHigh;
        uint64_t workingSize;
        //Internal interpolation/decimation members (obviously)
        CICInterpolator internalInterpolator;
        CICDecimator internalDecimator;
};

#endif
