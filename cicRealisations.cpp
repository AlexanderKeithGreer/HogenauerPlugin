#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include "cicBase.hpp"
#include "cicRealisations.hpp"

using namespace std;


////////////////////////////////////////////////////
// Explanation of CIC operation management.
////////////////////////////////////////////////////
//  This holds for both the decimators and integrators
//
//  Integrators are straightforward to implement:
//  Add the data value to the first entry to the first integrator
//    memory block. Then add each memory block to itself and the
//    next entry. Finally, pass the last value out.
//
//  Comb filters require delays, and delays that can move. This
//    probably requires circular buffers: extract the delayed
//    value, replace it with the new, move the index!
//  The right approach is to work our way through the buffer,
//    starting with the low fs input. Update the buffer in
//    each stage, then add the output to our number (passed
//    to the next stage!)
//
//  Memory is arranged (eg D=2, S=3):
//  +---+---+---+---+---+---+---+---+---+
//  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
//  +---+---+---+---+---+---+---+---+---+
//
//   I1  I2  I3  |-----> |-----> |----->
//                C1       C2      C3

////////////////////////////////////////////////////
// Interpolator Functionality
////////////////////////////////////////////////////
CICInterpolator::CICInterpolator (uint64_t r, uint64_t d, uint64_t s)
{
    initCIC(r, d, s);
}


CICInterpolator::~CICInterpolator (void)
{
    clearMemory();
}


void CICInterpolator::runFilter (uint64_t steps)
//Actually run the CIC filter
{
    cout << steps << " steps for the interpolator \n";
    cout << rCIC << " r for the interpolator \n";
    cout << sCIC << " s for the interpolator \n";
    cout << dCIC << " d for the interpolator \n";
}

////////////////////////////////////////////////////
// Decimator Functionality
////////////////////////////////////////////////////
CICDecimator::CICDecimator (uint64_t r, uint64_t d, uint64_t s)
{
    initCIC(r, d, s);
}


CICDecimator::~CICDecimator (void)
{
  clearMemory();
}


void CICDecimator::runFilter (uint64_t steps)
//Actually run the CIC filter
{


    //  Redundant definitions to improve ease of reading
    //    (I assume the compiler will optimise them away!)
    uint64_t nInteg = sCIC;
    uint64_t nComb = sCIC;
    int64_t combSwap;
    int64_t combSum = 0; // The sum of each delay + input
    uint64_t combInd = 0; // The index of the circular buffer currently being
                          //   used as an input!

    for (uint64_t stepLow = 0; stepLow < steps; stepLow++)
    {
        //Integrator section, high rate
        for (uint64_t stepHigh = 0; stepHigh < rCIC; stepHigh++)
        {
            //  Preliminary steps: the first integ in the chain needs the data
            //    value from the high rate stream!
            cout << i64Memory[0] << "memstart \n";
            cout << i64Input[stepLow*rCIC + stepHigh] << " input at " << stepLow*rCIC + stepHigh << "\n";
            i64Memory[0] = i64Input[stepLow*rCIC + stepHigh] + i64Memory[0];
            cout << i64Memory[0] << "memend \n";

            for (int64_t integ = nInteg - 1; integ >= 1; integ--)
            {
                //Do the steps assoc with each integrator
                i64Memory[integ] = i64Memory[integ] + i64Memory[integ-1];
            }
        }

        cout << "\n";
        //Comb section, low rate
        combSum = i64Memory[sCIC - 1];
        cout << combSum << "combSum start\n";
        for (uint64_t comb = 0; comb < nComb; comb++)
        {
            //Do the steps assoc with each comb
            //This index gives the current comb output. Pop, then replace.
            combSwap = i64Memory[sCIC * (1 + comb) + combInd];
            i64Memory[sCIC * (1 + comb) + combInd] = combSum;
            combSum = combSum - combSwap;
            cout << combSum << "combSum end\n";
        }
        //Finished this iteration.
        i64Output[stepLow] = combSum;
        combInd = combInd % dCIC;
        cout << "\n";
    }
}
