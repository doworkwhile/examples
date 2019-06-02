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
    lastDirRight = last == None ? False : (last.right == top)

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

  def print_tree(self):
    self.print_recursive(self.head, 0)

  def print_recursive(self, node, depth):
    if not node:
      return
    self.print_recursive(node.right, depth + 1)
    for i in xrange(depth):
      print '-----|',
    print node.v
    self.print_recursive(node.left, depth + 1)





bt = BinaryTree()
bt.create(Leaf(5))
bt.create(Leaf(8))
bt.create(Leaf(7))
bt.create(Leaf(9))
bt.print_tree()
bt.delete(8)
bt.print_tree()
# print bt.head.v
# print bt.head.right.v
# print bt.head.right.left.v
# print bt.head.right.right.v