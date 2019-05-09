function findTheNonRepeatingNumbers(ary) {
  console.log("searching array:\n", ary);
  var dict = {};

  ary.forEach((e) => {
    if (dict[e] === undefined) {
      dict[e] = false;
    } else if ( dict[e] == false ) {
      dict[e] = true;
    }
  });

  var no_repeats = [];

  for (var key of Object.keys(dict)) {
    if ( dict[key] == false ) {
      // object key becomes a string, convert back to number
      no_repeats.push( Number(key) );
    }
  }

  return no_repeats;
}

console.log( findTheNonRepeatingNumbers([1, 2, 3, 2, 1, 4]) );
console.log( findTheNonRepeatingNumbers([2, 1, 3, 2]) );
