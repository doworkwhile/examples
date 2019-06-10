import math

class PriorityQueue():
  def __init__(self):
    self.contents = []

  def add(self, item, priority):
    self.contents.append( (item, priority) )
    self.heapUp()

  def poll(self):
    contentLen = len(self.contents)
    if contentLen == 0:
      return None
    if contentLen == 1:
      return self.contents.pop()[0]

    item = self.contents[0]
    self.contents[0] = self.contents.pop()
    self.heapDown()
    return item[0]

  # re-ordering
  def heapUp(self):
    current = len(self.contents) - 1

    while self.isParentDisordered(current):
      parentIndex = self.getParentIndex(current)
      self.swap(current, parentIndex)
      current = parentIndex

  def heapDown(self):
    current = 0
    nxt = None

    while self.hasLeft(current):
      if self.isRightLeftOrdered(current):
        nxt = self.getRightIndex(current)
      else:
        nxt = self.getLeftIndex(current)

      if self.isOrdered(self.contents[current], self.contents[nxt]):
        break

      self.swap(current, nxt)
      current = nxt

  # order validation
  def isOrdered(self, above, below):
    return above[1] < below[1]

  def isParentDisordered(self, i):
    return\
      self.hasParent(i) and\
      not self.isOrdered(self.parent(i), self.contents[i])

  def isRightLeftOrdered(self, i):
    return\
       self.hasRight(i) and\
       self.isOrdered(self.right(i), self.left(i))

  # contents of parent, left, right
  def parent(self, i):
    return self.contents[self.getParentIndex(i)]

  def left(self, i):
    return self.contents[self.getLeftIndex(i)]

  def right(self, i):
    return self.contents[self.getRightIndex(i)]

  # presence of parent, left, right
  def hasParent(self, i):
    return self.getParentIndex(i) >= 0

  def hasLeft(self, i):
    return self.getLeftIndex(i) < len(self.contents)

  def hasRight(self, i):
    return self.getRightIndex(i) < len(self.contents)

  # indexes of parent, left right
  def getParentIndex(self, i):
    return int(math.floor((i - 1) / 2))

  def getLeftIndex(self, i):
    return (2 * i) + 1

  def getRightIndex(self, i):
    return (2 * i) + 2

  def swap(self, a, b):
    temp = self.contents[a]
    self.contents[a] = self.contents[b]
    self.contents[b] = temp

  def isEmpty(self):
    return len(self.contents) == 0

  def __str__(self):
    return str(self.contents)

  def __repr__(self):
    return str(self.contents)
