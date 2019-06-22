const sieve = function (n) {

  // no primes besides 1 below 2
  const prime_minimum = 2;

  // all composite numbers greater than this have smaller divisors
  const prime_maximum = Math.sqrt(n);

  // the arrays are 0-indexed and we start at 2 so ..
  // the size of the array is n-1 to exclude the digit '1'
  const list = new Array(n - 1).fill(true);

  // 'i' here represents the integer whose multiples are obviously composite
  // 'i' is NOT THE ARRAY INDEX
  for (let i = prime_minimum; i < prime_maximum; i++) {
    // again, the arrays are 0-indexed and we start at 2 so ..
    // the digit '2' is at index 0, so the index of any integer is really i-2

    // skip any number already marked composite
    // it's multiples will already be marked
    if ( list[ i - 2 ] ) {

      // mark the multiple of i as composite ( but not i )
      // by setting its related index to false
      // (we will filter all false values)
      for(let j = i*i; j <= n; j += i) {
        list[j - 2] = false;
      }
    }
  }


  return list
    // each index of the array represents the digit index+2
    .map( (e,i) => e ? i+2 : false )

    // filter the indexes marked false
    .filter(e => !!e);
};

module.exports = sieve;