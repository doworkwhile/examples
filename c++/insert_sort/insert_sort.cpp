#include <iostream>
#include <stdlib.h>

using namespace std;

void fillArray(int* ary, int max, int valRange)
{
  int halfRange = valRange / 2;
  for (int i = 0; i < max; i++) {
    ary[i] = (rand() % valRange) - halfRange;
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

void insertSort(int* ary, int max)
{
  for (int i = 1; i < max; i++) {
    for (int j = i; j > 0 && ary[j] < ary[j - 1]; j--) {
      swap(ary[j], ary[j-1]);
    }
  }
}

int main()
{
  srand(time(NULL));

  int ary_count_min = 2;
  int ary_count_max = 10;
  for (int i = 2; i <= ary_count_max; ++i) {
    int ary[i] = {};
    int* ary_ptr = &ary[0];

    fillArray(ary_ptr, i, 2000);
    printArray(ary_ptr, i);
    insertSort(ary_ptr, i);
    printArray(ary_ptr, i);
    cout << endl;
  }
  return 0;
}