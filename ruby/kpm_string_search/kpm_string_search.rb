def kpmStringSearch(toSearch, toFind)
  i = 0
  j = 0
  endLen = toFind.size
  maxSearchLen = toSearch.size

  while i < maxSearchLen
    searchVal = toSearch[i]
    findVal = toFind[j]

    if (searchVal != findVal)
      if (j > 0)
        j = 0
      else
        i += 1
      end
    else
      i += 1
      j += 1
      return i - j if j == endLen
    end
  end

  # not found
  return -1
end

toFind = "jump"
toSearch = "the quick brown fox jumps over the lazy dog"
puts kpmStringSearch(toSearch, toFind)

toSearch = " jumjumps over the lazy dog"
puts kpmStringSearch(toSearch, toFind)

toSearch = "the quick brown fox over the lazy dog"
puts kpmStringSearch(toSearch, toFind)

toFind = "example"
toSearch = "here is a simple example"
puts kpmStringSearch(toSearch, toFind)