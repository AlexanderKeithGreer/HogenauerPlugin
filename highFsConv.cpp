#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include "cicBase.hpp"
#include "cicRealisations.hpp"
#include "highFsConv.hpp"

using namespace std;

//Everything I've been doing to date is pointless because the
//  impulse will get smushed back when the bandwidth shrinks.
//However, deep down, I knew that the point was more C++ practice.
//So whatever.

ConvolveHighFs::ConvolveHighFs(uint64_t r, uint64_t dUp, uint64_t sUp,
    uint64_t dDown, uint64_t sDown, uint64_t workingMemorySize)
{
    //Create our interpolator and decimator
    internalInterpolator = CICInterpolator(r, dUp, sUp);
    internalDecimator = CICDecimator(r, dDown, sDown);

    //Quickly give our convolution values data
    convIndices = (uint64_t*) calloc(0, sizeof(uint64_t));
    convValues = (int64_t*) calloc(0, sizeof(int64_t));

    //Add the working memory we need
    rawInterSignalHigh = (int64_t*) calloc(workingMemorySize, sizeof(int64_t));
    convolvedSignalHigh = (int64_t*) calloc(workingMemorySize, sizeof(int64_t));
    //Add more working memory to deal with overflows!
    overflowSignalHigh = (int64_t*) calloc(workingMemorySize, sizeof(int64_t));
    workingSize = workingMemorySize;
}


ConvolveHighFs::~ConvolveHighFs(uint64_t r, uint64_t dUp, uint64_t sUp,
    uint64_t dDown, uint64_t sDown)
{
    //Delete our classes;
    delete internalInterpolator;
    delete internalDecimator;

    //Free our dynamic memory
    free(convIndices);
    free(convValues);
}


ConvolveHighFs::addConvValues(uint64_t[] positions,
    int64_t[] values, uint64_t noValuesIn);
{
     noValuesTemp = noConvValues + noValuesIn;
    //reallocate the indices
    uint64_t* IndicesTemp = (uint64_t*) calloc(noValuesTemp, sizeof(uint64_t));
    int64_t* ValuesTemp = (int64_t*) calloc(noValuesTemp, sizeof(int64_t));

    //Copy our old values to the start
    for (int index = 0;index < noConvValues;index++)
    {
        IndicesTemp[index] = convIndices[index];
        ValuesTemp[index] = convValues[index];
    }
    //Append our new values at the end
    for (int index = noConvValues; index < noValuesTemp; index++)
    {
        IndicesTemp[index] = positions[index];
        ValuesTemp[index] = values[index];
    }
    //Check that we have no values twice the length of our working memory,
    //  remove them if we do!
    for (int index = 0; index < noValuesTemps; index++)
    {
        if (IndicesTemp[index] >= workingSize)
        {
            std::count << "WARNING\nIndex exceeds size of working memory buffer\n"
            std::count << "Zeroing it\n"
            ValuesTemp[index] = 0;
            IndicesTemp[index] = 0;
        }
    }

    //Free our old values and transfer
    free(convIndices);
    free(convValues);
    noConvValues = noValuesTemp;
    convIndices = IndicesTemp;
    convValues = ValuesTemp;
}

void CICBase::i64InOutSet(int64_t* input, int64_t* output)
//Sets the input and output vectors to operate on
{
    i64Input = input;
    i64Output = output;
}

ConvolveHighFs::runFilter(uint64_t steps);
{

}
