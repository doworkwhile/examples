class LLNode:
  def __init__(self, symbol, freq):
    self.symbol = symbol
    self.freq = freq
    self.prefix = None
    self.next = None
    self.left = None
    self.right = None

class LL:
  def __init__(self):
    self.head = None

  def insert(self, node):
    if not self.head:
      self.head = node
      return

    if node.freq < self.head.freq:
      node.next = self.head
      self.head = node
      return

    search = self.head
    while search.next and search.next.freq < node.freq:
      search = search.next
    node.next = search.next
    search.next = node

  def pop(self):
    if not self.head:
      return None
    ret = self.head
    self.head = self.head.next
    return ret

  def to_s(self):
    if not self.head:
      return '[]'

    ret = '[ %d'%(self.head.freq)
    current = self.head.next
    if current:
      ret +=', '
      while current:
        ret += str(current.freq)
        current = current.next
        if current:
          ret += ', '
    ret += ' ]'
    return ret

class HuffmanTree():
  def __init__(self, ll):
    self.head = None
    self.buildTreeFromLL(ll)
    self.buildPrefixes(self.head, None, False)

  def buildTreeFromLL(self, ll):
    while True:
      popFirst = ll.pop()
      popSecond = ll.pop()

      if not popSecond:
        self.head = popFirst
        return

      newFreq = popFirst.freq + popSecond.freq
      newLeaf = LLNode("$", newFreq)
      newLeaf.left = popFirst
      newLeaf.right = popSecond
      ll.insert(newLeaf)

  def buildPrefixes(self, top, last, wasRight):
    if not top:
      return

    top.prefix = ""
    if last:
      top.prefix = last.prefix
      top.prefix += "1" if wasRight else "0"

    self.buildPrefixes(top.left, top, False)
    self.buildPrefixes(top.right, top, True)

  def to_s(self, top, depth):
    if not top:
      return

    self.to_s(top.right, depth+1)
    for i in xrange(0, depth):
      print "---|",
    print top.symbol, top.freq, top.prefix
    self.to_s(top.left, depth+1)



ordAstart = ord('a')
alphaLen = 26
symbols = list(map(chr, range(ordAstart, ordAstart + alphaLen)))
freqs = range(1, 1 + alphaLen)
# symbols = (" ", "a", "m", "l", "f", "t")
# freqs = (20, 40, 10, 7, 8, 15)
datas = [LLNode(symbols[i], freqs[i]) for i in xrange(0, alphaLen)]

for i in xrange(0, alphaLen):
  print symbols[i], freqs[i]

ll = LL()
for i in datas:
  ll.insert(i)
print ll.to_s()

ht = HuffmanTree(ll)
ht.to_s(ht.head, 0)
# print ll.head.freq

for i in datas:
  print i.symbol, i.prefix


text = "hello"

for c in text:
  print c, datas[ord(c) - ordAstart].prefix,