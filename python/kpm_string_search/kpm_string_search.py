def kpmStringSearch(toSearch, toFind):
  i = 0
  j = 0
  endLen = len(toFind)
  maxSearchLen = len(toSearch)

  while i < maxSearchLen:
    searchVal = toSearch[i]
    findVal = toFind[j]

    if (searchVal != findVal):
      if (j > 0):
        j = 0
      else:
        i += 1
    else:
      i += 1
      j += 1
      if j == endLen:
        return i - j

  # not found
  return -1

toFind = "jump"
toSearch = "the quick brown fox jumps over the lazy dog"
print kpmStringSearch(toSearch, toFind)

toSearch = " jumjumps over the lazy dog"
print kpmStringSearch(toSearch, toFind)

toSearch = "the quick brown fox over the lazy dog"
print kpmStringSearch(toSearch, toFind)

toFind = "example"
toSearch = "here is a simple example"
print kpmStringSearch(toSearch, toFind)