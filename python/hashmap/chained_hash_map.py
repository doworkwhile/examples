class ChainedHashNode:
  def __init__(self, key, n, nxt=None):
    self.key = key
    self.n = n
    self.nxt = nxt

  def __repr__(self):
    return str((self.key, self.n))

class ChainedHashMap:
  def __init__(self, n = 100):
    self.n = n
    self.contents = [[] for i in xrange(n)]
    self.head = None

  def insert(self, key, n):
    i = self.hash_func(key)
    newNode = ChainedHashNode(key, n)
    self.contents[i].append(newNode)

    if not self.head or self.compare(n, self.head.n):
      newNode.nxt = self.head
      self.head = newNode
      return

    current = self.head
    while current.nxt and self.compare(current.nxt.n, n):
      current = current.nxt
    newNode.nxt = current.nxt
    current.nxt = newNode


  def compare(self, left, right):
    return left > right


  def hash_func(self, key):
    return hash(key) % self.n

  def __getitem__(self, key):
    i = self.hash_func(key)
    chain = self.contents[i]
    for c in xrange(len(chain)):
      if chain[c].key == key:
        return chain[c]

chm = ChainedHashMap(5)

keys = [25, 40, 75, 60, 4, 12, 99]
for k in keys:
  chm.insert(k, k)

current = chm.head
while current:
  print current
  current = current.nxt

print chm[keys[3]]
