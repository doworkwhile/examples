import random

def partition(ary, pivot):
  left = -1
  right = len(ary)

  while left < right:
    while left < right:
      left = left + 1
      if ary[left] > pivot:
        break
    while right > left:
      right = right - 1
      if ary[right] < pivot:
        break

    temp = ary[left]
    ary[left] = ary[right]
    ary[right] = temp

  return left

randMin = 10
randMax = 100
pivot = (randMin + randMax) / 2
aryLen = 10
ary = random.sample(xrange(randMin, randMax + 1), aryLen)
print ary
print 'pivot on', pivot
partAt = partition(ary, pivot)
print 'part at', partAt
print ary