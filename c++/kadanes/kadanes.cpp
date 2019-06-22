#include <iostream>
#include "../knuth_shuffle/knuth_shuffle.h"
#include "kadanes.h"

int main() {
  // the size of an array, and the array
  int aryLen = 10;
  int ary[aryLen];
  int* aryPtr = &ary[0];

  // half of the array size
  int halfAryLen = aryLen / 2;
  int lastAryIndex = aryLen - 1;

  // fill the array with values shifted by half the array size + 1
  for (int i = 0; i < aryLen; i++) {
    ary[i] = i - halfAryLen + 1;
  }

  // print the array
  for (int i = 0; i < lastAryIndex; i++) {
    std::cout << ary[i] << " ";
  }
  std::cout << ary[lastAryIndex] << std::endl;

  // shuffle the array
  knuthShuffle(aryPtr, aryLen);

  // print the array
  for (int i = 0; i < lastAryIndex; i++) {
    std::cout << ary[i] << " ";
  }
  std::cout << ary[lastAryIndex] << std::endl;

  // run the kadanes algorithm
  struct KadanesResult result;
  Kadanes(&result, aryPtr, aryLen);

  // print the results
  std::cout << "Max Sub-Array Total: " << result.max << std::endl;
  std::cout << "Max Sub-Array Item Count: " << result.itemsLen << std::endl;
  std::cout << "Max Sub-Array Items: [ ";
  for (int i = 0; i < result.itemsLen; i++) {
    std::cout << result.items[i] << " ";
  }
  std::cout << "]" << std::endl;

  // clean up
  KadanesResult_Free(&result);

  return 0;
}