#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void fillArray(int* ary, int aryLen, int randMin, int randMax)
{
	for (int i = 0; i < aryLen; i++) {
		ary[i] = randMin + (rand() % (randMax - randMin));
	}
}

void printArray(int* ary, int aryLen)
{
	for (int i = 0; i < aryLen; i++) {
		printf("%d ", ary[i]);
	}
	printf("\n");
}

void mergeSortRecurse(int* ary, int* copy, int left, int right)
{
	int size = right - left;
	int mid = left + (size / 2);
	if (size == 1) {
		return;
	}
	// if size > 2, we can recurse on our left/right parts
	if (size > 2) {
		mergeSortRecurse(ary, copy, left, mid);
		mergeSortRecurse(ary, copy, mid, right);
	}

	// copy the l/r parts in ascending order into a copy array
	int lbegin = left;
	int rbegin = mid;
	for (int i = 0; i < size; i++) {
		if (lbegin == mid) { // done with left
			copy[left + i] = ary[rbegin];
			rbegin++;
		} else if (rbegin == right) { // done with right
			copy[left + i] = ary[lbegin];
			lbegin++;
		} else {
			int lsmaller = ary[lbegin] < ary[rbegin];
			if (lsmaller) {
				copy[left + i] = ary[lbegin];
				lbegin++;
			} else {
				copy[left + i] = ary[rbegin];
				rbegin++;
			}
		}
	}

	// copy the sorted items back
	for (int i = 0; i < size; i++) {
		ary[left + i] = copy[left + i];
	}
}

void mergeSort(int* ary, int aryLen)
{
	int copy[aryLen];
	int* copy_ptr = &copy[0];
	for (int i = 0; i < aryLen; i++) {
		copy[i] = ary[i];
	}
	mergeSortRecurse(ary, copy_ptr, 0, aryLen);
}

int main()
{
	srand(time(NULL));

	int randMin = 10;
	int randMax = 100;
	int aryLen = 10;
	int ary[aryLen];
	int* ary_ptr = &ary[0];

	fillArray(ary_ptr, aryLen, randMin, randMax);
	printArray(ary_ptr, aryLen);
	mergeSort(ary_ptr, aryLen);
	printArray(ary_ptr, aryLen);


	return 0;
}