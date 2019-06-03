#include <stdio.h>

int KPMStringSearch(char* src, int srcLen, char* find, int findLen)
{
	int srcCompareAt = 0;
	int findCompareAlsoAt = 0;

	// walk the whole string
	while (srcCompareAt < srcLen) {
		// compare chars with an index for each string
		if (src[srcCompareAt] != find[findCompareAlsoAt]) {
			// if we were on a streak of finding chars
			// reset the 'find' string index to 0
			// but don't increment
			if (findCompareAlsoAt > 0) {
				findCompareAlsoAt = 0;
			} else {
				srcCompareAt++;
			}
		} else {
			findCompareAlsoAt++;
			srcCompareAt++;
			if (findCompareAlsoAt == findLen) {
				return srcCompareAt - findCompareAlsoAt;
			}
		}
	}
}

int main()
{
	char* testSrc = "this is an exaexample string";
	int testSrcLen = 25;
	char* testFind = "example";
	int testFindLen = 7;
	int expectAnswer = 14;

	int foundAt = KPMStringSearch(
		testSrc, testSrcLen, testFind, testFindLen);
	printf("%d = %d? %s\n",
		foundAt, expectAnswer,
		foundAt == expectAnswer ? "true" : "false");
	return 0;
}