import random

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

ary = [0,1,2,3,4,5,6,7,8,9]
print ary
knuthShuffle(ary)
print ary