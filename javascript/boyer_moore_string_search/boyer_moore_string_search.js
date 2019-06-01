function getComparisonIndexes (indexCount, toFind) {
  let indexes = new Array(indexCount).fill(-1);
  for (let i = 0; i < toFind.length; i++) {
    indexes[ toFind.charCodeAt(i) ] = i;
  }
  return indexes;
}

function boyerMooreStringSearch (toSearch, toFind) {
  let endLen = toFind.length;
  let maxSearchLen = toSearch.length;
  const lastfindIndex = endLen - 1;
  let i = lastfindIndex;
  let j = lastfindIndex;
  let indexes = getComparisonIndexes(256, toFind);

  while (i < maxSearchLen) {
    let searchVal = toSearch[i];
    let findVal = toFind[j];
    if (searchVal != findVal) {
      j = lastfindIndex;
      let lastIndexInFindOfVal = indexes[searchVal.charCodeAt(0)];
      if (lastIndexInFindOfVal > -1) {
        i += endLen - (lastIndexInFindOfVal + 1);
      } else {
        i += j + 1;
      }
    } else {
      i -= 1;
      j -= 1;
      if (j == 0) {
        return i - j;
      }
    }
  }

  return -1;
}

let toFind = "jump";
let toSearch = "the quick brown fox jumps over the lazy dog";
console.log(boyerMooreStringSearch(toSearch, toFind));

toSearch = " jum jumps over the lazy dog";
console.log(boyerMooreStringSearch(toSearch, toFind));

toSearch = "the quick brown fox over the lazy dog";
console.log(boyerMooreStringSearch(toSearch, toFind));

toFind = "example";
toSearch = "here is a simple example";
console.log(boyerMooreStringSearch(toSearch, toFind));