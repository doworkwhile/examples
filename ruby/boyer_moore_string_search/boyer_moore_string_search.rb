def getComparisonIndexes(indexCount, toFind)
  indexes = [-1] * indexCount
  toFind.chars.each_with_index { |c, i|
    indexes[c.ord] = i
  }
  indexes
end

def boyerMooreStringSearch(toSearch, toFind)
  endLen = toFind.size
  maxSearchLen = toSearch.size
  lastfindIndex = endLen - 1
  i = lastfindIndex
  j = lastfindIndex
  indexes = getComparisonIndexes(256, toFind)

  while i < maxSearchLen
    searchVal = toSearch[i]
    findVal = toFind[j]
    if searchVal != findVal
      j = lastfindIndex
      lastIndexInFindOfVal = indexes[searchVal.ord]
      if lastIndexInFindOfVal > -1
        i += endLen - (lastIndexInFindOfVal + 1)
      else
        i += j + 1
      end
    else
      i -= 1
      j -= 1
      return i - j if j == 0
    end
  end

  return -1
end

toFind = "jump"
toSearch = "the quick brown fox jumps over the lazy dog"
puts boyerMooreStringSearch(toSearch, toFind)

toSearch = " jum jumps over the lazy dog"
puts boyerMooreStringSearch(toSearch, toFind)

toSearch = "the quick brown fox over the lazy dog"
puts boyerMooreStringSearch(toSearch, toFind)

toFind = "example"
toSearch = "here is a simple example"
puts boyerMooreStringSearch(toSearch, toFind)