#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CHOICES 9
#define MAX_WEIGHT 14
#define CHOICES_ARY_MAX 10
#define MAX_WEIGHT_ARY_MAX 15

void fillArray(int* ary, int aryLen)
{
	for (int i = 0; i < aryLen; i++) {
		ary[i] = i + 1;
	}
}

void shuffleArray(int* ary, int aryLen)
{
	for (int i = aryLen - 1; i > 0; i--) {
		int swapIndex = rand() % i;

		ary[i] += ary[swapIndex];
		ary[swapIndex] = ary[i] - ary[swapIndex];
		ary[i] -= ary[swapIndex];
	}
}

void printWeightValueTable(int* w, int* v, int len)
{
	printf("w | v\n");
	printf("--|--\n");
	for (int i = 0; i < len; i++) {
		printf("%d | %d\n", w[i], v[i]);
	}
}

void printSolutionTable(int s[CHOICES_ARY_MAX][MAX_WEIGHT_ARY_MAX], int n, int W)
{
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= W; j++) {
			if (s[i][j] < 10) {
				printf(" ");
			}
			printf("%d ", s[i][j]);
		}
		printf("\n");
	}
}

int max(int a, int b)
{
	return (a > b) ? a : b;
} 

int recurseAnswer(int* w, int* v, int weightCap, int nItems)
{
	if (nItems == 0 || weightCap == 0) {
		return 0;
	}

	int lastIndex = nItems - 1;
	if (w[lastIndex] > weightCap) {
		return recurseAnswer(w, v, weightCap, lastIndex);
	}

	int newWeightCap = weightCap - w[lastIndex];
	return max(
		v[lastIndex] + recurseAnswer(w, v, newWeightCap, lastIndex),
		recurseAnswer(w, v, weightCap, lastIndex)
	);
}

int buildSolutionTable(
	int s[CHOICES_ARY_MAX][MAX_WEIGHT_ARY_MAX], int* w, int * v)
{
	for (int i = 0; i < CHOICES + 1; i++) {
		for (int j = 0; j < MAX_WEIGHT + 1; j++) {
			int lastChoice = i - 1;
			int lastWeight = w[lastChoice];
			if (i == 0 || j == 0) {
				s[i][j] = 0;
			} else if (lastWeight <= j) {
				int valInPrevRow = v[lastChoice];
				int prevWeight = w[lastChoice];
				int prvA = s[lastChoice][j-lastWeight];
				int old = valInPrevRow + prvA;
				s[i][j] = max(old, s[lastChoice][j]);
			} else {
				s[i][j] = s[lastChoice][j];
			}
		}
	}
}

int main()
{
	srand(time(NULL));

	int weights[CHOICES];
	int values[CHOICES];
	int* weights_ptr = &weights[0];
	int* values_ptr = &values[0];

	fillArray(weights_ptr, CHOICES);
	fillArray(values_ptr, CHOICES);
	shuffleArray(values_ptr, CHOICES);

	// build solution table from bottom
	int solveTable[CHOICES_ARY_MAX][MAX_WEIGHT_ARY_MAX];
	buildSolutionTable(solveTable, weights_ptr, values_ptr);
	printSolutionTable(solveTable, CHOICES, MAX_WEIGHT);
	printWeightValueTable(weights_ptr, values_ptr, CHOICES);

	// recurse from top
	printf("answer: %d\n", recurseAnswer(weights_ptr, values_ptr, MAX_WEIGHT, CHOICES));


	return 0;
}