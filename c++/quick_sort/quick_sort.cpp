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

int partition(int* ary, int start, int end, int pivot)
{
  int left = start - 1;
  int right = end + 1;

  while(true) {
    while(ary[++left] < pivot);
    while(right > 0 && ary[--right] > pivot);

    if (left >= right) {
      break;
    }

    swap(ary[left], ary[right]);
  }
  return left;
}

void quicksort(int* ary, int start, int end)
{
  if (end - start < 1) {
    return;
  }

  int pivot = ary[end];
  int partAt = partition(ary, start, end, pivot);
  quicksort(ary, start, partAt - 1);
  quicksort(ary, partAt + 1, end);
}


int main()
{
  srand(time(NULL));

  int aryLen = 11;
  int randRange = 100;
  int ary[aryLen] = {0};
  int pivotVal = 50;

  fillArray(ary, aryLen, randRange);
  printArray(ary, 0, aryLen);
  quicksort(ary, 0, aryLen - 1);
  printArray(ary, 0, aryLen);

  return 0;
}


