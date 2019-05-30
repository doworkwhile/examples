import random

class Node:
  def __init__(self, v, nxt, prev):
    self.v = v
    self.nxt = nxt
    self.prev = prev

class DoubleLinkedList:
  def __init__(self):
    self.head = None

  def addSorted(self, v):
    temp = Node(v, None, None)
    if not self.head:
      self.head = temp
      self.head.nxt = self.head
      self.head.prev = self.head
      return

    if v < self.head.v:
      temp.nxt = self.head
      temp.prev = self.head.prev
      self.head.prev.nxt = temp
      self.head.prev = temp
      self.head = temp
      return

    last = self.head
    current = self.head.nxt
    while current != self.head and current.v < v:
      last = current
      current = current.nxt
    temp.nxt = current
    temp.prev = last
    current.prev = temp
    last.nxt = temp

  def to_s(self):
    if not self.head:
      return '[]'

    ret = '[ %d'%(self.head.v)
    current = self.head.nxt
    if current != self.head:
      ret +=', '
      while current != self.head:
        ret += str(current.v)
        if current.nxt != self.head:
          ret += ', '
        current = current.nxt
    ret += ' ]'
    return ret

  def getIndex(self, i):
    if not self.head:
      return None
    if i == 0:
      return self.head

    goingUp = i > 0
    startAt = 1 if goingUp else -1
    startNode = self.head.nxt if goingUp else self.head
    moveOp = 1 if goingUp else -1
    while startAt != i:
      startAt += moveOp
      startNode = startNode.nxt if goingUp else startNode.prev
    return startNode

  def indexOf(self, v):
    if not self.head:
      return None
    if v == self.head:
      return 0

    index = 0
    current = self.head.nxt
    while current != self.head:
      index += 1
      if current.v == v:
        return index
      current = current.nxt
    return None

  def swapIndexes(self, first, second):
    if (first == second):
      return

    firstNode = self.getIndex(first)
    secondNode = self.getIndex(second)

    if (firstNode == secondNode):
      return

    self.swapNodes(firstNode, secondNode)

  def swapNodes(self, firstNode, secondNode):
    # temp values if not adjacent
    oldsnp = secondNode.prev
    oldfnn = firstNode.nxt
    adjacent = oldsnp == firstNode

    # start unhooking in same direction as temp values
    # (sn.p & fn.n, inversion is sn.n & fn.p)
    secondNode.prev = firstNode.prev
    secondNode.prev.nxt = secondNode
    firstNode.nxt = secondNode.nxt
    firstNode.nxt.prev = firstNode

    # adjacent means first node behind(prev) second node (..->fn->sn->..)
    # if adjancent, sn and fn should link directly (..->sn->fn->..)
    # otherwise use the temp values
    if (adjacent):
      secondNode.nxt = firstNode
      firstNode.prev = secondNode
    else:
      firstNode.prev = oldsnp
      firstNode.prev.nxt = firstNode
      secondNode.nxt = oldfnn
      secondNode.nxt.prev = secondNode

    if self.head == firstNode:
      self.head = secondNode
    elif self.head == secondNode:
      self.head = firstNode

  def insertAt(self, i, v):
    nodeAt = self.getIndex(i)
    if not nodeAt:
      self.addSorted(v)
      return

    temp = Node(v, nodeAt, nodeAt.prev)
    nodeAt.prev.nxt = temp
    nodeAt.prev = temp

    if i == 0:
      self.head = temp

  def clear(self):
    self.head = None

  def insertSort(self):
    if not self.head or self.head.nxt == self.head:
      return

    outerLast = self.head
    outerNext = outerLast.nxt
    while outerNext != self.head:
      # should we step back?
      if outerLast.v > outerNext.v:
        outerMirror = outerNext
        outerBackstep = outerLast
        while outerBackstep != self.head and outerMirror.v < outerBackstep.prev.v:
          outerBackstep = outerBackstep.prev


        # moving (om)30 past (ob)90 = 30->90
        # disconnect self
        outerMirror.prev.nxt = outerMirror.nxt
        outerMirror.nxt.prev = outerMirror.prev

        # update self
        outerMirror.nxt = outerBackstep
        outerMirror.prev = outerBackstep.prev

        # update around self
        outerMirror.prev.nxt = outerMirror
        outerMirror.nxt.prev = outerMirror

        if outerBackstep == self.head:
          self.head = outerMirror
      # iterate forward
      outerLast = outerNext
      outerNext = outerNext.nxt

  def tail(self):
    return self.head.prev if self.head else None

  def lastIndex(self):
    return self.indexOf(self.tail().v) if self.tail() else None

  def shuffle(self):
    if not self.head:
      return
    li = self.lastIndex()
    for i in xrange(0, li):
      outer = li - i
      swap = random.randint(0, outer)
      self.swapIndexes(outer, swap)

  def bubbleSort(self):
    if not self.head or self.head.nxt == self.head:
      return

    outer = self.tail()
    while outer != self.head:
      current = self.head
      while current != outer:
        if (current.nxt.v < current.v and current.nxt != self.head):
          self.swapNodes(current, current.nxt)
          if current.prev == outer:
            outer = current
        else:
          current = current.nxt
      outer = outer.prev


  def find(self, v):
    if not self.head:
      return None
    if self.head.v == v:
      return self.head

    current = self.head.nxt
    while current != self.head:
      if current.v == v:
        return current
      current = current.nxt
    return None

  def to_a(self):
    if not self.head:
      return []

    ret = [ self.head.v ]
    current = self.head.nxt
    while current != self.head:
      ret.append(current.v)
      current = current.nxt
    return ret

  def delete(self, v):
    node = self.find(v)
    if not node:
      return

    self.deleteNode(node)

  def deleteAt(self, i):
    node = self.getIndex(i)
    if not node:
      return

    self.deleteNode(node)

  def deleteNode(self, n):
    n.prev.nxt = n.nxt
    n.nxt.prev = n.prev
    if n == self.head:
      self.head = n.nxt