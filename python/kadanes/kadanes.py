import random

def max_subarray(ary):
  max_sub = 0
  max_total = 0
  sub_items = []
  max_items = []
  for i in ary:
    max_sub = max(0, max_sub + i)

    did_go_higher = max_sub > max_total
    did_zero_sub = max_sub == 0

    max_total = max(max_total, max_sub)
    
    did_sync_max = max_total != 0 and max_total == max_sub
    did_not_sync_and_not_zero = not did_sync_max and not did_zero_sub

    if did_zero_sub:
      sub_items = []
    if did_sync_max or did_not_sync_and_not_zero:
      sub_items.append(i)
    if did_sync_max and did_go_higher:
      max_items = sub_items[:]

  return [max_items, max_total]

def knuthShuffle(ary):
  aryLen = len(ary)
  for i in xrange(0, aryLen - 1):
    swapIndex = random.randint(i + 1, aryLen - 1)
    ary[swapIndex] += ary[i]
    ary[i] = ary[swapIndex] - ary[i]
    ary[swapIndex] -= ary[i] 

ary = range(-3, 5)
knuthShuffle(ary)
print ary
print max_subarray(ary)