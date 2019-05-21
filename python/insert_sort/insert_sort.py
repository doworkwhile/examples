import random

aryLen = 10
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

def insertSort(ary):
  aryLen = len(ary)
  for i in range(1, aryLen):
    j = i
    while j > 0 and ary[j] < ary[j-1]:
      temp = ary[j]
      ary[j] = ary[j-1]
      ary[j-1] = temp
      j -= 1
      pass
  pass

print ary
knuthShuffle(ary)
print ary
insertSort(ary)
print ary