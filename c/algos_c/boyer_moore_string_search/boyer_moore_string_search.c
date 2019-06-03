#include <stdio.h>

void fillCharCountIndexes(int* indexAry, int indexLen, char* find, int findLen)
{
	for (int i = 0; i < indexLen; i++) {
		indexAry[i] = -1;
	}
	for (int i = 0; i < findLen; i++) {
		int toCount = (int) find[i];
		if (toCount < indexLen) {
			indexAry[toCount] = i;
		}
	}
}

int BoyerMooreStringSearch(char* src, int srcLen, char* find, int findLen)
{
	// we start comparing by matching the last index of the find string
	// with the same index of the src string
	int lastFindIndex = findLen - 1;
	int srcCompareAt = lastFindIndex;
	int findCompareAt = lastFindIndex;

	// keep a record of the last index of any char in the find str
	int maxComparisonValue = 256;
	int comparisonCountIndexs[maxComparisonValue];
	fillCharCountIndexes(&comparisonCountIndexs[0], maxComparisonValue,
		find, findLen);

	// walk the length of the src string
	while (srcCompareAt <= srcLen) {
		// compare src and find with 2 indexes
		if (src[srcCompareAt] != find[findCompareAt]) {
			// load the last index of the src char in the find str
			int compareIndex = -1;
			int toFind  = (int) src[srcCompareAt];
			if (toFind > maxComparisonValue) {
				printf("index array too small: "\
				       "cannot compare value %d\n",
				       toFind);
			} else {
				compareIndex = comparisonCountIndexs[toFind];
			}

			// if we were on a streak
			if (findCompareAt != lastFindIndex) {
				// move forward by the amt of letters we had
				// moved backward
				srcCompareAt += lastFindIndex - findCompareAt;
			// if we are not on a streak, but find str has the char 
			} else if (compareIndex > 0) {
				// move forward by the distance of that char
				// from the end of the find str
				srcCompareAt += lastFindIndex - compareIndex;
			// if find str does not have that char at all
			} else {
				// move forward by the whole word
				srcCompareAt += findLen;
			}
		} else {
			// if we match a char, move backwards
			// if it was the last char, return the src compare index
			if (findCompareAt == 0) {
				return srcCompareAt;
			}
			findCompareAt--;
			srcCompareAt--;
		}
	}
	return -1;
}

int main()
{

	printf("%d\n",
		BoyerMooreStringSearch(
			"the quick brown fox jumps over the lazy dog", 43,
			"jump", 4));
	printf("%d\n",
		BoyerMooreStringSearch(
			" jum jumps over the lazy dog", 28,
			"jump", 4));
	printf("%d\n",
		BoyerMooreStringSearch(
			"the quick brown fox over the lazy dog", 37,
			"jump", 4));
	printf("%d\n",
		BoyerMooreStringSearch(
			"this is an exaexample string", 25,
			"example", 7));
	return 0;
}