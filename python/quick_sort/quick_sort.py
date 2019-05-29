from random import shuffle

def swap(ary, i, j):
  if i == j:
    return
  ary[i] += ary[j]
  ary[j] = ary[i] - ary[j]
  ary[i] -= ary[j]

def quickSortRecurse(ary, left, right):
  if (left < right):
    pivot = ary[right]

    i = left - 1
    for j in xrange(left, right):
      if ary[j] < pivot:
        i += 1
        swap(ary, i, j)

    pivotIndex = i + 1
    swap(ary, pivotIndex, right)

    quickSortRecurse(ary, left, pivotIndex - 1)
    quickSortRecurse(ary, pivotIndex + 1, right)


def quickSort(ary):
  quickSortRecurse(ary, 0, len(ary) - 1)

ary = list(reversed(range(1, 10)))
shuffle(ary)
print ary
quickSort(ary)
print ary