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
    lastDirRight = False
    while top != None and top.v != v:
      if v > top.v:
        last = top
        top = top.right
        lastDirRight = True
      elif v < top.v:
        last = top
        top = top.left
        lastDirRight = False
    if not top.v == v: # node does not exist
      return
    # now top.v == v

    # if no children, simply disconnect from parent   
    if not top.right and not top.left:
      if not last: # if we are the head, we don't have parents
        self.head = None
      else:
        if lastDirRight:
          last.right = None
        else:
          last.left = None
      return

    # if only right child
    if top.right and not top.left:
      if not last:
        self.head = top.right
      else:
        if lastDirRight:
          last.right = top.right
        else:
          last.left = top.right
      return

    # if only left child
    if top.left and not top.right:
      if not last:
        self.head = top.left
      else:
        if lastDirRight:
          last.right = top.left
        else:
          last.left = top.left
      return

    # must be both children
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






bt = BinaryTree()
bt.create(Leaf(5))
bt.create(Leaf(8))
bt.create(Leaf(7))
bt.create(Leaf(9))
print bt.head.v
print bt.head.right.v
print bt.head.right.left.v
print bt.head.right.right.v