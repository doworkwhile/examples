#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillArray(int* ary, int aryLen, int randMin, int randMax)
{
	for (int i = 0; i < aryLen; i++) {
		ary[i] = randMin + (rand() % (randMax - randMin));
	}
}
int partition(int* ary, int aryLen, int pivot)
{
	int left = -1;
	int right = aryLen;

	while(left < right) {
		while(left < right && ary[++left] < pivot) {}
		while(right > left && ary[--right] > pivot) {}
		int temp = ary[left];
		ary[left] = ary[right];
		ary[right] = temp;
	}

	return left;
}

int main()
{
	srand(time(NULL));

	int aryLen = 10;
	int ary[aryLen];
	int* ary_ptr = &ary[0];
	int randMin = 10;
	int randMax = 100;
	int pivot = (randMin + randMax) / 2;

	fillArray(ary_ptr, aryLen, randMin, randMax);
	for (int i = 0; i < aryLen; i++) {
		printf("%d ", ary[i]);
	}
	printf("\n");
	int partAt = partition(ary_ptr, aryLen, pivot);
	printf("part at %d\n", partAt);
	for (int i = 0; i < aryLen; i++) {
		if (i == partAt) {
			printf("- ");
		}
		printf("%d ", ary[i]);
	}
	printf("\n");
}