#include <iostream>
#include <stdlib.h>

using namespace std;

void fillArray(int* ary, int max, int valRange)
{
  for (int i = 0; i < max; i++) {
    ary[i] = rand() % valRange;
  }
}

void printArray(int* ary, int from, int to)
{
  int i = from;
  for (; i < to - 1; ++i) {
    cout << ary[i] << " ";
  }
  cout << ary[i] << endl;
}

int partition(int* ary, int max, int pivot)
{
  int left = -1;
  int right = max;

  while(true) {
    while(left < right && ary[++left] < pivot);
    while(right > left && ary[--right] > pivot);

    if (left >= right) {
      break;
    }

    swap(ary[left], ary[right]);
  }
  return left;
}


int main()
{
  srand(time(NULL));

  int aryLen = 10;
  int randRange = 100;
  int ary[aryLen] = {0};
  int pivotVal = 50;

  fillArray(ary, aryLen, randRange);
  printArray(ary, 0, aryLen);
  cout << "pivoting on " << pivotVal << endl;
  int partitionedAt = partition(ary, aryLen, pivotVal);
  cout << "partitions: " << endl;
  printArray(ary, 0, partitionedAt);
  printArray(ary, partitionedAt, aryLen);

  return 0;
}


