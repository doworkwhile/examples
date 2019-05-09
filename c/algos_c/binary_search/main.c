#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillArray(int* ary, int aryLen)
{
	for (int i = 0; i < aryLen; i++) {
		ary[i] = i;
	}
}

void printArray(int* ary, int aryLen)
{
	int i = 0;
	for (i = 0; i < aryLen - 1; i++) {
		printf("%d ", ary[i]);
	}
	printf("%d\n", ary[i]);
}

void hideNumberRandomly(int* ary, int aryLen, int hidden)
{
	ary[rand() % aryLen] = hidden;
}

void binarySearch(int* ary, int aryLen, int hidden)
{
	int low = 0;
	int high = aryLen - 1;
	int check;
	int found;
	int iters = 1;

	printf("searching for %d ", hidden);

	while (low <= high) {
		check = (low + high) / 2;
		found = ary[check];

		if (found == hidden) {
			printf("FOUND AT %d & ITERATIONS = %d\n", check, iters);
			return;
		} else if (found > hidden) {
			high = check - 1;
		} else {
			low = check + 1;
		}
		iters++;
	}
	printf("NOT FOUND & ITERATIONS = %d\n", iters);
}

int main()
{
	srand(time(NULL));

	int aryLen = 10;
	int hidden = -1;
	int* ary = (int*) calloc(aryLen, sizeof(int));
	fillArray(ary, aryLen);
	printArray(ary, aryLen);

	for (int i = -1; i <= 10; i++) {
		binarySearch(ary, aryLen, i);
	}
	free(ary);

	return 0;
}
