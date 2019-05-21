import random

aryLen = 20
ary = range(1,aryLen+1)

def knuthShuffle(ary):
  aryLen = len(ary)
  for i in range(1, aryLen+1):
    j = aryLen - i
    if j > 0:
      swapI = random.randint(0, j-1)
    else:
      swapI = 0
    temp = ary[swapI]
    ary[swapI] = ary[j]
    ary[j] = temp
  pass

def bubbleSort(ary):
  aryLen = len(ary)
  for i in range(1, aryLen + 1):
    outer = aryLen - i
    for inner in range(0, outer):
      if (ary[inner] > ary[inner + 1]):
        temp = ary[inner]
        ary[inner] = ary[inner + 1]
        ary[inner + 1] = temp
  pass

print ary
knuthShuffle(ary)
print ary
bubbleSort(ary)
print ary