import math

class Heap:
  def __init__(self):
    self.contents = []

  def add(self, v):
    self.contents.append(v)
    self.heapUp()

  def find(self, v):
    items = []

    for i in xrange(0, len(self.contents)):
      if self.contents[i] == v:
        items.append(i)

    return items

  def peek(self):
    if len(self.contents) > 0:
      return self.contents[0]

  def poll(self):
    contentLen = len(self.contents)
    if contentLen == 0:
      return None
    if contentLen == 1:
      return self.contents.pop()

    item = self.contents[0]
    self.contents[0] = self.contents.pop()
    self.heapDown()
    return item

  def remove(self, v):
    foundItems = self.find(v)

    # remove ALL instances
    for i in xrange(0, len(foundItems)):
      # because we fix the tree after every removal
      # we have to recheck which indexes our item is at
      firstRemoveIndex = self.find(v).pop()

      # if found is last in array
      if firstRemoveIndex == len(self.contents) - 1:
        self.contents.pop()
      else:
        # move last item to index of found item
        self.contents[firstRemoveIndex] = self.contents.pop()

        # heap down without both a left item and
        # a missing or correctly ordered parent
        if self.hasLeft(firstRemoveIndex) and\
          self.hasNoParentOrIsParentOrdered(firstRemoveIndex):
          self.heapDown(firstRemoveIndex)
        else:
            self.heapUp(firstRemoveIndex)

  def heapUp(self, startAt=None):
    current = startAt or len(self.contents) - 1

    while self.hasParent(current) and self.getParentDisordered(current):
      parentIndex = self.getParentIndex(current)
      self.swap(current, parentIndex)
      current = parentIndex

  def heapDown(self, startAt = 0):
    current = startAt
    nxt = None

    while self.hasLeft(current):
      if self.hasRight(current) and self.getChildrenOrdered(current):
        nxt = self.getRightIndex(current)
      else:
        nxt = self.getLeftIndex(current)

      if self.getOrdered(self.contents[current], self.contents[nxt]):
        break

      self.swap(current, nxt)
      current = nxt

  def left(self, i):
    return self.contents[self.getLeftIndex(i)]

  def right(self, i):
    return self.contents[self.getRightIndex(i)]

  def hasLeft(self, i):
    return self.getLeftIndex(i) < len(self.contents)

  def hasRight(self, i):
    return self.getRightIndex(i) < len(self.contents)

  def getLeftIndex(self, i):
    return (2 * i) + 1

  def getRightIndex(self, i):
    return (2 * i) + 2

  def parent(self, i):
    return self.contents[self.getParentIndex(i)]

  def hasParent(self, i):
    return self.getParentIndex(i) >= 0

  def getParentIndex(self, i):
    return int(math.floor((i - 1) / 2))

  def getParentDisordered(self, i):
    return not self.getOrdered(self.parent(i), self.contents[i])

  def getChildrenOrdered(self, i):
    return self.getOrdered(self.right(i), self.left(i))

  def hasNoParentOrIsParentOrdered(self, i):
    return\
      not self.parent(i) or \
      self.getOrdered(self.parent(i), self.contents[i])

  def swap(self, above, below):
    temp = self.contents[below]
    self.contents[below] = self.contents[above]
    self.contents[above] = temp

  def __str__(self):
    return self.contents.__str__()

class MinHeap(Heap):
  def __init__(self):
    Heap.__init__(self)

  def getOrdered(self, above, below):
    return above < below


class MaxHeap(Heap):
  def __init__(self):
    Heap.__init__(self)

  def getOrdered(self, above, below):
    return above > below


items = [25, 2, 75, 54, 73, 99, 3]

minh = MinHeap()
maxh = MaxHeap()

for i in items:
  minh.add(i)
  maxh.add(i)

print minh
print maxh

for i in xrange(0, len(items) / 2):
  print minh.poll()
print minh
minh.remove(minh.contents[1])
print minh

for i in xrange(0, len(items) / 2):
  print maxh.poll()
print maxh
maxh.remove(maxh.contents[1])
print maxh
