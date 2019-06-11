class ChainedHashMap:
  def __init__(self, n = 100):
    self.n = n
    self.contents = [[] for i in xrange(n)]

  def insert(self, key, n):
    i = self.hash_func(key)
    self.contents[i].append((key, n))

  def hash_func(self, key):
    return hash(key) % self.n

  def __getitem__(self, key):
    i = self.hash_func(key)
    chain = self.contents[i]
    if len(chain) == 0:
      return None

    for c in xrange(len(chain)):
      if chain[c][0] == key:
        return chain[c][1]

chm = ChainedHashMap()

keys = []
for i in xrange(10):
  key = hash(str(i))
  keys.append(key)
  chm.insert(key, i)

print chm.contents
for i in keys:
  print i, '=', chm[i]
print 'cat = ', chm['cat']
