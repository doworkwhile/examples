class AhoCorasickNode():
  def __init__(self, letter):
    self.letter = letter
    self.children = []
    self.word = None
    self.prevLink = None
    self.letterChain = None
    self.suffixLink = None
    self.outputLink = None

  def setWord(self, word):
    self.word = word

  def childHasLetter(self, letter):
    found = None
    for child in self.children:
      if child.letter is letter:
        found = child
    return found

  def attachChild(self, child):
    self.children.append(child)

  def display(self, depth = 0):
    for i in xrange(depth):
      print '----|',
    print self.letter or "(root)",
    if self.word:
      print "(", self.word, ")",
    if self.suffixLink:
      print "[", self.suffixLink.letter, '/', self.suffixLink.letterChain, ']',
    if self.outputLink:
      print "{", self.outputLink.word, '}',
    print

    for child in self.children:
      child.display(depth + 1)

class AhoCorasickTrie():
  def __init__(self):
    self.head = AhoCorasickNode('*')
    self.head.letterChain = '*'

  def add(self, word):
    current = self.head
    letterIndex = 0
    while letterIndex < len(word):
      letter = word[letterIndex]
      childWithLetter = current.childHasLetter(letter)

      if childWithLetter:
        current = childWithLetter
      else:
        newNode = AhoCorasickNode(letter)
        newNode.prevLink = current
        newNode.letterChain = word[0:letterIndex+1]
        current.attachChild(newNode)
        current = newNode

      letterIndex += 1

      # final word output
      if letterIndex is len(word):
        current.word = word

    self.buildSuffixes()
    self.buildOutputs()

  def buildSuffixes(self):
    que = [self.head]

    while len(que) > 0:
      item = que.pop(0)

      myPrev = item.prevLink
      if myPrev is self.head:
        item.suffixLink = self.head
      elif myPrev:
        backLink = myPrev
        while backLink.suffixLink:
          backLink = backLink.suffixLink
          backForLink = backLink.childHasLetter(item.letter)
          if backForLink:
            item.suffixLink = backForLink
            break
        if not item.suffixLink:
          item.suffixLink = self.head

      for child in item.children:
        que.append(child)

  def buildOutputs(self):
    que = [self.head]

    while len(que) > 0:
      item = que.pop(0)

      if item.suffixLink:
        if item.suffixLink.word:
          item.outputLink = item.suffixLink
        elif item.suffixLink.outputLink:
          item.outputLink = item.suffixLink.outputLink

      for child in item.children:
        que.append(child)

  def search(self, word):
    outputs = []

    wordIndex = 0
    searchCurrent = self.head
    while wordIndex < len(word):
      letter = word[wordIndex]
      childWithLetter = searchCurrent.childHasLetter(letter)
      while not childWithLetter and searchCurrent is not self.head:
        searchCurrent = searchCurrent.suffixLink
        childWithLetter = searchCurrent.childHasLetter(letter)

      if childWithLetter:
        if childWithLetter.word:
          outputs.append((wordIndex, childWithLetter.word))

        outputLinkChain = childWithLetter.outputLink
        while outputLinkChain:
          outputs.append((wordIndex, outputLinkChain.word))
          outputLinkChain = outputLinkChain.outputLink

        searchCurrent = childWithLetter
      wordIndex += 1

    return outputs

  def display(self):
    self.head.display()
