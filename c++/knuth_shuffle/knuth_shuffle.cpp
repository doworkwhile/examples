#include <stdio.h>
#include <algorithm>
#include <time.h>

void knuthShuffle(int* ary, int aryLen)
{
  for (int i = aryLen - 1; i > 0; i--) {
    int swapIndex = rand() % i;
    std::swap(ary[swapIndex], ary[i]);
  }
}

int main()
{
  srand(time(NULL));

  int aryLen = 10;
  int ary[aryLen];
  for (int i = 0; i < aryLen; i++) {
    ary[i] = i;
    printf("%d ", ary[i]);
  }
  printf("\n");

  knuthShuffle(&ary[0], aryLen);

  for (int i = 0; i < aryLen; i++) {
    printf("%d ", ary[i]);
  }
  printf("\n");
}