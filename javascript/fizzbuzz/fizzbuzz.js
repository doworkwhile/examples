function fizzbuzz(max) {
  if (max < 1) { return; }
  for (let i = 1; i <= max; i++) {
    let m3 = !( i % 3 );
    let m5 = !( i % 5 );
    if (m3 && m5) {
      console.log("FizzBuzz");
    } else if (m3) {
      console.log("Fizz");
    } else if (m5) {
      console.log("Buzz");
    } else {
      console.log( i );
    }
  }
}

fizzbuzz( 20 );
