#include <stdio.h>
#include "knuth_shuffle.h"

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