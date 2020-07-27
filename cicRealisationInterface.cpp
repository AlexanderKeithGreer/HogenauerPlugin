#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include "cicBase.hpp"
#include "cicRealisations.hpp"

//  A set of wrappers around the C++ classes I've written such that
//    they can be passed around from python!

extern "C" {
    ////////////////////////////////////////////////////////////////////////
    // DECIMATOR
    ////////////////////////////////////////////////////////////////////////
    CICDecimator* CICDecimatorI(uint64_t r, uint64_t d, uint64_t s)
    {
        return new CICDecimator(r, d, s);
    }

    void CICDecimatorRunFilter(CICDecimator* CICDecimatorO, uint64_t steps)
    {
        CICDecimatorO->runFilter(steps);
    }

    void CICDecimatorI64InOutSet(CICDecimator* CICDecimatorO, int64_t* input, int64_t* output)
    {
        CICDecimatorO->i64InOutSet(input, output);
    }

    void CICDecimatorEnd(CICDecimator* CICDecimatorO)
    {
        CICDecimatorO->clearMemory();
    }


    ////////////////////////////////////////////////////////////////////////
    // INTERPOLATOR
    ////////////////////////////////////////////////////////////////////////
    CICInterpolator* CICInterpolatorI(uint64_t r, uint64_t d, uint64_t s)
    {
        return new CICInterpolator(r, d, s);
    }

    void CICInterpolatorRunFilter(CICDecimator* CICInterpolatorO, uint64_t steps)
    {
        CICInterpolatorO->runFilter(steps);
    }

    void CICInterpolatorI64InOutSet(CICDecimator* CICInterpolatorO, int64_t* input, int64_t* output)
    {
        CICInterpolatorO->i64InOutSet(input, output);
    }

    void CICInterpolatorEnd(CICDecimator* CICInterpolatorO)
    {
        CICInterpolatorO->clearMemory();
    }


}
