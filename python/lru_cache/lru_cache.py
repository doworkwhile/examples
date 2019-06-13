from collections import deque

class LRUCache:
  def __init__(self, size=10):
    self.size = size
    self.count = 0
    self.que = deque(maxlen=size)
    self.cache = {}

  def get(self, key):
    value = self.cache.get(key)
    if not value:
      return -1

    self.que.remove(key)
    self.que.appendleft(key)
    return value

  def put(self, key, val):
    if self.count == self.size:
      invalid = self.que.pop()
      del self.cache[invalid]
    else:
      self.count += 1
    self.cache[key] = val
    self.que.appendleft(key)

lruc = LRUCache(2)

print 'lruc test'
lruc.put(1, 1);
lruc.put(2, 2);
print lruc.get(1) == 1;       # returns 1
lruc.put(3, 3);               # evicts key 2
print lruc.get(2) == -1;      # returns -1 (not found)
lruc.put(4, 4);               # evicts key 1
print lruc.get(1) == -1;      # returns -1 (not found)
print lruc.get(3) == 3;       # returns 3
print lruc.get(4) == 4;       # returns 4
