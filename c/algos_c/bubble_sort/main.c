#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void fillArrayRandom(int* ary, int aryLen, int randRange)
{
	for (int i = 0; i < aryLen; i++) {
		ary[i] = rand() % randRange;
	}
}

void printArray(int* ary, int aryLen)
{
	int i;
	for (i = 0; i < aryLen - 1; i++) {
		printf("%d ", ary[i]);
	}
	printf("%d\n", ary[i]);
}

void bubbleSort(int* ary, int aryLen) {
	int out;
	int inner;
	int valLeft;
	int valRight;
	for (out = aryLen - 1; out > 0; out--) {
		for (inner = 0; inner < out; inner++) {
			valLeft = ary[inner];
			valRight = ary[inner + 1];
			if (valRight < valLeft) {
				ary[inner] = valRight;
				ary[inner + 1] = valLeft;
			}
		}
	}
}

int main()
{
	srand(time(NULL));

	int aryMin = 2;
	int aryMax = 10;
	int randRange = 1000;

	for (int i = aryMin; i <= aryMax; i++) {
		int* ary = (int*) calloc(i, sizeof(int));
		fillArrayRandom(ary, i, randRange);
		printArray(ary, i);
		bubbleSort(ary, i);
		printArray(ary, i);
		printf("\n");
	}
}