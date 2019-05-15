#include <stdlib.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int compareCount = 0;
int insertCount = 0;
int copyCount = 0;

void printArray(int* ary, int size)
{
  int i = 0;
  for (; i < size - 1; i++) {
    cout << ary[i] << " ";
  }
  cout << ary[i] << endl;
}

void merge(int* ary, int* cpy, int l, int m, int r)
{
  int lLen = m - l;
  int rLen = r - m;
  int i = 0;
  int j = 0;
  int w = 0;
  while (i < lLen && j < rLen) {
    compareCount++;
    insertCount++;
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
    insertCount++;
    i++;
    w++;
  }
  while(j < rLen) {
    cpy[l + w] = ary[m + j];
    insertCount++;
    j++;
    w++;
  }
  for (int b = l; b < l + w; b++) {
    copyCount++;
    ary[b] = cpy[b];
  }

}

void mergeSort(int* ary, int* cpy, int l, int r)
{

  if (r - l < 2) {
    return;
  }

  int mid = (l + r) / 2;

  mergeSort(ary, cpy, l, mid);
  mergeSort(ary, cpy, mid, r);
  merge(ary, cpy, l, mid, r);
}

void fillArray(int* ary, int size, int randRange)
{
  for (int i = 0; i < size; i++) {
    ary[i] = rand() % randRange;
  }
}

void insertSort(int* ary, int max)
{
  for (int i = 1; i < max; i++) {
    for (int j = i; j > 0 && ++compareCount && ary[j] < ary[j - 1]; j--) {
      insertCount++;
      swap(ary[j], ary[j-1]);
    }
  }
}

void bubbleSort(int* ary, int max)
{
  for (int outer = max - 1; outer > 0; outer--) {
    for(int inner = 0; inner < outer; inner++) {
      if (ary[inner] > ary[inner + 1] && ++compareCount) {
        insertCount++;
        swap(ary[inner], ary[inner + 1]);
      }
    }
  }
}

int main()
{
  srand(time(NULL));

  int arrayLen = 10000;
  int randRange = 100000;
  int ary[arrayLen] = {0};
  int cpy[arrayLen] = {0};

  fillArray(&ary[0], arrayLen, randRange);
  // printArray(&ary[0], arrayLen);
  mergeSort(&ary[0], &cpy[0], 0, arrayLen);
  // printArray(&ary[0], arrayLen);
  printf("-- Merge Sort --\n");
  printf("comparisons: %d\n", compareCount);
  printf("inserts: %d\n", insertCount);
  printf("copies: %d\n", copyCount);

  compareCount = 0;
  insertCount = 0;
  fillArray(&ary[0], arrayLen, randRange);
  // printArray(&ary[0], arrayLen);
  insertSort(&ary[0], arrayLen);
  // printArray(&ary[0], arrayLen);
  printf("-- Insert Sort --\n");
  printf("comparisons: %d\n", compareCount);
  printf("inserts: %d\n", insertCount);

  compareCount = 0;
  insertCount = 0;
  fillArray(&ary[0], arrayLen, randRange);
  // printArray(&ary[0], arrayLen);
  bubbleSort(&ary[0], arrayLen);
  // printArray(&ary[0], arrayLen);
  printf("-- Bubble Sort --\n");
  printf("comparisons: %d\n", compareCount);
  printf("inserts: %d\n", insertCount);


  return 0;
}