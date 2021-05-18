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
  int64_t p = 16;
  int64_t n = -16;

  int64_t data0[10] = {p, n, p, n, p, n, p, n, p, n};
  int64_t data1[4] = {p, n, p, n};
  int64_t data2[4] = {p, p, -p, p};
  int64_t data3[20] = {1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0};
  int64_t data4[20] = {1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0};
  int64_t out0[20] = {};
  CICInterpolator InterpTest (3, 2, 2);

  CICDecimator DeciTest (2, 1, 1);
  //InterpTest.i64InOutSet(data2, out0);
  //InterpTest.runFilter(4);
  DeciTest.i64InOutSet(data4, out0);
  DeciTest.runFilter(20);
  iterPrint(out0, 10);

  return 0;
}
