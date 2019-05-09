#include <iostream>
#include <stdlib.h>

using namespace std;

void fillArray(int* ary, int max, int val_min_inclusive, int val_max_exclusive)
{
  for (int i = 0; i < max; ++i) {
    ary[i] = val_min_inclusive + (rand() % val_max_exclusive);
  }
}

void printArray(int* ary, int max)
{
  int i = 0;
  for (; i < max - 1; ++i) {
    cout << ary[i] << " ";
  }
  cout << ary[i] << endl;
}

void bubbleSort(int* ary, int max)
{
  for (int outer = max - 1; outer > 0; outer--) {
    for(int inner = 0; inner < outer; inner++) {
      if (ary[inner] > ary[inner + 1]) {
        swap(ary[inner], ary[inner + 1]);
        // int temp = ary[inner + 1];
        // ary[inner + 1] = ary[inner];
        // ary[inner] = temp;
      }
    }
  }
}

int main()
{
  srand(time(NULL));

  int ary_min_count = 2;
  int ary_max_count = 10;
  for (int i = ary_min_count; i <= ary_max_count; i++) {
    int ary[i] = {};
    int* ary_ptr = &ary[0];

    fillArray(ary_ptr, i, -1000, 2000);
    printArray(ary_ptr, i);
    bubbleSort(ary_ptr, i);
    printArray(ary_ptr, i);
    cout << endl;
  }
  return 0;
}