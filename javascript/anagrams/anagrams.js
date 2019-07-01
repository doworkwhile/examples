const readline = require('readline');

const readlineInterface = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

function anagramRotate (chars, at) {
  if (at >= chars.length) {
    return;
  }

  const temp = chars[at];
  for (let i = at; i < chars.length - 1; i++) {
    chars[i] = chars[i + 1];
  }
  chars[chars.length - 1] = temp;
}

function anagramRecurse (chars, at) {
  const end = chars.length - at;
  if (end == 1) {
    return;
  }

  for (let i = 0; i < end; i++) {
    anagramRecurse(chars, at + 1);
    if (end == 2) {
      console.log(chars.join(''));
    }
    anagramRotate(chars, at);
  }
}

function anagrams (input) {
  let chars = input.split('');
  anagramRecurse(chars, 0);
}

readlineInterface.question('Input a string to anagram > ', (input) => {
  anagrams(input);
  readlineInterface.close();
});

