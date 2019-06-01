function kpmStringSearch (toSearch, toFind) {
  let i = 0;
  let j = 0;
  let endLen = toFind.length;
  let maxSearchLen = toSearch.length;

  while (i < maxSearchLen) {
    let searchVal = toSearch[i];
    let findVal = toFind[j];

    if (searchVal != findVal) {
      if (j > 0) {
        j = 0;
      } else {
        i += 1;
      }
    } else {
      i += 1;
      j += 1;
      if (j == endLen) {
        return i - j;
      }
    }
  }

  // not found
  return -1;
}

let toFind = "jump";
let toSearch = "the quick brown fox jumps over the lazy dog";
console.log(kpmStringSearch(toSearch, toFind));

toSearch = " jumjumps over the lazy dog";
console.log(kpmStringSearch(toSearch, toFind));

toSearch = "the quick brown fox over the lazy dog";
console.log(kpmStringSearch(toSearch, toFind));

toFind = "example";
toSearch = "here is a simple example";
console.log(kpmStringSearch(toSearch, toFind));