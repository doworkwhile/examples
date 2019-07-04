class Leaf():
  def __init__(self, v, left=None, right=None):
    self.v = v
    self.left = left
    self.right = right

class BinaryTree():
  def __init__(self):
    self.head = None

  def create(self, l):
    if not self.head:
      self.head = l
      return

    top = self.head
    while top.v != l.v:
      if l.v > top.v:
        if not top.right:
          top.right = l
        top = top.right
      else: # l.v < top.v
        if not top.left:
          top.left = l
        top = top.left

  def read(self, v):
    if not self.head:
      return None

    top = self.head
    while top != None and top.v != v:
      if v > top.v:
        top = top.right
      elif v < top.v:
        top = top.left
    return top

  def delete(self, v):
    if not self.head:
      return None

    # find node of value v, also store the parent
    last = None
    top = self.head
    while top.v != v:
      last = top
      if v > top.v:
        top = top.right
      elif v < top.v:
        top = top.left
      if not top: # could not find value
        return None
    lastDirRight = False if last == None else (last.right == top)

    if top.right and top.left:
      self.__deleteWhenLeafHasBothChildren(top)
    elif top.right:
      self.__deleteWhenLeafHasOneChild(top.right, last, lastDirRight)
    elif top.left:
      self.__deleteWhenLeafHasOneChild(top.left, last, lastDirRight)
    else:
      self.__deleteWhenLeafHasOneChild(None, last, lastDirRight)

  def __deleteReplaceTop(self, top, last, lastDirRight):
    if not last:
      self.head = top
    else:
      if lastDirRight:
        last.right = top
      else:
        last.left = top

  def __deleteWhenLeafHasBothChildren(self, top):
    # top.right is guaranteed to not be nil
    minParent = top.right
    minAtRight = top.right
    while minAtRight.left != None:
      minParent = minAtRight
      minAtRight = minAtRight.left

    top.v = minAtRight.v
    if minParent == minAtRight:
      top.right = None
    else:
      minParent.left = minAtRight.right

  def printTree(self):
    self.printRecursive(self.head, 0)

  def printRecursive(self, node, depth):
    if not node:
      return
    self.printRecursive(node.right, depth + 1)
    for i in xrange(depth):
      print '-----|',
    print node.v
    self.printRecursive(node.left, depth + 1)

  def makeLinkedList(self):
    grandparent = None
    parent = self.head
    leftChild = None

    while parent:
      leftChild = parent.left

      if leftChild:
        if grandparent:
          grandparent.right = leftChild
        else:
          self.head = leftChild

        parent.left = leftChild.right
        leftChild.right = parent

        parent = leftChild
      else:
        grandparent = parent
        parent = parent.right

  def makeBalanced(self):
    self.makeLinkedList

    leafCount = 0
    current = self.head
    while current:
      leafCount += 1
      current = current.right

    msbOf = leafCount + 1
    msbShifts = 0
    while (msbOf > 1):
      msbOf = msbOf >> 1
      msbShifts += 1
    levelRotations = (1 << msbShifts) - 1
    firstRotations = leafCount - levelRotations
    self.doBalanceRotations(firstRotations)

    while levelRotations > 1:
      levelRotations /= 2
      self.doBalanceRotations(levelRotations)

  def doBalanceRotations(self, rotations):
    grandparent = None
    parent = self.head
    rightChild = parent.right

    while rotations > 0:
      if not rightChild:
        break

      if grandparent:
        grandparent.right = rightChild
      else:
        self.head = rightChild
      parent.right = rightChild.left
      rightChild.left = parent

      grandparent = rightChild
      parent = grandparent.right
      rightChild = parent.right if parent else None

      rotations -= 1

  def isSymmetricWalk(self):
    if not self.head:
      return True

    return self.isSymmetricWalkRecurse(self.head.left, self.head.right)


  def isSymmetricWalkRecurse(self, left, right):
    if not left and not right:
      return True
    if not left or not right:
      return False

    return self.isSymmetricWalkRecurse(left.left, right.right) and self.isSymmetricWalkRecurse(left.right, right.left)

  def clear(self):
    self.head = None

  def isSymmetricCount(self):
    kq = self.isSymmetricCountRecurse(self.head, [0, 0])
    return kq[0] is kq[1]

  def isSymmetricCountRecurse(self, start, collect):
    if not start:
      return collect

    if start.left:
      collect[0] += 1

    if start.right:
      collect[1] += 1

    self.isSymmetricCountRecurse(start.left, collect)
    self.isSymmetricCountRecurse(start.right, collect)

    return collect

  def reverse(self):
    self.reverseRecurse(self.head)

  def reverseRecurse(self, start):
    if not start:
      return

    temp = start.left
    start.left = start.right
    start.right = temp

    self.reverseRecurse(start.left)
    self.reverseRecurse(start.right)




def ap(t, v):
  t.create(Leaf(v))
  t.printTree()
  print 'count symmetric?', bt.isSymmetricCount()
  print 'walk symmetric?', bt.isSymmetricWalk()
  print

bt = BinaryTree()

ap(bt, 10)
ap(bt, 5)
ap(bt, 7)
ap(bt, 2)
ap(bt, 15)
ap(bt, 12)
ap(bt, 18)

bt.reverse()
bt.printTree()
