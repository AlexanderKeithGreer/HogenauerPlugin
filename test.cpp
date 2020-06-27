//Testing file for the functions etc that I'm slowly building up.
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include "cicBase.hpp"
#include "cicRealisations.hpp"

using namespace std;

void iterPrint(int64_t* data, uint64_t n)
{
    for (uint64_t index = 0; index < n; index++)
    {
        cout << data[index] << ", ";
    }
    cout << "\n";
}

int main()
{
  int64_t p = 1024;
  int64_t n = -1024;

  //int64_t data0[20] = {1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0};
  int64_t data0[20] = {p, n, p, n, p, n, p, n, p, n, p, n, p, n, p, n, p, n, p, n};
  //int64_t data0[20] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int64_t out0[10] = {};
  CICInterpolator InterpTest (4, 1, 1);

  CICDecimator DeciTest (2, 2, 1);
  DeciTest.i64InOutSet(data0, out0);
  DeciTest.runFilter(10);
  iterPrint(out0, 10);

  return 0;
}
