# list union
# add unique elements from l2 to l1
def union(l1, l2):
  for el in l2:
    if el not in l1:
      l1.append(el)

### Usage:
# acd = AhoCorasickDictionaries
# acd.add('blah')
# acd.search('blah')
# call acd.build, to precompile the dictionaries -before- searching
# but acd.search will call acd.build if it was not already called
class AhoCorasickDictionaries:
  def __init__(self):
    self.transitions = {}
    self.alphabet = {}
    self.fallbacks = {}
    self.outputs = {}
    self.uniqIndex = 0
    self.built = False

  ### Step 1: Add a word, create transitions mark output state for full word
  def add(self, word):
    state = 0
    for letter in word:
      if (state, letter) in self.transitions:
        state = self.transitions[(state, letter)]
      else:
        self.uniqIndex += 1
        self.transitions[(state, letter)] = self.uniqIndex
        state = self.uniqIndex

    # add the full word to it's ending state
    if state not in self.outputs:
      self.outputs[state] = []
    self.outputs[state].append(word)

    # mark unbuilt
    self.built = False

  ### Step 2-4: Compile from added words
  def build(self):
    self.__buildAlphabetFromTransitions()

    self.__buildFallbackDefaults()

    self.__buildFallbacksAndAlphabetDefaultsAndSharedOutputsWithQueue()

    # mark built
    self.built = True

  ### Step 2: Alphabet from transitions
  def __buildAlphabetFromTransitions(self):
    for t in self.transitions:
      if not t[0] in self.alphabet:
        self.alphabet[t[0]] = []
      self.alphabet[t[0]].append(t[1])

  ### Step 3: Fallback defaults
  def __buildFallbackDefaults(self):
    for a in self.alphabet:
      if a is not 0:
        self.fallbacks[a] = 0

  ### Step 4: Transition traversal using queue
  ### Step 4a: Fallback generation
  ### Step 4b: Output state duplication
  def __buildFallbacksAndAlphabetDefaultsAndSharedOutputsWithQueue(self):
    if len(self.alphabet) is 0:
      return

    que = [self.transitions[0, l] for l in self.alphabet[0]]
    while (len(que) > 0):
      check = que.pop(0)

      if check in self.alphabet:
        for a in self.alphabet[check]:
          t = self.fallbacks[check]

          while t and (t, a) not in self.transitions:
            t = self.fallbacks[t]

          snext = self.transitions[(check, a)]
          fsnext = 0
          if (t, a) in self.transitions:
            fsnext = self.transitions[(t, a)]
          self.fallbacks[snext] = fsnext

          if not snext in self.outputs:
            self.outputs[snext] = []
          if not fsnext in self.outputs:
            self.outputs[fsnext] = []
          union(self.outputs[snext], self.outputs[fsnext])

          que.append(snext)
      else:
        self.alphabet[check] = []

  # return an array of matches on the text using our dictionaries
  def search(self, text):
    # make sure to rebuild after adding more words
    if not self.built:
      self.build()

    ret = []
    state = 0
    for index, char in enumerate(text):
      # falling back
      while state and (state, char) not in self.transitions:
        state = self.fallbacks[state]

      # transition
      if (state, char) in self.transitions:
        state = self.transitions[(state, char)]
      else:
        state = 0

      # output
      if state in self.outputs and self.outputs[state]:
        ret.append((index, self.outputs[state]))
    return ret

  def display(self):
    print('=== Transitions ===')
    for t in self.transitions:
      print t, '=', self.transitions[t]

    print('=== Alphabet ===')
    for a in self.alphabet:
      print a, '=', self.alphabet[a]

    print('=== Fallbacks ===')
    for f in self.fallbacks:
      print f, '=', self.fallbacks[f]

    print('=== Outputs ===')
    for o in self.outputs:
      print o, '=', self.outputs[o]
