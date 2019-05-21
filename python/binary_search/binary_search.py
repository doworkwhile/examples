import random

aryLen = 20
ary = range(1,aryLen+1)

def binarySearch(ary, find):
  aryLen = len(ary)

  begin = 0
  end = aryLen-1

  while begin <= end:
    check = (begin + end) / 2
    checkVal = ary[check]
    if find == checkVal:
      return check
    elif find > checkVal:
      begin = check + 1
    else:
      end = check - 1
    pass

  return -1
  pass

print ary
findVal = random.randint(0, aryLen-1)+1
print 'Finding', findVal
print 'at index', binarySearch(ary, findVal)
print 'find too small', binarySearch(ary, -1)
print 'find too large', binarySearch(ary, aryLen+1)
print 'finding last = ', ary[aryLen-1]
print 'at index', binarySearch(ary, ary[aryLen-1])
print 'finding first = ', ary[0]
print 'at index', binarySearch(ary, ary[0])