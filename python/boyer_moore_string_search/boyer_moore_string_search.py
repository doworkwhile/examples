def getComparisonIndexes(indexCount, toFind):
  indexes = [-1] * indexCount
  for i, c in enumerate(toFind):
    indexes[ord(c)] = i
  return indexes

def boyerMooreStringSearch(toSearch, toFind):
  endLen = len(toFind)
  maxSearchLen = len(toSearch)
  lastfindIndex = endLen - 1
  i = lastfindIndex
  j = lastfindIndex
  indexes = getComparisonIndexes(256, toFind)

  while i < maxSearchLen:
    searchVal = toSearch[i]
    findVal = toFind[j]
    if searchVal != findVal:
      j = lastfindIndex
      lastIndexInFindOfVal = indexes[ord(searchVal)]
      if lastIndexInFindOfVal > -1:
        i += endLen - (lastIndexInFindOfVal + 1)
      else:
        i += j + 1
    else:
      i -= 1
      j -= 1
      if j == 0:
        return i - j
  return -1

toFind = "jump"
toSearch = "the quick brown fox jumps over the lazy dog"
print boyerMooreStringSearch(toSearch, toFind)

toSearch = " jum jumps over the lazy dog"
print boyerMooreStringSearch(toSearch, toFind)

toSearch = "the quick brown fox over the lazy dog"
print boyerMooreStringSearch(toSearch, toFind)

toFind = "example"
toSearch = "here is a simple example"
print boyerMooreStringSearch(toSearch, toFind)