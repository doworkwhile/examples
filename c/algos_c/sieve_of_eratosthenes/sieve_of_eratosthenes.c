#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct SieveResult
{
	int* results;
	int resultsLen;
} SieveResult;

void sieve(SieveResult* result, int n)
{
	int primeMinimum = 2;
	int primeMaximum = (int) sqrt(n);
	int nSkip1 = n - 1;

	/* create an array of length n - 1 to store the numbers
	 * that are being tested for primality.
	 * use n - 1 because the search starts from 2 instead of 1.
	 * every int should have the same initial state of 0.
	 */
	int* options = calloc(nSkip1, sizeof(int));

	// mark every non prime with 1
	// this is the 'Sieve of Eratosthenes'
	for (int i = primeMinimum; i < primeMaximum; i++) {
		if (options[i - primeMinimum] == 0) {
			for (int j = i * i; j <= n; j += i) {
				options[j - primeMinimum] = 1;
			}
		}
	}

	// now that all primes are marked 1
	// count the primes to set an array size
	int primeCount = 0;
	for (int i = 0; i < nSkip1; i++) {
		if (options[i] == 1) {
			primeCount++;
		}
	}

	// collect the primes in an array
	int* filtered = calloc(primeCount, sizeof(int));
	int filteredLen = 0;
	for (int i = 0; i < nSkip1; i++) {
		if (options[i] == 0) {
			filtered[filteredLen++] = i + primeMinimum;
		}
	}

	// free the array of numbers that were primality tested
	free(options);

	// set the values of the result object
	result->results = filtered;
	result->resultsLen = filteredLen;
}

int main()
{
	SieveResult result;
	sieve(&result, 100);

	printf("[ ");
	for (int i = 0; i < result.resultsLen; i++) {
		printf("%d ", result.results[i]);
	}
	printf("]\n");

	free(result.results);
	return 0;
}