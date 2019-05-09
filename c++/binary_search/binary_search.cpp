#include <iostream>
#include <stdlib.h>

using namespace std;

void fillArray(int* ary, int aryLen, int valRange, int valFind)
{
  for (int i = 0; i < aryLen; i++) {
    ary[i] = rand() % valRange;
  }

  int findIndex = rand() % aryLen; 
  ary[findIndex] = valFind;
  cout << "inserted " << valFind << endl; 
}

void printArray(int* ary, int aryLen)
{
  int i = 0;
  for (; i < aryLen - 1; i++) {
    cout << ary[i] << " ";
  }
  cout << ary[i] << endl;
}

void binarySearch(int* ary, int aryLen, int valFind)
{
  int begin = 0;
  int end = aryLen - 1;
  int check;
  int found;

  cout << "searching for " << valFind << endl;
  while(begin <= end) {
    check = (begin + end) / 2;
    found = ary[check];

    if (found == valFind) {
      cout << "Found at index " << check << endl;
      return;
    } else if (found > valFind) {
      end = check - 1;
    } else if (found < valFind) {
      begin = check + 1;
    }
  }
  cout << "Value was not found!" << endl;
}

int main()
{
  srand(time(NULL));

  int aryLen = 10;
  int ary[aryLen] = {0,1,2,3,4,5,6,7,8,9};

  printArray(ary, aryLen);
  for (int i = -1; i <= aryLen; ++i)
  {
    binarySearch(ary, aryLen, i);
    cout << endl;
  }
}
