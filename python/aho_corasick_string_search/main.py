from aho_corasick_dictionaries import AhoCorasickDictionaries

findIn = 'darling caring car sinking in helsinki'
matchWords = [ 'ing', 'sink', 'car' ]

# build dictionary
acd = AhoCorasickDictionaries()
for word in matchWords:
  acd.add(word)

# prebuild to check what happened
acd.build()

print('=== Transitions ===')
for t in acd.transitions:
  print t, '=', acd.transitions[t]

print('=== Alphabet ===')
for a in acd.alphabet:
  print a, '=', acd.alphabet[a]

print('=== Fallbacks ===')
for f in acd.fallbacks:
  print f, '=', acd.fallbacks[f]

print('=== Outputs ===')
for o in acd.outputs:
  print o, '=', acd.outputs[o]

print('=== Searching ===')
res = acd.search(findIn)
for r in res:
  print r
