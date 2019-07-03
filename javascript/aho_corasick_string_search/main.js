const AhoCorasickTrie = require('./aho_corasick_trie.js');

const act = new AhoCorasickTrie();

const matchWords = [ 'ring', 'ing', 'sink', 'car' ];
const findIn = 'darling caring car sinking in helsinki';

console.log("Dictionary: ", matchWords);
console.log("Search String: ", findIn);

for (let word of matchWords) {
  act.add(word);
}
act.build();
act.display();
const results = act.search(findIn);
console.log("Results");
console.log(results);
