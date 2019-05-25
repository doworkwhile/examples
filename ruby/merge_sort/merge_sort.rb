def merge_sort_recurse(ary, copy, left, right)
  size = right - left
  mid = (left + right) / 2
  return if (size == 1) # can't sort only 1 element

  # divide in half and sort the sections
  if (size > 2)
    merge_sort_recurse(ary, copy, left, mid)
    merge_sort_recurse(ary, copy, mid, right)
  end

  # after sorting our l/r sections
  # copy the items from the sections, in ascending order
  # into a temp ary
  lbegin = left
  rbegin = mid 
  for i in 0...size
    if (lbegin == mid) # left is done, copy right
      copy[left + i] = ary[rbegin]
      rbegin += 1
    elsif (rbegin == right) # right is done, copy left
      copy[left + i] = ary[lbegin]
      lbegin += 1
    else # copy smallest of l/r
      if ary[lbegin] < ary[rbegin]
        copy[left + i] = ary[lbegin]
        lbegin += 1
      else
        copy[left + i] = ary[rbegin]
        rbegin += 1
      end
    end
  end

  # copy the order of the temp array back into the original array
  for i in 0...size
    ary[left + i] = copy[left + i]
  end
end

def merge_sort(ary)
  aryLen = ary.size
  copy = [*0...aryLen]
  merge_sort_recurse(ary, copy, 0, aryLen)
end


randMin = 10
randMax = 100
aryLen = 10
ary = [*0...aryLen].map { |e| randMin + rand(randMax - randMin) }
puts ary.to_s
merge_sort(ary)
puts ary.to_s