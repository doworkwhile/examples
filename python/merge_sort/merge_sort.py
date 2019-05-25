from random import shuffle

def mergeSortRecurse(ary, copy, left, right):
  size = right - left
  # can't sort only 1 element
  if (size == 1):
    return

  # size > 2, we can split in half and recurse onto both
  mid = (left + right) / 2
  if (size > 2):
    mergeSortRecurse(ary, copy, left, mid)
    mergeSortRecurse(ary, copy, mid, right)

  # implicit size >= 2, sort our halves into ascending order
  lbegin = left
  rbegin = mid
  i = 0
  # while both sections have items
  while (lbegin < mid and rbegin < right):
    if (ary[lbegin] < ary[rbegin]):
      copy[left + i] = ary[lbegin]
      lbegin += 1
    else:
      copy[left + i] = ary[rbegin]
      rbegin += 1
    i += 1
  # one of the sections is finished, copy the rest from the unfinished side
  while (lbegin < mid):
    copy[left + i] = ary[lbegin]
    lbegin += 1
    i += 1
  while (rbegin < right):
    copy[left + i] = ary[rbegin]
    rbegin += 1
    i += 1

  # write the values from ordered copy back into the original
  for i in xrange(size):
    ary[left + i] = copy[left + i]

def mergeSort(ary):
  aryLen = len(ary)
  copy = range(aryLen)
  mergeSortRecurse(ary, copy, 0, aryLen)

aryLen = 20
ary = range(aryLen)
shuffle(ary)
print ary
mergeSort(ary)
print ary