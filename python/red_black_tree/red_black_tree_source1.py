### helper methods, reduce `self.` and null checking
def is_red(n):
  return n.red if n else False

def is_black(n):
  return not n.red if n else False

def get_left(n):
  return n.left if n else None

def get_right(n):
  return n.right if n else None

def get_parent(n):
  return n.parent if n else None

def get_sibling(n):
  if not n or not get_parent(n):
    return None
  nParent = get_parent(n)
  return get_right(nParent) if n == get_left(nParent) else get_left(nParent)

def get_grandparent(n):
  return get_parent(get_parent(n))

def get_max_on_left(n):
  search = n.left
  if search:
    while search.right:
      search = search.right
  return search

def set_color(n, red):
  if n:
    n.red = red

def get_color(n):
  if n:
    return n.red

def set_left(n, left):
  if n.left:
    n.left.parent = None
  if left:
    detach_parent(left)
    left.parent = n
  n.left = left

def set_right(n, right):
  if n.right:
    n.right.parent = None
  if right:
    detach_parent(right)
    right.parent = n
  n.right = right

def detach_parent(n):
  if n and n.parent:
    if n == n.parent.left:
      n.parent.left = None
    else:
      n.parent.right = None
### end helper methods

class RBNode:
  def __init__(self, value, red=True, parent=None, left=None, right=None):
    self.value = value
    self.red = red
    self.parent = parent
    self.left = left
    self.right = right

  def nstr(self):
    return str(self.value) + ("R" if self.red else "B")

