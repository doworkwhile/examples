#include <iostream>
#include <stdlib.h>

using namespace std;

void fillArray(int* ary, int max, int valRange)
{
  for (int i = 0; i < max; i++) {
    ary[i] = rand() % valRange;
  }
}

void printArray(int* ary, int max)
{
  for (int i = 0; i < max; i++) {
    cout << ary[i] << " ";
  }
  cout << endl;
}

void manualSort(int* ary, int start, int end)
{
  int size = (end - start) + 1;
  if (size == 1) {
    return;
  }

  if (size == 2 && ary[start] > ary[end]) {
    swap(ary[start], ary[end]);
  } else if (size == 3) {
    if (ary[start] > ary[end - 1]) {
      swap(ary[start], ary[end - 1]);
    }

    if (ary[start] > ary[end]) {
      swap(ary[start], ary[end]);
    }

    if (ary[end - 1] > ary[end]) {
      swap(ary[end - 1], ary[end]);
    } 
  }
}

int medianPart(int* ary, int start, int end)
{
  int mid = (start + end) / 2;
  if (ary[start] > ary[mid]) {
    swap(ary[start], ary[mid]);
  }

  if (ary[start] > ary[end]) {
    swap(ary[start], ary[end]);
  }

  if (ary[mid] > ary[end]) {
    swap(ary[mid], ary[end]);
  }

  swap(ary[mid], ary[end - 1]);
  return ary[end - 1];
}

int partition(int* ary, int start, int end, int pivot)
{
  int left = start;
  int right = end - 1;

  while(true) {
    while(ary[++left] < pivot);
    while(ary[--right] > pivot);

    if (left >= right) {
      break;
    }

    swap(ary[left], ary[right]);
  }
  swap(ary[left], ary[end - 1]);
  return left;
}

void quicksort(int* ary, int start, int end)
{
  if (end - start < 1) {
    return;
  }

  if (end - start < 3) {
    manualSort(ary, start, end);
    return;
  }

  int pivot = medianPart(ary, start, end);
  int partAt = partition(ary, start, end, pivot);
  quicksort(ary, start, partAt - 1);
  quicksort(ary, partAt + 1, end);
}


int main()
{
  srand(time(NULL));

  int aryLen = 10;
  int randRange = 1000;
  int ary[aryLen] = {0};

  fillArray(ary, aryLen, randRange);
  printArray(ary, aryLen);
  quicksort(ary, 0, aryLen - 1);
  printArray(ary, aryLen);

  return 0;
}


