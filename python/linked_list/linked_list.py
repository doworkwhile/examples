import random;

class Node():
  def __init__(self, v, nxt):
    self.value = v
    self.nxt = nxt

class LinkedList():
  def __init__(self):
    self.head = None

  def add(self, v):
    if not self.head:
      self.head = Node(v, None)
      return
    if v < self.head.value:
      self.head = Node(v, self.head)
      return

    current = self.head
    while current.nxt and current.nxt.value < v:
      current = current.nxt
      pass
    current.nxt = Node(v, current.nxt)

  def to_s(self):
    ret = '['
    current = self.head
    while current:
      ret += str(current.value)
      if current.nxt:
        ret += ', '
      current = current.nxt
    ret += ']'
    return ret

  def find(self, v):
    current = self.head
    while current:
      if current.value == v:
        return current
      current = current.nxt
    return current

  def getIndexOf(self, v):
    current = self.head
    i = 0
    while current:
      if current.value == v:
        return i
      current = current.nxt
      i += 1
    return -1


randLen = 10
randMin = 10
randMax = 100
randVals = [ random.randint(randMin, randMax - 1) for i in xrange(0, randLen)]
print randVals

ll = LinkedList()
for i in randVals:
  ll.add(i)

print ll.to_s()
findVal = random.sample(randVals, 1)[0]
print 'finding', findVal, '@ index', ll.getIndexOf(findVal)


    