class RBTree:
  def __init__(self):
    self.head = None

  # mostly the same as a BinaryTree insert
  # but after the node is inserted call insert_adjust(node)
  def insert(self, value):
    if not self.head:
      self.head = RBNode(value)
      self.insert_adjust(self.head)
      return

    search = self.head
    while search.value != value:
      if value < search.value:
        if not search.left:
          set_left(search, RBNode(value, parent=search))
          self.insert_adjust(search.left)
        search = search.left
      elif value > search.value:
        if not search.right:
          set_right(search, RBNode(value, parent=search))
          self.insert_adjust(search.right)
        search = search.right

  def find(self, value):
    if not self.head:
      return None

    search = self.head
    while True:
      if value == search.value:
        return search
      if value < search.value:
        if not search.left:
          return None
        search = search.left
      elif value > search.value:
        if not search.right:
          return None
        search = search.right

  def delete(self, value):
    node = self.find(value)
    if not node:
      return

    # swap values with the max node to the left
    if node.left and node.right:
      maxLeft = get_max_on_left(node)
      node.value = maxLeft.value
      node = maxLeft
      # the below calculations are now on the node we swapped values with

    # we know there is only a left child
    # because get_max_on_left would have moved right again
    if node.left:
      if node == self.head:
        self.head = node.left
      elif node == node.parent.left:
        set_left(node.parent, node.left)
      else: # node == node.parent.right:
        set_right(node.parent, node.left)

      if not node.red:
        self.delete_adjust(node)
    elif node == self.head:
      self.head = None
    else:
      if not node.red:
        self.delete_adjust(node)
      detach_parent(node)

  def rotate_right(self, n):
    if not n.left:
      return

    lastLeft = n.left
    set_left(n, lastLeft.right)
    if not get_parent(n):
      self.head = lastLeft
    elif n == get_left(get_parent(n)):
      set_left(get_parent(n), lastLeft)
    else:
      set_right(get_parent(n), lastLeft)
    set_right(lastLeft, n)

  def rotate_left(self, n):
    if not n.right:
      return

    lastRight = n.right
    set_right(n, lastRight.left)
    if not get_parent(n):
      self.head = lastRight
    elif n == get_left(get_parent(n)):
      set_left(get_parent(n), lastRight)
    else:
      set_right(get_parent(n), lastRight)
    set_left(lastRight, n)

  def insert_adjust(self, n):
    # unless our parent is red, no need to adjust
    if n and self.head != n and is_red(get_parent(n)):
      # if both siblings of the parent are red
      if is_red(get_sibling(get_parent(n))):
        # make parent and sibling black
        set_color(get_parent(n), False)
        set_color(get_sibling(get_parent(n)), False)
        # make grandparent red
        set_color(get_grandparent(n), True)
        # rerun adjustment on red grandparent
        self.insert_adjust(get_grandparent(n))
      # if our parent is our grandparents left
      elif get_parent(n) == get_left(get_grandparent(n)):
        # if n is our parents right, rotate left, set n to the new parent
        if n == get_right(get_parent(n)):
          self.rotate_left(n = get_parent(n))
        # set our parent black
        set_color(get_parent(n), False)
        # set our grandparent red
        set_color(get_grandparent(n), True)
        # rotate our grandparent right
        self.rotate_right(get_grandparent(n))
      # if our parent is our grandparents right
      elif get_parent(n) == get_right(get_grandparent(n)):
        # if n is our parents left, rotate right, set n to the new parent
        if n == get_left(get_parent(n)):
          self.rotate_right(n = get_parent(n))
        # set our parent black
        set_color(get_parent(n), False)
        # set our grandparent red
        set_color(get_grandparent(n), True)
        # rotate our grandparent left
        self.rotate_left(get_grandparent(n))
    # ensure head is black
    set_color(self.head, False)

  def delete_adjust(self, n):
    while n != self.head and not n.red:
      # if n is left of parent
      if n == get_left(get_parent(n)):
        # hold the (right) sibling
        sibling = get_right(get_parent(n))
        # if our sibling is red
        if is_red(sibling):
          # set the sibling to black, the parent to red
          set_color(sibling, False)
          set_color(get_parent(n), True)
          # rotate left
          self.rotate_left(get_parent(n))
          # get the new sibling
          sibling = get_right(get_parent(n))

        # if sibling children are both black
        if is_black(get_left(sibling)) and is_black(get_right(sibling)):
          # sibling becomes red
          set_color(sibling, True)
          # re-iterate with the parent
          n = get_parent(n)
        # if only 1 child is black
        else:
          # if sibling right child is black
          if is_black(get_right(sibling)):
            # set the sibling left to black, and the sibling to red
            set_color(get_left(sibling), False)
            set_color(sibling, True)
            # rotate right
            self.rotate_right(sibling)
            # get the new sibling
            sibling = get_right(get_parent(n))
          # set the sibling to the color of n's parent
          set_color(sibling, get_color(get_parent(n)))
          # set the parent to black
          set_color(get_parent(n), False)
          # set the sibling right black
          set_color(get_right(sibling), False)
          # rotate parent left
          self.rotate_left(get_parent(n))
          # n is the new head
          n = self.head
      # if n is right of parent
      else:
        # this is a mirror of the above
        # the sibling is now the left
        # the rotations are also mirrored
        sibling = get_left(get_parent(n))
        if is_red(sibling):
          set_color(sibling, False)
          set_color(get_parent(n), True)
          self.rotate_right(get_parent(n))
          sibling = get_left(get_parent(n))

        if is_black(get_left(sibling)) and is_black(get_right(sibling)):
          set_color(sibling, True)
          n = get_parent(n)
        else:
          if is_black(get_left(sibling)):
            set_color(get_right(sibling), False)
            set_color(sibling, True)
            self.rotate_left(sibling)
            sibling = get_left(get_parent(n))
          set_color(sibling, get_color(get_parent(n)))
          set_color(get_parent(n), False)
          set_color(get_left(sibling), False)
          self.rotate_right(get_parent(n))
          n = self.head
      set_color(n, False)

  def to_s(self):
    if not self.head:
      return "[ ]"

    nodes = []
    self.to_s_recurse(self.head, nodes)

    return "[ " + ", ".join(map(lambda n: n.nstr(), nodes)) + " ]"

  def to_s_recurse(self, node, collection):
    if not node:
      return

    self.to_s_recurse(node.left, collection)
    collection.append(node)
    self.to_s_recurse(node.right, collection)

  def to_print(self, top, depth):
    if not self.head:
      print "(Empty)"

    if not top:
      return

    self.to_print(top.right, depth + 1)
    for i in xrange(0, depth):
      print "----|",
    print top.nstr()
    self.to_print(top.left, depth + 1)

  def clear(self):
    self.head = None



### Driver
rbt = RBTree()
for i in reversed(xrange(1, 16)):
  rbt.insert(i)
print rbt.to_s()
print

rbt.to_print(rbt.head, 0)

print
rbt.delete(20)
rbt.to_print(rbt.head, 0)

print
rbt.clear()
rbt.to_print(rbt.head, 0)

print
rbt.insert(50)
rbt.to_print(rbt.head, 0)
