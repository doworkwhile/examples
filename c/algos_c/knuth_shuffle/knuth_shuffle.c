#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void fillArray(int* ary, int aryLen)
{
	for (int i = 0; i < aryLen; i++) {
		ary[i] = i;
	}
}

void printArray(int* ary, int aryLen)
{
	for (int i = 0; i < aryLen; i++) {
		printf("%d ", ary[i]);
	}
	printf("\n");
}

void knuthShuffle(int* ary, int aryLen)
{
	for (int i = 1; i < aryLen; i++) {
		int outer = aryLen - i;
		int swap = rand() % outer;
		int temp = ary[swap];
		ary[swap] = ary[outer];
		ary[outer] = temp;
	}
}

int main()
{
	srand(time(NULL));

	int aryLen = 10;
	int ary[aryLen];
	int* ary_ptr = &ary[0];

	fillArray(ary_ptr, aryLen);
	printArray(ary_ptr, aryLen);
	knuthShuffle(ary_ptr, aryLen);
	printArray(ary_ptr, aryLen);

	return 0;
}
