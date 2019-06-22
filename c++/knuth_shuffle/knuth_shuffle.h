#ifndef KNUTH_SHUFFLE
#define KNUTH_SHUFFLE

#include <algorithm>
#include <time.h>

void knuthShuffle(int* ary, int aryLen)
{
  srand(time(NULL));
  for (int i = aryLen - 1; i > 0; i--) {
    int swapIndex = rand() % i;
    std::swap(ary[swapIndex], ary[i]);
  }
}

#endif