#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "cicBase.hpp"

using namespace std;

void CICBase::initCIC (uint64_t r, uint64_t d, uint64_t s)
{
    rCIC = r;
    dCIC = d;
    sCIC = s;

    //The data we need is S integrator memory blocks
    // And SD integrator memory delay blocks
    //I'm going to lump this data together such that it's all in one vector.
    //This is because I don't care to see if putting it not together makes a
    // difference to the cache load times.
    i64Memory = (int64_t*) calloc (s * (d + 1), sizeof(int64_t));
}

void CICBase::clearMemory (void)
//Checks to see if any heap is being used, and clears it if it isn't
{
    free(i64Memory);
}

void CICBase::i64InOutSet (int64_t* input, int64_t* output)
//Sets the input and output vectors to operate on
{
    i64Input = input;
    i64Output = output;
}
