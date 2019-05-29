#include <stdio.h>

void swap(int* ary, int i, int j) {
	if (i == j) { // Important!
		return;
	}
	ary[i] += ary[j];
	ary[j] = ary[i] - ary[j];
	ary[i] -= ary[j];
}

void fillArray(int* aryPtr, int aryLen)
{
	for (int i = 0; i < aryLen; i++) {
		aryPtr[i] = aryLen - i;
	}
}

void printArray(int* aryPtr, int aryLen)
{
	for (int i = 0; i < aryLen; i++) {
		printf("%d ", aryPtr[i]);
	}
	printf("\n");
}

void quickSortRecurse(int* aryPtr, int left, int right)
{
	if (left < right) {
		// stage 1 pivot
		int pivot = aryPtr[right];

		// stage 2 stack < pivot to left
		int i = left - 1;
		for (int j = left; j < right; j++) {
			if (aryPtr[j] < pivot) {
				swap(aryPtr, ++i, j);
			}
		}

		// stage 3 insert pivot
		int pivotIndex = i + 1;
		swap(aryPtr, pivotIndex, right);

		// stage 4 recurse on sections
		quickSortRecurse(aryPtr, left, pivotIndex - 1);
		quickSortRecurse(aryPtr, pivotIndex + 1, right);
	}
}

void quickSort(int* aryPtr, int aryLen)
{
	quickSortRecurse(aryPtr, 0, aryLen - 1);
}

int main()
{
	int aryLen = 10;
	int ary[aryLen];
	int* aryPtr = &ary[0];

	fillArray(aryPtr, aryLen);
	printArray(aryPtr, aryLen);
	quickSort(aryPtr, aryLen);
	printArray(aryPtr, aryLen);
}