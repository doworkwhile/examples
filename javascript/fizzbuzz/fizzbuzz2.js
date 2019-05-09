function fizzbuzz2(max) {
  for (let i = 1; i <= max; i++) {
    let msg = '';
    if ( !(i % 3) ) { msg += 'Fizz' }
    if ( !(i % 5) ) { msg += 'Buzz' }
    console.log( msg || i );
  }
}

fizzbuzz2( 20 );
