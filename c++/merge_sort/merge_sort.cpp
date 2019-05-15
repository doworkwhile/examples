#include <stdlib.h>
#include <iostream>
#include <stdio.h>

using namespace std;

void printArray(int* ary, int size)
{
  int i = 0;
  for (; i < size - 1; i++) {
    cout << ary[i] << " ";
  }
  cout << ary[i] << endl;
}

void merge(int* ary, int* cpy, int l, int m, int r, int c)
{
  int lLen = m - l;
  int rLen = r - m;
  int i = 0;
  int j = 0;
  int w = 0;
  while (i < lLen && j < rLen) {
    if (ary[l + i] < ary[m + j]) {
      cpy[l + w] = ary[l + i];
      i++;
    } else {
      cpy[l + w] = ary[m + j];
      j++;
    }
    w++;
  }
  while(i < lLen) {
    cpy[l + w] = ary[l + i];
    i++;
    w++;
  }
  while(j < rLen) {
    cpy[l + w] = ary[m + j];
    j++;
    w++;
  }
  for (int b = l; b < l + w; b++) {
    ary[b] = cpy[b];
  }

}

void mergeSort(int* ary, int* cpy, int l, int r, int c)
{

  if (r - l < 2) {
    return;
  }

  int mid = (l + r) / 2;

  mergeSort(ary, cpy, l, mid, c+1);
  mergeSort(ary, cpy, mid, r, c+1);
  merge(ary, cpy, l, mid, r, c);
}


void fillArray(int* ary, int size, int randRange)
{
  for (int i = 0; i < size; i++) {
    ary[i] = rand() % randRange;
  }
}

int main()
{
  srand(time(NULL));

  int arrayLen = 10;
  int randRange = 100;
  int ary[arrayLen] = {0};
  int cpy[arrayLen] = {0};

  fillArray(&ary[0], arrayLen, randRange);
  printArray(&ary[0], arrayLen);
  mergeSort(&ary[0], &cpy[0], 0, arrayLen, 0);
  printArray(&ary[0], arrayLen);

  return 0;
}