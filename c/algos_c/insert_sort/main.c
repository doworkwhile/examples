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

void insertSort(int* ary, int aryLen)
{
	for (int i = 1; i < aryLen; i++) {
		int check = ary[i];
		int countBack = i - 1;
		for (; countBack >= 0 && check < ary[countBack]; countBack--) {
			ary[countBack+1] = ary[countBack];
		}
		ary[countBack+1] = check;
	}
}

void scrambleArray(int* ary, int aryLen)
{
	for (int i = aryLen - 1; i > 0; i--) {
		int swapAt = rand() % i;
		int temp = ary[swapAt];
		ary[swapAt] = ary[i];
		ary[i] = temp;
	}
}

int main()
{
	srand(time(NULL));

	int aryMin = 2;
	int aryMax = 10;
	int randRange = 100;

	for (int i = aryMin; i <= aryMax; i++) {
		int* ary = (int*) calloc(i, sizeof(int));
		fillArrayRandom(ary, i, randRange);
		printArray(ary, i);
		insertSort(ary, i);
		printArray(ary, i);
		printf("shuffle\n");
		scrambleArray(ary, i);
		printArray(ary, i);
		insertSort(ary, i);
		printArray(ary, i);
		printf("\n");
		free(ary);
	}
}